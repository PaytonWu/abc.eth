// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_OBJECT)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_OBJECT

#pragma once

#include "object_decl.h"
#include "unpack.h"

#include <abc/utility.h>

#include <cstdint>
#include <span>
#include <string_view>
#include <vector>

namespace abc::ethereum::rlp {

class object_parser {
private:
    enum next_ret : std::uint8_t {
        cont,
        done,
        abort,
    };

    struct element {
        abc::ethereum::rlp::object const * ptr;
        size_t rest;

        element(abc::ethereum::rlp::object const * ptr, size_t rest) : ptr{ptr}, rest{rest} {}

        constexpr auto get() const -> abc::ethereum::rlp::object const & {
            return *ptr;
        }

        template <typename VisitorT>
        constexpr auto next(VisitorT && visitor) -> next_ret {
            if (rest == 0) {
                return visitor.end_list() ? next_ret::done : next_ret::abort;
            }

            if (!visitor.end_list_item()) {
                return next_ret::abort;
            }
            --rest;
            if (rest == 0) {
                return visitor.end_list() ? next_ret::done : next_ret::abort;
            }
            if (!visitor.start_list_item()) {
                return next_ret::abort;
            }
            ++ptr;
            return next_ret::cont;
        }
    };

    abc::ethereum::rlp::object const * current_;
    std::vector<element> ctx_;

public:
    explicit object_parser(abc::ethereum::rlp::object const & object) : current_{&object} {
    }

    template <typename VisitorT>
    auto parse(VisitorT && visitor) -> void {
        while (true) {
            bool start_collection = false;
            switch (current_->type) {
                case abc::ethereum::rlp::type::string:
                    if (!visitor.visit_string(std::string_view{ current_->data.string.ptr, current_->data.string.size })) {
                        return;
                    }
                    break;

                case abc::ethereum::rlp::type::bytes:
                    if (!visitor.visit_bytes(std::span < byte const>{ current_->data.bytes.ptr, current_->data.bytes.size })) {
                return;
            }
                    break;

                case abc::ethereum::rlp::type::list:
                    if (!visitor.visit_list(current_->data.list.size)) {
                        return;
                    }
                    ctx_.push_back(element{ current_->data.list.ptr, current_->data.list.size });
                    start_collection = current_->data.list.size != 0;
                    if (start_collection && !visitor.start_list_item()) {
                        return;
                    }
                    break;

                default:
                    abc::unreachable();
                    break;
            }

            if (ctx_.empty()) {
                return;
            }

            if (!start_collection) {
                while (true) {
                    auto r = ctx_.back().next(visitor);
                    if (r == next_ret::done) {
                        ctx_.pop_back();
                        if (ctx_.empty()) {
                            return;
                        }
                    } else if (r == next_ret::cont) {
                        break;
                    } else {
                        // abort
                        return;
                    }
                }
            }
            current_ = std::addressof(ctx_.back().get());
        }
    }
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_OBJECT

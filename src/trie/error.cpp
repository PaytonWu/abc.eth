// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "abc/ethereum/trie/error.h"

namespace abc::ethereum::trie
{

auto
make_error_code(errc const ec) -> std::error_code
{
    return std::error_code{static_cast<int>(ec), ethereum_trie_category()};
}

auto
ethereum_trie_category() -> std::error_category const &
{
    static struct : std::error_category
    {
    public:
        [[nodiscard]] auto
        name() const noexcept -> char const * override
        {
            return "ethereum_trie_category";
        }

        [[nodiscard]] auto
        message(int const code) const -> std::string override
        {
            switch (static_cast<errc>(code))
            {
                case errc::success:
                    return "success";

                case errc::trie_already_committed:
                    return "trie already committed";

                case errc::unexpected_eof:
                    return "unexpected EOF";

                case errc::missing_node:
                    return "missing node";

                case errc::over_sized_embedded_node:
                    return "over sized embedded node";

                case errc::invalid_number_of_list_elements:
                    return "invalid number of list elements";

                default:
                    return "unknown error";
            }
        }
    } category;

    return category;
}

} // namespace abc::ethereum::trie

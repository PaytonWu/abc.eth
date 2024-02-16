// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "abc/ethereum/types/error.h"

namespace abc::ethereum::types
{

auto
make_error_code(errc const ec) -> std::error_code
{
    return std::error_code{static_cast<int>(ec), ethereum_category()};
}

auto
ethereum_category() -> std::error_category const &
{
    static struct : std::error_category
    {
    public:
        [[nodiscard]] auto
        name() const noexcept -> char const * override
        {
            return "ethereum_category";
        }

        [[nodiscard]] auto
        message(int const code) const -> std::string override
        {
            switch (static_cast<errc>(code))
            {
                case errc::success:
                    return "success";

                case errc::invalid_address:
                    return "invalid address";

                default:
                    return "unknown error";
            }
        }
    } category;

    return category;
}

} // namespace abc::ethereum::types

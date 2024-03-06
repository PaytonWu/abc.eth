// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/rlp/error.h>

namespace abc::ethereum::rlp
{

auto
make_error_code(errc const ec) -> std::error_code
{
    return std::error_code{static_cast<int>(ec), ethereum_rlp_category()};
}

auto
ethereum_rlp_category() -> std::error_category const &
{
    static struct : std::error_category
    {
    public:
        [[nodiscard]] auto
        name() const noexcept -> char const * override
        {
            return "ethereum_rlp_category";
        }

        [[nodiscard]] auto
        message(int const code) const -> std::string override
        {
            switch (static_cast<errc>(code))
            {
                case errc::success:
                    return "success";

                case errc::empty_input:
                    return "empty input";

                case errc::invalid_encoded_data:
                    return "input does not conform to RLP encoding form";

                case errc::stack_overflow:
                    return "rlp decode stack overflow";

                case errc::unpack_error:
                    return "rlp unpack error";

                case errc::type_error:
                    return "rlp type error";

                case errc::unexpected_eof:
                    return "unexpected EOF";

                case errc::non_canonical_size:
                    return "rlp: non-canonical size";

                default:
                    return "unknown error";
            }
        }
    } category;

    return category;
}

} // namespace abc::ethereum::rlp

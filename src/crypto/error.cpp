// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/crypto/error.h>

namespace abc::ethereum::crypto
{

auto
make_error_code(errc const ec) -> std::error_code
{
    return std::error_code{static_cast<int>(ec), ethereum_crypto_category()};
}

auto
ethereum_crypto_category() -> std::error_category const &
{
    static struct : std::error_category
    {
    public:
        [[nodiscard]] auto
        name() const noexcept -> char const * override
        {
            return "ethereum_crypto_category";
        }

        [[nodiscard]] auto
        message(int const code) const -> std::string override
        {
            switch (static_cast<errc>(code))
            {
                case errc::invalid_private_key:
                    return "invalid private key";

                case errc::invalid_private_key_length:
                    return "invalid private key length";

                case errc::invalid_public_key:
                    return "invalid public key";

                default:
                    return "unknown error";
            }
        }
    } category;

    return category;
}

} // namespace abc::ethereum::crypto

// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_CRYPTO_KECCAK
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_CRYPTO_KECCAK

#pragma once

#include <abc/fixed_bytes.h>

#include <cryptopp/filters.h>
#include <cryptopp/keccak.h>

#include <span>
#include <string>
#include <string_view>
#include <vector>

namespace abc::ethereum::crypto {

template <unsigned int DigestBitSize>
class [[nodiscard]] keccak {
    static_assert(DigestBitSize % 8 == 0);
public:
    constexpr static size_t DigestSize = DigestBitSize / 8;
private:
    CryptoPP::Keccak_Final<DigestSize> keccak_;

public:
    keccak() = default;

    static auto digest(std::string const & input) -> fixed_bytes<DigestSize, byte_numbering::msb0> {
        fixed_bytes<DigestSize, byte_numbering::msb0> digest;
        CryptoPP::Keccak_Final<DigestSize> hasher;

        hasher.CalculateDigest(digest.data(), input.data(), input.size());

        return digest;
    }

    static auto digest(std::string_view input) -> fixed_bytes<DigestSize, byte_numbering::msb0> {
        fixed_bytes<DigestSize, byte_numbering::msb0> digest;
        CryptoPP::Keccak_Final<DigestSize> hasher;

        hasher.CalculateDigest(digest.data(), input.data(), input.size());

        return digest;
    }

    static auto digest(std::span<byte const> input) -> fixed_bytes<DigestSize, byte_numbering::msb0> {
        fixed_bytes<DigestSize, byte_numbering::msb0> digest;
        CryptoPP::Keccak_Final<DigestSize> hasher;

        hasher.CalculateDigest(digest.data(), input.data(), input.size());

        return digest;
    }
};

using keccak256_t = keccak<256>;

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_CRYPTO_KECCAK

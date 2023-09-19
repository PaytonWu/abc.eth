// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_CRYPTO_ECDSA
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_CRYPTO_ECDSA

#pragma once

#include <cryptopp/eccrypto.h>

namespace abc::ethereum::crypto::ecdsa {

using public_key_t = CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey;
using private_key_t = CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey;

auto gnerate_private_key() -> private_key_t;
auto public_key(private_key_t const & private_key) -> public_key_t;

}


#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_CRYPTO_ECDSA

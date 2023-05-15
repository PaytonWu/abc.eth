// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/crypto/ecdsa.h>

#include <cryptopp/oids.h>
#include <cryptopp/ripemd.h>
#include <cryptopp/hex.h>
#include <cryptopp/osrng.h>

using namespace CryptoPP;

namespace abc::ethereum::crypto {

auto ecdsa::gnerate_private_key() -> ecdsa::private_key_t {
    AutoSeededRandomPool prng;

    private_key_t private_key;
    private_key.Initialize(prng, ASN1::secp256k1());

    return private_key;
}

auto ecdsa::public_key(ecdsa::private_key_t const & private_key) -> public_key_t {
    public_key_t public_key;
    private_key.MakePublicKey(public_key);
    return public_key;
}

}
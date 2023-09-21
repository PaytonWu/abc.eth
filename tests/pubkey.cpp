// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <iostream>
#include <cryptopp/eccrypto.h>
#include <cryptopp/oids.h>
#include <cryptopp/asn.h>
#include <cryptopp/integer.h>
#include <cryptopp/osrng.h>
#include <iomanip>

#include <gtest/gtest.h>

using namespace CryptoPP;

std::vector<byte> exportPublicKey(const ECDSA<ECP, SHA256>::PublicKey& publicKey)
{
    ByteQueue queue;
    publicKey.Save(queue);

    std::vector<byte> exportedKey(queue.MaxRetrievable());
    queue.Get(exportedKey.data(), exportedKey.size());

    return exportedKey;
}

//std::vector<uint8_t> generateRandomPrivateKey()
//{
//    AutoSeededRandomPool prng;
//    ECDSA<ECP, SHA256>::PrivateKey privateKey;
//
//    privateKey.Initialize( prng, ASN1::secp256k1() );
//
//    // Convert the private key to a hexadecimal string
//    Integer privateKeyInt = privateKey.GetPrivateExponent();
//    std::vector<uint8_t> privateKeyStr;
//    privateKeyStr.resize(32);
//    privateKeyInt.Encode(privateKeyStr.data(), privateKeyStr.size());
//
//    return privateKeyStr;
//}

TEST(pubkey, main)
{
//    AutoSeededRandomPool rng;

    // Generate a random private key
//    ECDSA<ECP, SHA256>::PrivateKey privateKey;
//    privateKey.Initialize(rng, ASN1::secp256k1());
//
//    // Derive the corresponding public key
//    ECDSA<ECP, SHA256>::PublicKey publicKey;
//    privateKey.MakePublicKey(publicKey);

    // Export the public key in bytes
//    std::vector<byte> exportedKey = generateRandomPrivateKey();
//
//    std::cout << "Exported public key (" << exportedKey.size() << " bytes): ";
//    for (const auto& byte : exportedKey)
//        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
//    std::cout << std::endl;
}
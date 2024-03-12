// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/rlp/raw.h>

#include <abc/hex_string.h>

#include <gtest/gtest.h>
#include <range/v3/view/enumerate.hpp>
#include <range/v3/view/remove_if.hpp>

#include <cctype>
#include <string>
#include <system_error>

using namespace abc::ethereum::rlp;

auto
unhex(std::string_view str) -> abc::bytes_t
{
    auto hex_str = str | ranges::view::remove_if([](char c) { return static_cast<bool>(std::isspace(c)); }) | ranges::to<std::string>;
    std::cout << "hex_str: " << hex_str << std::endl;

    return abc::hex_string::from(hex_str)
        .transform([](auto && hex) { return hex.template bytes<abc::byte_numbering::msb0>(); })
        .transform([](auto && bytes_be) { return abc::bytes_t::from(bytes_be); })
        .expect("invalid hex string");
}

TEST(rlp_raw, count_value)
{
    struct
    {
        std::string input;
        int count;
        std::error_code ec;
    } tests[]{
        // simple cases
        {"", 0, std::error_code{}},
        {"00", 1, std::error_code{}},
        {"80", 1, std::error_code{}},
        {"C0", 1, std::error_code{}},
        {"01 02 03", 3, std::error_code{}},
        {"01 C406070809 02", 3, std::error_code{}},
        {"820101 820202 8403030303 04", 4, std::error_code{}},

        // size errors
        {"8142", 0, make_error_code(errc::non_canonical_size)},
        {"01 01 8142", 0, make_error_code(errc::non_canonical_size)},
        {"02 84020202", 0, make_error_code(errc::value_too_large)},

        {.input =
             "A12000BF49F440A1CD0527E4D06E2765654C0F56452257516D793A9B8D604DCFDF2AB853F851808D10000000000000000000000000A056E81F171BCC55A6FF8345E692C0F86E5B48E01B996CADC001622FB5E363B421A0C5D2460186F7233C927E7DB2DCC703C0E500B653CA82273B7BFAD8045D85A470",
         .count = 2,
         .ec = std::error_code{}},
    };

    for (auto [i, test] : ranges::view::enumerate(tests))
    {
        auto result = count_value(unhex(test.input));
        std::cout << "test case: " << i << std::endl;
        if (!test.ec)
        {
            ASSERT_FALSE(result.is_err());
            ASSERT_EQ(test.count, result.value());
        }
        else
        {
            ASSERT_TRUE(result.is_err());
            ASSERT_EQ(test.ec, result.error());
        }
    }
}

TEST(rlp_raw, split_bytes)
{
    std::string_view input[]{
        "C0",
        "C100",
        "C3010203",
        "C88363617483646F67",
        "F8384C6F72656D20697073756D20646F6C6F722073697420616D65742C20636F6E7365637465747572206164697069736963696E6720656C6974",
    };

    for (auto [i, test] : ranges::view::enumerate(input))
    {
        auto result = split_bytes(unhex(test));
        ASSERT_TRUE(result.is_err());
        ASSERT_EQ(make_error_code(errc::expected_bytes), result.error());
    }
}

TEST(rlp_raw, split_list)
{
    std::string_view input[]{
        "80",
        "00",
        "01",
        "8180",
        "81FF",
        "820400",
        "83636174",
        "83646F67",
        "B8384C6F72656D20697073756D20646F6C6F722073697420616D65742C20636F6E7365637465747572206164697069736963696E6720656C6974",
    };

    for (auto [i, test] : ranges::view::enumerate(input))
    {
        auto result = split_list(unhex(test));
        ASSERT_TRUE(result.is_err());
        ASSERT_EQ(make_error_code(errc::expected_list), result.error());
    }
}

TEST(rlp_raw, split_unsigned_integral)
{
    struct
    {
        std::string_view input;
        std::uint64_t value;
        std::string_view rest;
        std::error_code ec;
    } tests[]{
        {"01", 1, "", {}},
        {"7FFF", 0x7F, "FF", {}},
        {"80FF", 0, "FF", {}},
        {"81FAFF", 0xFA, "FF", {}},
        {"82FAFAFF", 0xFAFA, "FF", {}},
        {"83FAFAFAFF", 0xFAFAFA, "FF", {}},
        {"84FAFAFAFAFF", 0xFAFAFAFA, "FF", {}},
        {"85FAFAFAFAFAFF", 0xFAFAFAFAFA, "FF", {}},
        {"86FAFAFAFAFAFAFF", 0xFAFAFAFAFAFA, "FF", {}},
        {"87FAFAFAFAFAFAFAFF", 0xFAFAFAFAFAFAFA, "FF", {}},
        {"88FAFAFAFAFAFAFAFAFF", 0xFAFAFAFAFAFAFAFA, "FF", {}},

        // errors
        {"", 0, "", make_error_code(errc::unexpected_eof)},
        {"00", 0, "00", make_error_code(errc::non_canonical_integral)},
        {"81", 0, "81", make_error_code(errc::value_too_large)},
        {"8100", 0, "8100", make_error_code(errc::non_canonical_size)},
        {"8200FF", 0, "8200FF", make_error_code(errc::non_canonical_integral)},
        {"8103FF", 0, "8103FF", make_error_code(errc::non_canonical_size)},
        {"89FAFAFAFAFAFAFAFAFAFF", 0, "89FAFAFAFAFAFAFAFAFAFF", make_error_code(errc::uint_overflow)},
    };

    for (auto [i, test] : ranges::view::enumerate(tests))
    {
        auto result = split_unsigned_integral<std::uint64_t>(unhex(test.input));
        if (!test.ec)
        {
            ASSERT_FALSE(result.is_err());
            auto const & value = result.value();

            ASSERT_EQ(test.value, value.value);
            ASSERT_EQ(test.rest.size(), value.rest.size());
            for (auto j = 0u; j < test.rest.size(); ++j)
            {
                ASSERT_EQ(test.rest[j], value.rest[j]);
            }
            // ASSERT_EQ(static_cast<void const *>(test.rest.data()), static_cast<void const *>(value.rest.data()));
        }
        else
        {
            ASSERT_TRUE(result.is_err());
            ASSERT_EQ(test.ec, result.error());
        }
    }
}
// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/rlp/raw.h>

#include <abc/ethereum/rlp/pack.h>
#include <abc/ethereum/rlp/simple_buffer.h>

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
        auto const test_input = unhex(test.input);
        auto result = split_unsigned_integral<std::uint64_t>(test_input);
        if (!test.ec)
        {
            ASSERT_FALSE(result.is_err());
            auto const & value = result.value();

            ASSERT_EQ(test.value, value.value);
            auto test_rest = unhex(test.rest);
            ASSERT_EQ(test_rest.size(), value.rest.size());
            for (auto j = 0u; j < test_rest.size(); ++j)
            {
                ASSERT_EQ(test_rest[j], value.rest[j]);
            }
        }
        else
        {
            ASSERT_TRUE(result.is_err());
            ASSERT_EQ(test.ec, result.error());
        }
    }
}

TEST(rlp_raw, split)
{
    struct
    {
        std::string_view input;
        type type;
        std::string_view content;
        std::string_view rest;
        std::error_code ec;
    } tests[] {
        {"00FFFF", abc::ethereum::rlp::type::byte, "00", "FFFF", {}},
            {"01FFFF", abc::ethereum::rlp::type::byte, "01", "FFFF", {}},
            {"7FFFFF", abc::ethereum::rlp::type::byte, "7F", "FFFF", {}},
            {"80FFFF", abc::ethereum::rlp::type::bytes, "", "FFFF", {}},
            {"C3010203", abc::ethereum::rlp::type::list, "010203", {}, {}},
            
            // errors
            {"", abc::ethereum::rlp::type::invalid, {}, {}, make_error_code(errc::unexpected_eof)},

            {"8141", abc::ethereum::rlp::type::invalid, {}, "8141", make_error_code(errc::non_canonical_size)},
            {"B800", abc::ethereum::rlp::type::invalid, {}, "B800", make_error_code(errc::non_canonical_size)},
            {"B802FFFF", abc::ethereum::rlp::type::invalid, {}, "B802FFFF", make_error_code(errc::non_canonical_size)},
            {"B90000", abc::ethereum::rlp::type::invalid, {}, "B90000", make_error_code(errc::non_canonical_size)},
            {"B90055", abc::ethereum::rlp::type::invalid, {}, "B90055", make_error_code(errc::non_canonical_size)},
            {"BA0002FFFF", abc::ethereum::rlp::type::invalid, {}, "BA0002FFFF", make_error_code(errc::non_canonical_size)},
            {"F800", abc::ethereum::rlp::type::invalid, {}, "F800", make_error_code(errc::non_canonical_size)},
            {"F90000", abc::ethereum::rlp::type::invalid, {}, "F90000", make_error_code(errc::non_canonical_size)},
            {"F90055", abc::ethereum::rlp::type::invalid, {}, "F90055", make_error_code(errc::non_canonical_size)},
            {"FA0002FFFF", abc::ethereum::rlp::type::invalid, {}, "FA0002FFFF", make_error_code(errc::non_canonical_size)},

            {"81", abc::ethereum::rlp::type::invalid, {}, "81", make_error_code(errc::value_too_large)},
            {"8501010101", abc::ethereum::rlp::type::invalid, {}, "8501010101", make_error_code(errc::value_too_large)},
            {"C60607080902", abc::ethereum::rlp::type::invalid, {}, "C60607080902", make_error_code(errc::value_too_large)},

            // size check overflow
            {"BFFFFFFFFFFFFFFFFF", abc::ethereum::rlp::type::invalid, {}, "BFFFFFFFFFFFFFFFFF", make_error_code(errc::value_too_large)},
            {"FFFFFFFFFFFFFFFFFF", abc::ethereum::rlp::type::invalid, {}, "FFFFFFFFFFFFFFFFFF", make_error_code(errc::value_too_large)},

            {
                "B838FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
            abc::ethereum::rlp::type::invalid, {},
                 "B838FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
            make_error_code(errc::value_too_large)
            },
            {
                "F838FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
            abc::ethereum::rlp::type::invalid, {},
                 "F838FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
            make_error_code(errc::value_too_large)
            },

            // a few bigger values, just for kicks
            {
                "F839FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
                abc::ethereum::rlp::type::list,
                  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
                 "",
            {}
            },
            {
                "F90211A060EF29F20CC1007AE6E9530AEE16F4B31F8F1769A2D1264EC995C6D1241868D6A07C62AB8AC9838F5F5877B20BB37B387BC2106E97A3D52172CBEDB5EE17C36008A00EAB6B7324AADC0F6047C6AFC8229F09F7CF451B51D67C8DFB08D49BA8C3C626A04453343B2F3A6E42FCF87948F88AF7C8FC16D0C2735CBA7F026836239AB2C15FA024635C7291C882CE4C0763760C1A362DFC3FFCD802A55722236DE058D74202ACA0A220C808DE10F55E40AB25255201CFF009EA181D3906638E944EE2BF34049984A08D325AB26796F1CCB470F69C0F842501DC35D368A0C2575B2D243CFD1E8AB0FDA0B5298FF60DA5069463D610513C9F04F24051348391A143AFFAB7197DFACDEA72A02D2A7058A4463F8FB69378369E11EF33AE3252E2DB86CB545B36D3C26DDECE5AA0888F97BCA8E0BD83DC5B3B91CFF5FAF2F66F9501010682D67EF4A3B4E66115FBA0E8175A60C93BE9ED02921958F0EA55DA0FB5E4802AF5846147BAD92BC2D8AF26A08B3376FF433F3A4250FA64B7F804004CAC5807877D91C4427BD1CD05CF912ED8A09B32EF0F03BD13C37FF950C0CCCEFCCDD6669F2E7F2AA5CB859928E84E29763EA09BBA5E46610C8C8B1F8E921E5691BF8C7E40D75825D5EA3217AA9C3A8A355F39A0EEB95BC78251CCCEC54A97F19755C4A59A293544EEE6119AFA50531211E53C4FA00B6E86FE150BF4A9E0FEEE9C90F5465E617A861BB5E357F942881EE762212E2580",
            abc::ethereum::rlp::type::list,
                  "A060EF29F20CC1007AE6E9530AEE16F4B31F8F1769A2D1264EC995C6D1241868D6A07C62AB8AC9838F5F5877B20BB37B387BC2106E97A3D52172CBEDB5EE17C36008A00EAB6B7324AADC0F6047C6AFC8229F09F7CF451B51D67C8DFB08D49BA8C3C626A04453343B2F3A6E42FCF87948F88AF7C8FC16D0C2735CBA7F026836239AB2C15FA024635C7291C882CE4C0763760C1A362DFC3FFCD802A55722236DE058D74202ACA0A220C808DE10F55E40AB25255201CFF009EA181D3906638E944EE2BF34049984A08D325AB26796F1CCB470F69C0F842501DC35D368A0C2575B2D243CFD1E8AB0FDA0B5298FF60DA5069463D610513C9F04F24051348391A143AFFAB7197DFACDEA72A02D2A7058A4463F8FB69378369E11EF33AE3252E2DB86CB545B36D3C26DDECE5AA0888F97BCA8E0BD83DC5B3B91CFF5FAF2F66F9501010682D67EF4A3B4E66115FBA0E8175A60C93BE9ED02921958F0EA55DA0FB5E4802AF5846147BAD92BC2D8AF26A08B3376FF433F3A4250FA64B7F804004CAC5807877D91C4427BD1CD05CF912ED8A09B32EF0F03BD13C37FF950C0CCCEFCCDD6669F2E7F2AA5CB859928E84E29763EA09BBA5E46610C8C8B1F8E921E5691BF8C7E40D75825D5EA3217AA9C3A8A355F39A0EEB95BC78251CCCEC54A97F19755C4A59A293544EEE6119AFA50531211E53C4FA00B6E86FE150BF4A9E0FEEE9C90F5465E617A861BB5E357F942881EE762212E2580",
                 "",
            {}
            },
            {
                "F877A12000BF49F440A1CD0527E4D06E2765654C0F56452257516D793A9B8D604DCFDF2AB853F851808D10000000000000000000000000A056E81F171BCC55A6FF8345E692C0F86E5B48E01B996CADC001622FB5E363B421A0C5D2460186F7233C927E7DB2DCC703C0E500B653CA82273B7BFAD8045D85A470",
            abc::ethereum::rlp::type::list,
                  "A12000BF49F440A1CD0527E4D06E2765654C0F56452257516D793A9B8D604DCFDF2AB853F851808D10000000000000000000000000A056E81F171BCC55A6FF8345E692C0F86E5B48E01B996CADC001622FB5E363B421A0C5D2460186F7233C927E7DB2DCC703C0E500B653CA82273B7BFAD8045D85A470",
                 "",
            {}
            },
    };

    for (auto [i, test] : ranges::view::enumerate(tests))
    {
        auto const test_input = unhex(test.input);
        auto result = split(test_input);
        if (!test.ec)
        {
            ASSERT_FALSE(result.is_err());
            auto const & value = result.value();

            auto const test_content = unhex(test.content);
            ASSERT_EQ(test_content.size(), value.content.size());
            for (auto j = 0u; j < test_content.size(); ++j)
            {
                ASSERT_EQ(test_content[j], value.content[j]);
            }

            auto const test_rest = unhex(test.rest);
            ASSERT_EQ(test_rest.size(), value.rest.size());
            for (auto j = 0u; j < test_rest.size(); ++j)
            {
                ASSERT_EQ(test_rest[j], value.rest[j]);
            }
        }
        else
        {
            ASSERT_TRUE(result.is_err());
            ASSERT_EQ(test.ec, result.error());
        }
    }
}

TEST(rlp_raw, read_size)
{
    struct
    {
        std::string_view input;
        std::uint8_t size_of_length;
        std::uint64_t size;
        std::error_code ec;
    } tests[] {
        {.input = "", .size_of_length = 1, .size = 0, .ec = make_error_code(errc::unexpected_eof) },
        {.input = "FF", .size_of_length = 2, .size = 0, .ec = make_error_code(errc::unexpected_eof) },
        {.input = "00", .size_of_length = 1, .size = 0, .ec = make_error_code(errc::non_canonical_size) },
        {.input = "36", .size_of_length = 1, .size = 0, .ec = make_error_code(errc::non_canonical_size) },
        {.input = "37", .size_of_length = 1, .size = 0, .ec = make_error_code(errc::non_canonical_size) },
        {.input = "38", .size_of_length = 1, .size = 0x38, .ec = {}},
        {.input = "FF", .size_of_length = 1, .size = 0xFF, .ec = {}},
        {.input = "FFFF", .size_of_length = 2, .size = 0xFFFF, .ec = {}},
        {.input = "FFFFFF", .size_of_length = 3, .size = 0xFFFFFF, .ec = {}},
        {.input = "FFFFFFFF", .size_of_length = 4, .size = 0xFFFFFFFF, .ec = {}},
        {.input = "FFFFFFFFFF", .size_of_length = 5, .size = 0xFFFFFFFFFF, .ec = {}},
        {.input = "FFFFFFFFFFFF", .size_of_length = 6, .size = 0xFFFFFFFFFFFF, .ec = {}},
        {.input = "FFFFFFFFFFFFFF", .size_of_length = 7, .size = 0xFFFFFFFFFFFFFF, .ec = {}},
        {.input = "FFFFFFFFFFFFFFFF", .size_of_length = 8, .size = 0xFFFFFFFFFFFFFFFF, .ec = {}},
        {.input = "0102", .size_of_length = 2, .size = 0x0102, .ec = {}},
        {.input = "010203", .size_of_length = 3, .size = 0x010203, .ec = {}},
        {.input = "01020304", .size_of_length = 4, .size = 0x01020304, .ec = {}},
        {.input = "0102030405", .size_of_length = 5, .size = 0x0102030405, .ec = {}},
        {.input = "010203040506", .size_of_length = 6, .size = 0x010203040506, .ec = {}},
        {.input = "01020304050607", .size_of_length = 7, .size = 0x01020304050607, .ec = {}},
        {.input = "0102030405060708", .size_of_length = 8, .size = 0x0102030405060708, .ec = {}},
    };

    for (auto [i, test] : ranges::view::enumerate(tests))
    {
        auto const test_input = unhex(test.input);
        auto result = read_size(test_input, test.size_of_length);
        if (!test.ec)
        {
            ASSERT_FALSE(result.is_err());
            ASSERT_EQ(test.size, result.value());
        }
        else
        {
            ASSERT_TRUE(result.is_err());
            ASSERT_EQ(test.ec, result.error());
        }
    }
}

TEST(rlp_raw, append_unsigned_integral)
{
    struct
    {
        std::uint64_t input;
        abc::bytes_t buffer;
        std::string_view output;
    } tests[] {
        {0, {}, "80"},
        {1, {}, "01"},
        {2, {}, "02"},
        {127, {}, "7F"},
        {128, {}, "8180"},
        {129, {}, "8181"},
        {0xFFFFFF, {}, "83FFFFFF"},
        {127, abc::bytes_t{1, 2, 3}, "0102037F"},
        {0xFFFFFF, abc::bytes_t{1, 2, 3}, "01020383FFFFFF"},
    };

    for (auto [i, test] : ranges::view::enumerate(tests))
    {
        auto const origin_test_buffer = test.buffer;
        auto const expected_buffer = unhex(test.output);

        append_unsigned_integral(test.buffer, test.input);
        ASSERT_EQ(expected_buffer, test.buffer);

        // Check that IntSize returns the appended size.
        auto const length = test.buffer.size() - origin_test_buffer.size();
        auto const sz = encoded_size_of_value(test.input);
        ASSERT_EQ(sz, length);
    }
}

TEST(rlp_raw, bytes_size)
{
    struct
    {
        abc::bytes_t v;
        std::uint64_t size;
    } tests[] {
        {.v = {}, .size = 1},
        {.v = {0x1}, .size = 1},
        {.v = {0x7E}, .size = 1},
        {.v = {0x7F}, .size = 1},
        {.v = {0x80}, .size = 2},
        {.v = {0xFF}, .size = 2},
        {.v = {0xFF, 0xF0}, .size = 3},
        // {.v = make([]byte, 55), .size = 56},
        // {.v = make([]byte, 56), .size = 58},
    };

    for (auto const & test : tests)
    {
        auto const result = bytes_size(test.v);
        ASSERT_EQ(test.size, result);

        simple_buffer buffer;
        packer<simple_buffer> packer{buffer};
        packer.pack(test.v);
        ASSERT_EQ(test.size, buffer.size());
    }

    {
        auto bytes = abc::bytes_t{};
        bytes.resize(55);
        auto const result = bytes_size(bytes);
        ASSERT_EQ(56, result);

        simple_buffer buffer;
        packer<simple_buffer> packer{buffer};
        packer.pack(bytes);
        ASSERT_EQ(56, buffer.size());
    }

    {
        auto bytes = abc::bytes_t{};
        bytes.resize(56);
        auto const result = bytes_size(bytes);
        ASSERT_EQ(58, result);

        simple_buffer buffer;
        packer<simple_buffer> packer{buffer};
        packer.pack(bytes);
        ASSERT_EQ(58, buffer.size());
    }


}
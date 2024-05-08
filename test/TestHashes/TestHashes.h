#pragma once

#include <gtest/gtest.h>
#include "Hashes.h"
#include "Hashes.cpp" // the linking error without this #include

#define UNUSED(x) (void)(x); // hack to bypass [[nodiscard]]

namespace TestHashes
{
    TEST(TestHashes, TestMethodCorrectHashMD5)
    {
        const std::string hash_md5_test
        {
            static_cast<char>(0xcd), static_cast<char>(0x6b), static_cast<char>(0x8f), static_cast<char>(0x09),
            static_cast<char>(0x73), static_cast<char>(0xd3), static_cast<char>(0x21), static_cast<char>(0x46),
            static_cast<char>(0x83), static_cast<char>(0x4e), static_cast<char>(0xde), static_cast<char>(0xca),
            static_cast<char>(0xf6), static_cast<char>(0xb4), static_cast<char>(0x27), static_cast<char>(0x26),
        };

        EXPECT_EQ(Hashes::Hashes::GetMD5("test"), hash_md5_test);
    }

    TEST(TestHashes, TestMethodEmptyHashMD5)
    {
        EXPECT_THROW(UNUSED(Hashes::Hashes::GetMD5("")), std::invalid_argument);
    }

    TEST(TestHashes, TestMethodCorrectHashSHA1)
    {
        const std::string hash_sha1_test
        {
            static_cast<char>(0x61), static_cast<char>(0x39), static_cast<char>(0x34), static_cast<char>(0x61),
            static_cast<char>(0x38), static_cast<char>(0x66), static_cast<char>(0x65), static_cast<char>(0x35),
            static_cast<char>(0x63), static_cast<char>(0x63), static_cast<char>(0x62), static_cast<char>(0x31),
            static_cast<char>(0x39), static_cast<char>(0x62), static_cast<char>(0x61), static_cast<char>(0x36),
            static_cast<char>(0x31), static_cast<char>(0x63), static_cast<char>(0x34), static_cast<char>(0x63),
            static_cast<char>(0x30), static_cast<char>(0x38), static_cast<char>(0x37), static_cast<char>(0x33),
            static_cast<char>(0x64), static_cast<char>(0x33), static_cast<char>(0x39), static_cast<char>(0x31),
            static_cast<char>(0x65), static_cast<char>(0x39), static_cast<char>(0x38), static_cast<char>(0x37),
            static_cast<char>(0x39), static_cast<char>(0x38), static_cast<char>(0x32), static_cast<char>(0x66),
            static_cast<char>(0x62), static_cast<char>(0x62), static_cast<char>(0x64), static_cast<char>(0x33),
        };

        EXPECT_EQ(Hashes::Hashes::GetSHA1("test"), hash_sha1_test);
    }

    TEST(TestHashes, TestMethodEmptyHashSHA1)
    {
        EXPECT_THROW(UNUSED(Hashes::Hashes::GetSHA1("")), std::invalid_argument);
    }
}

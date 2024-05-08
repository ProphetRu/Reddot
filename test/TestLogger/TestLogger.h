#pragma once

#include <gtest/gtest.h>
#include "LoggerSafe.h"
#include "LoggerSafe.cpp" // the linking error without this #include

namespace TestLogger
{
    TEST(TestLogger, TestLogOK)
    {
        EXPECT_NO_THROW(Log::LoggerSafe::Init("test.log"));
        EXPECT_NO_THROW(Log::LoggerSafe::LogInformation("test record"));
        Log::LoggerSafe::Cleanup();
    }

    TEST(TestLogger, TestCtrWithoutLogFileName)
    {
        EXPECT_THROW(Log::LoggerSafe::Init(""), std::invalid_argument);
    }

    TEST(TestLogger, TestLogWithEmptyLogRecord)
    {
        EXPECT_NO_THROW(Log::LoggerSafe::Init("test.log"));
        EXPECT_THROW(Log::LoggerSafe::LogInformation(""), std::invalid_argument);
        Log::LoggerSafe::Cleanup();
    }

    TEST(TestLogger, TestLogWithoutLogFileName)
    {
        Log::LoggerSafe::Cleanup();
        EXPECT_THROW(Log::LoggerSafe::LogInformation("test"), std::runtime_error);
    }
}

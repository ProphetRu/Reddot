#pragma once

#include <gtest/gtest.h>
#include "DB/DBManager.h"

// the linking error without this #include
#include "DB/DBManager.cpp"

namespace TestDBManager
{
	TEST(TestDBManager, TestCtrNoDBConnection)
	{
		EXPECT_THROW(DB::DBManager dbm("localhost", 3306, "root", "pass", "testdb"), std::exception);
	}

	TEST(TestDBManager, TestCtrEmpty)
	{
		EXPECT_THROW(DB::DBManager dbm("",          3306, "root", "pass", "testdb"), std::invalid_argument);
		EXPECT_THROW(DB::DBManager dbm("localhost", 0,    "root", "pass", "testdb"), std::invalid_argument);
		EXPECT_THROW(DB::DBManager dbm("localhost", 3306, "",     "pass", "testdb"), std::invalid_argument);
		EXPECT_THROW(DB::DBManager dbm("localhost", 3306, "root", "",     "testdb"), std::invalid_argument);
		EXPECT_THROW(DB::DBManager dbm("localhost", 3306, "root", "pass", ""),       std::invalid_argument);
	}
}

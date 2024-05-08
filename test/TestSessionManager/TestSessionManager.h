#pragma once

#include <gtest/gtest.h>
#include "CMS/SessionManager.h"
#include "CMS/SessionManager.cpp" // the linking error without this #include

namespace TestSessionManager
{
	TEST(TestSessionManager, TestAddSessionOK)
	{
		CMS::Session::SessionManager sm;
		EXPECT_NO_THROW(sm.AddSession("login", "hash"));
	}

	TEST(TestSessionManager, TestAddSessionEmptyLogin)
	{
		CMS::Session::SessionManager sm;
		EXPECT_THROW(sm.AddSession("", "hash"), std::invalid_argument);
	}

	TEST(TestSessionManager, TestAddSessionEmptyHash)
	{
		CMS::Session::SessionManager sm;
		EXPECT_THROW(sm.AddSession("login", ""), std::invalid_argument);
	}

	TEST(TestSessionManager, TestIsActiveSessionOK)
	{
		CMS::Session::SessionManager sm;
		EXPECT_NO_THROW(sm.AddSession("login", "hash"));
		EXPECT_EQ(sm.IsActiveSession("hash"), true);
	}

	TEST(TestSessionManager, TestIsActiveSessionFail)
	{
		CMS::Session::SessionManager sm;
		EXPECT_EQ(sm.IsActiveSession("hash"), false);

		EXPECT_NO_THROW(sm.AddSession("login", "hash"));
		EXPECT_EQ(sm.IsActiveSession("hash1"), false);
	}

	TEST(TestSessionManager, TestGetLoginOK)
	{
		CMS::Session::SessionManager sm;
		EXPECT_NO_THROW(sm.AddSession("login", "hash"));
		EXPECT_EQ(sm.GetLogin("hash"), "login");
	}

	TEST(TestSessionManager, TestGetLoginFail)
	{
		CMS::Session::SessionManager sm;
		EXPECT_EQ(sm.GetLogin("hash"), "");

		EXPECT_NO_THROW(sm.AddSession("login", "hash"));
		EXPECT_EQ(sm.GetLogin("hash1"), "");
	}

	TEST(TestSessionManager, TestDeleteSessionEmpty)
	{
		CMS::Session::SessionManager sm;
		EXPECT_THROW(sm.DeleteSession(""), std::invalid_argument);
	}

	TEST(TestSessionManager, TestDeleteSessionOK)
	{
		CMS::Session::SessionManager sm;
		EXPECT_NO_THROW(sm.DeleteSession("hash"));
	}
}
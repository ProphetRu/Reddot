#pragma once

#include <gtest/gtest.h>
#include "CMS/WebPages/WebPageFactory.h"

// the linking error without this #include
#include "CMS/WebPages/WebPageFactory.cpp"
#include "CMS/WebPages/WebPageID.h"
#include "CMS/WebPages/IWebPage.cpp"
#include "CMS/WebPages/WebPageAccount.cpp"
#include "CMS/WebPages/WebPageForbidden.cpp"
#include "CMS/WebPages/WebPageIndex.cpp"
#include "CMS/WebPages/WebPageLogin.cpp"
#include "CMS/WebPages/WebPageNotFound.cpp"
#include "CMS/WebPages/WebPagePost.cpp"
#include "CMS/WebPages/WebPageRegistration.cpp"

namespace TestWebPageFactory
{
	// tests is launched from the build folder
	const std::string WEB_PAGES_DIR_PATH{ R"(../test/TestWebPageFactory/www-data/)" };

	TEST(TestWebPageFactory, TestCtrOK)
	{
		EXPECT_NO_THROW(CMS::WebPages::WebPageFactory factory(WEB_PAGES_DIR_PATH));
	}

	TEST(TestWebPageFactory, TestCtrEmptyPath)
	{
		EXPECT_THROW(CMS::WebPages::WebPageFactory factory(""), std::invalid_argument);
	}

	TEST(TestWebPageFactory, TestCtrEmptyPages)
	{
		EXPECT_THROW(CMS::WebPages::WebPageFactory factory(WEB_PAGES_DIR_PATH + "empty-pages"), std::runtime_error);
	}

	TEST(TestWebPageFactory, TestGetWebPageID)
	{
		const CMS::WebPages::WebPageFactory factory(WEB_PAGES_DIR_PATH);
		EXPECT_EQ(factory.GetWebPageID("/404.html"),      CMS::WebPages::WebPageID::NotFound);
		EXPECT_EQ(factory.GetWebPageID("/403.html"),      CMS::WebPages::WebPageID::Forbidden);
		EXPECT_EQ(factory.GetWebPageID("/reg.html"),      CMS::WebPages::WebPageID::Registration);
		EXPECT_EQ(factory.GetWebPageID("/login.html"),    CMS::WebPages::WebPageID::Login);
		EXPECT_EQ(factory.GetWebPageID("/account.html"),  CMS::WebPages::WebPageID::Account);
		EXPECT_EQ(factory.GetWebPageID("/post.html"),     CMS::WebPages::WebPageID::Post);
		EXPECT_EQ(factory.GetWebPageID("/index.html"),    CMS::WebPages::WebPageID::Index);
		EXPECT_EQ(factory.GetWebPageID("/"),              CMS::WebPages::WebPageID::Index);
		EXPECT_EQ(factory.GetWebPageID("/notexist.html"), CMS::WebPages::WebPageID::NotFound);
	}

	TEST(TestWebPageFactory, TestCreateWebPageNotFound)
	{
		CMS::WebPages::WebPageFactory factory(WEB_PAGES_DIR_PATH);
		const auto page{ factory.CreateWebPageNotFound()->GenerateWebPage() };
		EXPECT_EQ(page.contains("Reddot - 404 Not Found"), true);
	}

	TEST(TestWebPageFactory, TestCreateWebPageForbidden)
	{
		CMS::WebPages::WebPageFactory factory(WEB_PAGES_DIR_PATH);
		const auto page{ factory.CreateWebPageForbidden()->GenerateWebPage() };
		EXPECT_EQ(page.contains("Reddot - 403 Forbidden"), true);
	}

	TEST(TestWebPageFactory, TestCreateWebPageRegistration)
	{
		CMS::WebPages::WebPageFactory factory(WEB_PAGES_DIR_PATH);
		auto page{ factory.CreateWebPageRegistration(CMS::WebPages::RegistrationState::None)->GenerateWebPage() };
		EXPECT_EQ(page.contains("Registration"), true);

		page = factory.CreateWebPageRegistration(CMS::WebPages::RegistrationState::Failed)->GenerateWebPage();
		EXPECT_EQ(page.contains("Registration failed"), true);

		page = factory.CreateWebPageRegistration(CMS::WebPages::RegistrationState::OK)->GenerateWebPage();
		EXPECT_EQ(page.contains("Registration OK"), true);
	}

	TEST(TestWebPageFactory, TestCreateWebPageLogin)
	{
		CMS::WebPages::WebPageFactory factory(WEB_PAGES_DIR_PATH);
		auto page{ factory.CreateWebPageLogin(CMS::WebPages::LoginState::None)->GenerateWebPage() };
		EXPECT_EQ(page.contains("Login"), true);

		page = factory.CreateWebPageLogin(CMS::WebPages::LoginState::Failed)->GenerateWebPage();
		EXPECT_EQ(page.contains("Login failed"), true);

		page = factory.CreateWebPageLogin(CMS::WebPages::LoginState::OK)->GenerateWebPage();
		EXPECT_EQ(page.contains("Login OK"), true);
	}

	TEST(TestWebPageFactory, TestCreateWebPageAccount)
	{
		CMS::WebPages::WebPageFactory factory(WEB_PAGES_DIR_PATH);
		const auto page{ factory.CreateWebPageAccount("alice", "user")->GenerateWebPage()};
		EXPECT_EQ(page.contains("Reddot - Account"), true);
		EXPECT_EQ(page.contains("alice"),            true);
		EXPECT_EQ(page.contains("user"),             true);
	}

	TEST(TestWebPageFactory, TestCreateWebPagePost)
	{
		CMS::WebPages::WebPageFactory factory(WEB_PAGES_DIR_PATH);

		const DB::Post post
		{
			.ID      = 42,
			.Login   = "alice",
			.Caption = "post_caption",
			.Body    = "post_body"
		};

		const auto page{ factory.CreateWebPagePost("alice", post)->GenerateWebPage()};

		EXPECT_EQ(page.contains("Reddot - Post"), true);
		EXPECT_EQ(page.contains("42"),            true);
		EXPECT_EQ(page.contains(post.Login),      true);
		EXPECT_EQ(page.contains(post.Caption),    true);
		EXPECT_EQ(page.contains(post.Body),       true);
	}

	TEST(TestWebPageFactory, TestCreateWebPageIndex)
	{
		CMS::WebPages::WebPageFactory factory(WEB_PAGES_DIR_PATH);

		const DB::Posts posts
		{
			DB::Post
			{
				.ID      = 42,
				.Login   = "alice",
				.Caption = "post_caption1",
				.Body    = "post_body1"
			},
			DB::Post
			{
				.ID      = 43,
				.Login   = "bob",
				.Caption = "post_caption2",
				.Body    = "post_body2"
			},
		};

		const auto page{ factory.CreateWebPageIndex("alice", posts)->GenerateWebPage()};

		EXPECT_EQ(page.contains("Reddot - Index"), true);
		EXPECT_EQ(page.contains("42"),             true);
		EXPECT_EQ(page.contains("43"),             true);
		EXPECT_EQ(page.contains(posts[0].Login),   true);
		EXPECT_EQ(page.contains(posts[0].Caption), true);
		EXPECT_EQ(page.contains(posts[1].Login),   true);
		EXPECT_EQ(page.contains(posts[1].Caption), true);
	}
}

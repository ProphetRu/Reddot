#pragma once

#include <gtest/gtest.h>
#include "WebSecurityFilters/WebSecurityFiltersManager.h"

// the linking error without this #include
#include "WebSecurityFilters/WebSecurityFiltersManager.cpp"
#include "WebSecurityFilters/IWebSecurityFilter.cpp"
#include "WebSecurityFilters/FilterDOM.cpp"
#include "WebSecurityFilters/FilterHTTP.cpp"
#include "WebSecurityFilters/FilterPaths.cpp"
#include "WebSecurityFilters/FilterSqlInjection.cpp"
#include "WebSecurityFilters/FilterXSS.cpp"
#include "WebSecurityFilters/FilterXXE.cpp"

namespace TestWebSecurityFilters
{
	TEST(TestWebSecurityFilters, TestFilterEmpty)
	{
		const Security::WebSecurityFiltersManager filters;
		EXPECT_THROW(filters.Check(""), std::invalid_argument);
	}

	TEST(TestWebSecurityFilters, TestFilterOK)
	{
		const Security::WebSecurityFiltersManager filters;
		EXPECT_NO_THROW(filters.Check("testcontent"));
	}

	TEST(TestWebSecurityFilters, TestFilterDOMDanger)
	{
		const Security::WebSecurityFiltersManager filters;
		EXPECT_THROW(filters.Check("test<content"), std::runtime_error);
	}

	TEST(TestWebSecurityFilters, TestFilterHTTPDanger)
	{
		const Security::WebSecurityFiltersManager filters;
		EXPECT_THROW(filters.Check("test\rcontent"), std::runtime_error);
	}

	TEST(TestWebSecurityFilters, TestFilterPathsDanger)
	{
		const Security::WebSecurityFiltersManager filters;
		EXPECT_THROW(filters.Check("test/content"), std::runtime_error);
	}

	TEST(TestWebSecurityFilters, TestFilterSqlInjectionDanger)
	{
		const Security::WebSecurityFiltersManager filters;
		EXPECT_THROW(filters.Check("test'content"), std::runtime_error);
	}

	TEST(TestWebSecurityFilters, TestFilterXSSDanger)
	{
		const Security::WebSecurityFiltersManager filters;
		EXPECT_THROW(filters.Check("test&content"), std::runtime_error);
	}

	TEST(TestWebSecurityFilters, TestFilterXXEDanger)
	{
		const Security::WebSecurityFiltersManager filters;
		EXPECT_THROW(filters.Check("test[content"), std::runtime_error);
	}
}

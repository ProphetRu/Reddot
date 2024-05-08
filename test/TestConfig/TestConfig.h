#pragma once

#include <gtest/gtest.h>
#include "Config.h"
#include "Config.cpp" // the linking error without this #include

namespace TestConfig
{
	// tests is launched from the build folder
	const std::string CONFIG_DIR_PATH{ R"(../test/TestConfig/test-configs/)" };
	TEST(TestConfig, TestConfigOK)
	{
		EXPECT_NO_THROW(Config::Config::Init(CONFIG_DIR_PATH + "config_ok.ini"));
		ASSERT_EQ(Config::Config::GetWebRootPath(), "Resources/www-data/");
		ASSERT_EQ(Config::Config::GetServerPort(),  4444);
		ASSERT_EQ(Config::Config::GetDBLogin(),     "reddot");
		ASSERT_EQ(Config::Config::GetDBPassword(),  "reddot");
		ASSERT_EQ(Config::Config::GetDBServer(),    "192.168.5.128");
		ASSERT_EQ(Config::Config::GetDBPort(),      3306);
		ASSERT_EQ(Config::Config::GetDBName(),      "reddot");
	}

	TEST(TestConfig, TestEmptyConfigFileName)
	{
		EXPECT_THROW(Config::Config::Init(""), std::invalid_argument);
	}

	TEST(TestConfig, TestNotExistConfigFileName)
	{
		EXPECT_THROW(Config::Config::Init("not_exist.ini"), std::runtime_error);
	}

	TEST(TestConfig, TestEmptyConfigFile)
	{
		EXPECT_THROW(Config::Config::Init(CONFIG_DIR_PATH + "config_empty.ini"), std::exception);
	}
	
	TEST(TestConfig, TestConfigNoWebRootPath)
	{
		EXPECT_THROW(Config::Config::Init(CONFIG_DIR_PATH + "config_no_web_root_path.ini"), std::invalid_argument);
	}

	TEST(TestConfig, TestConfigNoServerPort)
	{
		EXPECT_THROW(Config::Config::Init(CONFIG_DIR_PATH + "config_no_server_port.ini"), std::invalid_argument);
	}

	TEST(TestConfig, TestConfigNoDBLogin)
	{
		EXPECT_THROW(Config::Config::Init(CONFIG_DIR_PATH + "config_no_db_login.ini"), std::invalid_argument);
	}

	TEST(TestConfig, TestConfigNoDBPassword)
	{
		EXPECT_THROW(Config::Config::Init(CONFIG_DIR_PATH + "config_no_db_password.ini"), std::invalid_argument);
	}

	TEST(TestConfig, TestConfigNoDBServer)
	{
		EXPECT_THROW(Config::Config::Init(CONFIG_DIR_PATH + "config_no_db_server.ini"), std::invalid_argument);
	}

	TEST(TestConfig, TestConfigNoDBPort)
	{
		EXPECT_THROW(Config::Config::Init(CONFIG_DIR_PATH + "config_no_db_port.ini"), std::invalid_argument);
	}

	TEST(TestConfig, TestConfigNoDBName)
	{
		EXPECT_THROW(Config::Config::Init(CONFIG_DIR_PATH + "config_no_db_name.ini"), std::invalid_argument);
	}
	
	TEST(TestConfig, TestConfigEmptyWebRootPath)
	{
		EXPECT_THROW(Config::Config::Init(CONFIG_DIR_PATH + "config_empty_web_root_path.ini"), std::invalid_argument);
	}

	TEST(TestConfig, TestConfigEmptyServerPort)
	{
		EXPECT_THROW(Config::Config::Init(CONFIG_DIR_PATH + "config_empty_server_port.ini"), std::exception);
	}

	TEST(TestConfig, TestConfigEmptyDBLogin)
	{
		EXPECT_THROW(Config::Config::Init(CONFIG_DIR_PATH + "config_empty_db_login.ini"), std::invalid_argument);
	}

	TEST(TestConfig, TestConfigEmptyDBPassword)
	{
		EXPECT_THROW(Config::Config::Init(CONFIG_DIR_PATH + "config_empty_db_password.ini"), std::invalid_argument);
	}

	TEST(TestConfig, TestConfigEmptyDBServer)
	{
		EXPECT_THROW(Config::Config::Init(CONFIG_DIR_PATH + "config_empty_db_server.ini"), std::invalid_argument);
	}

	TEST(TestConfig, TestConfigEmptyDBPort)
	{
		EXPECT_THROW(Config::Config::Init(CONFIG_DIR_PATH + "config_empty_db_port.ini"), std::exception);
	}

	TEST(TestConfig, TestConfigEmptyDBName)
	{
		EXPECT_THROW(Config::Config::Init(CONFIG_DIR_PATH + "config_empty_db_name.ini"), std::invalid_argument);
	}
	
	TEST(TestConfig, TestConfigInvalidServerPort)
	{
		EXPECT_THROW(Config::Config::Init(CONFIG_DIR_PATH + "config_invalid_server_port.ini"), std::exception);
	}

	TEST(TestConfig, TestConfigInvalidDBPort)
	{
		EXPECT_THROW(Config::Config::Init(CONFIG_DIR_PATH + "config_invalid_db_port.ini"), std::exception);
	}

	TEST(TestConfig, TestConfigNotIntServerPort)
	{
		EXPECT_THROW(Config::Config::Init(CONFIG_DIR_PATH + "config_not_int_server_port.ini"), std::exception);
	}

	TEST(TestConfig, TestConfigNotIntDBPort)
	{
		EXPECT_THROW(Config::Config::Init(CONFIG_DIR_PATH + "config_not_int_db_port.ini"), std::exception);
	}
}

#include <iostream>
#include <memory>

#include "LoggerSafe.h"
#include "Config.h"
#include "Server/ServerHTTPS.h"
#include "CMS/CMS.h"

constexpr auto LOG_FILE_PATH   { "reddot.log"                };
constexpr auto CONFIG_FILE_PATH{ "resources/config.ini"      };
constexpr auto KEY_FILE_PATH   { "resources/cert/reddot.key" };
constexpr auto CERT_FILE_PATH  { "resources/cert/reddot.crt" };

int main(int argc, char* argv[]) noexcept
{
	try
	{
		Log::LoggerSafe::Init(LOG_FILE_PATH);
		Log::LoggerSafe::LogInformation("Server is running");

		Log::LoggerSafe::LogInformation("Init config");
		Config::Config::Init(CONFIG_FILE_PATH);

		Log::LoggerSafe::LogInformation("Init CMS");
		CMS::CMS::GetInstance();

#ifdef _DEBUG
		Log::LoggerSafe::LogDebug("Web root path: " + Config::Config::GetWebRootPath());
		Log::LoggerSafe::LogDebug("Server port  : " + std::to_string(Config::Config::GetServerPort()));
		Log::LoggerSafe::LogDebug("DB login     : " + Config::Config::GetDBLogin());
		Log::LoggerSafe::LogDebug("DB password  : " + Config::Config::GetDBPassword());
		Log::LoggerSafe::LogDebug("DB server    : " + Config::Config::GetDBServer());
		Log::LoggerSafe::LogDebug("DB port      : " + std::to_string(Config::Config::GetDBPort()));
		Log::LoggerSafe::LogDebug("DB name      : " + Config::Config::GetDBName());
#endif // _DEBUG

		Log::LoggerSafe::LogInformation("Init Server");
		const auto server_https{ std::make_unique<Server::ServerHTTPS>(KEY_FILE_PATH, CERT_FILE_PATH, Config::Config::GetServerPort()) };
		server_https->run(argc, argv);
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Critical: " << ex.what() << std::endl;
	}

	Log::LoggerSafe::LogInformation("Server is stopped");
	Log::LoggerSafe::Cleanup();
	return 0;
}

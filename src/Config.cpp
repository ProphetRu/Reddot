#include "Config.h"
#include <fstream>
#include <boost/program_options.hpp>

namespace Config
{
    namespace po = boost::program_options;

    void Config::Init(std::string_view config_file_name)
    {
        auto is_valid_port = [](int port) noexcept
        {
            return ((port > 0) && (port < 65535));
        };

        // check arg
        if (config_file_name.empty())
        {
            throw std::invalid_argument("Config file name is empty");
        }

        // open config file
        std::ifstream config_file{ config_file_name.data() };
        if (!config_file.is_open())
        {
            throw std::runtime_error("Can't open config file");
        }

        // parse config
        po::options_description config{ "Config" };

        config.add_options()
            ("web_root_path", po::value<std::string>(), "Web root path")
            ("server_port",   po::value<int>(),         "Server port")
            ("db_login",      po::value<std::string>(), "DB login")
            ("db_password",   po::value<std::string>(), "DB password")
            ("db_server",     po::value<std::string>(), "DB server")
            ("db_port",       po::value<int>(),         "DB port")
            ("db_name",       po::value<std::string>(), "DB name");

        po::variables_map vm{};
        po::store(po::parse_config_file(config_file, config), vm);
        po::notify(vm);

        config_file.close();

        // check config
        if (!vm.count("web_root_path"))
        {
            throw std::invalid_argument("Invalid config param web_root_path");
        }
        if (!vm.count("server_port"))
        {
            throw std::invalid_argument("Invalid config param server_port");
        }
        if (!vm.count("db_login"))
        {
            throw std::invalid_argument("Invalid config param db_login");
        }
        if (!vm.count("db_password"))
        {
            throw std::invalid_argument("Invalid config param db_password");
        }
        if (!vm.count("db_server"))
        {
            throw std::invalid_argument("Invalid config param db_server");
        }
        if (!vm.count("db_port"))
        {
            throw std::invalid_argument("Invalid config param db_port");
        }
        if (!vm.count("db_name"))
        {
            throw std::invalid_argument("Invalid config param db_name");
        }

        // setup and check params
        m_WebRootPath = vm["web_root_path"].as<std::string>();
        if (m_WebRootPath.empty())
        {
            throw std::invalid_argument("Invalid param web_root_path");
        }

        m_ServerPort = vm["server_port"].as<int>();
        if (!is_valid_port(m_ServerPort))
        {
            throw std::invalid_argument("Invalid param server_port");
        }

        m_DBLogin = vm["db_login"].as<std::string>();
        if (m_DBLogin.empty())
        {
            throw std::invalid_argument("Invalid param db_login");
        }

        m_DBPassword = vm["db_password"].as<std::string>();
        if (m_DBPassword.empty())
        {
            throw std::invalid_argument("Invalid param db_password");
        }

        m_DBServer = vm["db_server"].as<std::string>();
        if (m_DBServer.empty())
        {
            throw std::invalid_argument("Invalid param db_server");
        }

        m_DBPort = vm["db_port"].as<int>();
        if (!is_valid_port(m_DBPort))
        {
            throw std::invalid_argument("Invalid param db_port");
        }

        m_DBName = vm["db_name"].as<std::string>();
        if (m_DBName.empty())
        {
            throw std::invalid_argument("Invalid param db_name");
        }
    }
    
    std::string Config::GetWebRootPath() noexcept
    {
        return m_WebRootPath;
    }

    int Config::GetServerPort() noexcept
    {
        return m_ServerPort;
    }

    std::string Config::GetDBLogin() noexcept
    {
        return m_DBLogin;
    }

    std::string Config::GetDBPassword() noexcept
    {
        return m_DBPassword;
    }

    std::string Config::GetDBServer() noexcept
    {
        return m_DBServer;
    }

    int Config::GetDBPort() noexcept
    {
        return m_DBPort;
    }

    std::string Config::GetDBName() noexcept
    {
        return m_DBName;
    }
}
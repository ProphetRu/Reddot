#pragma once

#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Util/ServerApplication.h>
#include <thread>

namespace Server
{
    using Poco::Util::ServerApplication;

    /**
     * @brief A class for running an HTTPS server.
     */
    class ServerHTTPS final : public ServerApplication
    {
    public:
        /**
         * @brief Constructs a ServerHTTPS object with the specified key path, certificate path, port, max queued connections, and max threads.
         * @param key_path The path to the server's private key.
         * @param cert_path The path to the server's certificate.
         * @param port The port on which the server will listen.
         * @param max_queued The maximum number of queued connections.
         * @param max_threads The maximum number of threads to handle connections.
         */
        ServerHTTPS(std::string_view key_path, std::string_view cert_path, int port, int max_queued = 100, int max_threads = std::thread::hardware_concurrency());

        /**
         * @brief Default destructor.
         */
        virtual ~ServerHTTPS() noexcept override = default;

    protected:
        /**
         * @brief The main entry point for the HTTPS server application.
         * @param args The command-line arguments.
         * @return The exit code of the application.
         */
        virtual int main(const std::vector<std::string>& args) override;

    private:
        std::string m_KeyPath; /**< The path to the server's private key. */
        std::string m_CertPath; /**< The path to the server's certificate. */
        int m_Port{}; /**< The port on which the server will listen. */
        int m_MaxQueued{}; /**< The maximum number of queued connections. */
        int m_MaxThreads{}; /**< The maximum number of threads to handle connections. */
    };
}

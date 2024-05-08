#include "ServerHTTPS.h"
#include "../LoggerSafe.h"
#include "RequestHandlerFactoryHTTPS.h"
#include <Poco/Net/SecureServerSocket.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/PrivateKeyPassphraseHandler.h>
#include <Poco/Net/AcceptCertificateHandler.h>

namespace Server
{
    using Poco::Net::HTTPServer;
    using Poco::Net::HTTPServerParams;
    using Poco::Net::SSLManager;
    using Poco::Net::Context;
    using Poco::Net::AcceptCertificateHandler;

    ServerHTTPS::ServerHTTPS(std::string_view key_path, std::string_view cert_path, int port, int max_queued, int max_threads) :
		m_KeyPath{ key_path },
		m_CertPath{ cert_path },
	    m_Port{ port },
	    m_MaxQueued{ max_queued },
	    m_MaxThreads{ max_threads }
    {
    }

	int ServerHTTPS::main(const std::vector<std::string>&)
	{
        Log::LoggerSafe::LogInformation("Key file   : " + m_KeyPath);
        Log::LoggerSafe::LogInformation("Cert file  : " + m_CertPath);
        Log::LoggerSafe::LogInformation("Port       : " + std::to_string(m_Port));
        Log::LoggerSafe::LogInformation("Max queued : " + std::to_string(m_MaxQueued));
        Log::LoggerSafe::LogInformation("Max threads: " + std::to_string(m_MaxThreads));

        Poco::Net::initializeSSL();

        const Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> cert = new AcceptCertificateHandler(false);

        const auto context = new Context(
            Context::SERVER_USE, m_KeyPath, m_CertPath, "",
            Context::VERIFY_RELAXED, 9, false,
            "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH"
        );
        SSLManager::instance().initializeServer(nullptr, cert, context);

        const Poco::Net::SecureServerSocket svs(m_Port, 64, context);

        auto* params = new HTTPServerParams;
        params->setMaxQueued(m_MaxQueued);
        params->setMaxThreads(m_MaxThreads);

        HTTPServer server(new RequestHandlerFactoryHTTPS, svs, params);

        Log::LoggerSafe::LogInformation("Waiting connections...");
        server.start();

        waitForTerminationRequest();

        server.stop();
        return Application::EXIT_OK;
	}
}

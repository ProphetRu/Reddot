#pragma once

#include <Poco/Net/HTTPServer.h>

namespace Server
{
    using Poco::Net::HTTPRequestHandler;
    using Poco::Net::HTTPRequestHandlerFactory;
    using Poco::Net::HTTPServerRequest;

    /**
     * @brief A factory class for creating request handlers for HTTPS connections.
     */
    class RequestHandlerFactoryHTTPS final : public HTTPRequestHandlerFactory
    {
    public:
        /**
         * @brief Default destructor.
         */
        virtual ~RequestHandlerFactoryHTTPS() noexcept override = default;

        /**
         * @brief Creates a new request handler for the given HTTP server request.
         * @param request The HTTP server request.
         * @return A pointer to the created HTTP request handler.
         */
        virtual HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request) override;
    };
}

#pragma once

#include <Poco/Net/HTTPRequestHandler.h>

namespace Server
{
    using Poco::Net::HTTPRequestHandler;
    using Poco::Net::HTTPServerRequest;
    using Poco::Net::HTTPServerResponse;

    /**
     * @brief A class for handling HTTP requests in an HTTPS server.
     */
    class RequestHandlerHTTPS final : public HTTPRequestHandler
    {
    public:
        /**
         * @brief Default destructor.
         */
        virtual ~RequestHandlerHTTPS() noexcept override = default;

        /**
         * @brief Handles the HTTP request and generates an appropriate response.
         * @param request The HTTP request received.
         * @param response The HTTP response to be generated.
         */
        virtual void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override;
    };
}

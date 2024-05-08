#include "RequestHandlerHTTPS.h"
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/URI.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/Net/HTTPCookie.h>
#include "../LoggerSafe.h"
#include "../CMS/CMS.h"

namespace Server
{
    void RequestHandlerHTTPS::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
    {
        Log::LoggerSafe::LogInformation("Got new connection");
        CMS::CMSResponse cms_response;

        std::string session_hash;
        Poco::Net::NameValueCollection cookies{};
        request.getCookies(cookies);
        if (cookies.has("session_id"))
        {
            session_hash = cookies.get("session_id");
        }

        if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET)
        {
            const Poco::URI uri{ request.getURI() };

            cms_response = CMS::CMS::GetInstance().HandleGetRequestHTTP(session_hash, uri.getPath(), uri.getQueryParameters());
        }
        else if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST)
        {
            const Poco::URI uri{ request.getURI() };

            Poco::Net::HTMLForm form(request, request.stream());
            cms_response = CMS::CMS::GetInstance().HandlePostRequestHTTP(session_hash, uri.getPath(), form);

            if (cms_response.Status == CMS::ResponseStatus::HTTP_OK && !cms_response.SessionHash.empty())
            {
                Poco::Net::HTTPCookie cookie("session_id", cms_response.SessionHash);
                cookie.setPath("/");
                cookie.setHttpOnly(true);
                cookie.setSecure(true);

                response.addCookie(cookie);
            }
        }

        response.setStatus(static_cast<Poco::Net::HTTPResponse::HTTPStatus>(cms_response.Status));
        response.setContentType("text/html");
        auto& out = response.send();
        out << cms_response.Content;
    }
}

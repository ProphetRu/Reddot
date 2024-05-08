#pragma once

#include "WebPages/WebPageFactory.h"
#include "RequestHandlerManager.h"
#include "SessionManager.h"
#include <Poco/Net/HTMLForm.h>
#include "../WebSecurityFilters/WebSecurityFiltersManager.h"
#include <memory>

namespace CMS
{
    using POCOQueryParameters = std::vector<std::pair<std::string, std::string>>;

    /**
     * @brief Enum class representing the response status of the CMS.
     */
    enum class ResponseStatus
    {
        HTTP_OK        = 200,
        HTTP_FORBIDDEN = 403,
        HTTP_NOT_FOUND = 404,
    };

    /**
     * @brief Structure representing the response of the CMS.
     */
    struct CMSResponse final
    {
        ResponseStatus Status{ ResponseStatus::HTTP_OK }; /**< The status of the response. */
        std::string    SessionHash; /**< The session hash associated with the response. */
        std::string    Content; /**< The content of the response. */
    };

    /**
     * @brief The main CMS class responsible for handling requests and managing the system.
     */
    class CMS final
    {
    public:
        CMS(const CMS&) = delete;
        CMS& operator=(const CMS&) = delete;

        CMS(CMS&&) = delete;
        CMS& operator=(CMS&&) = delete;

        /**
         * @brief Gets the singleton instance of the CMS.
         * @return The CMS instance.
         */
        static CMS& GetInstance();
        
        /**
         * @brief Handles a GET HTTP request.
         * @param session_hash The session hash.
         * @param uri The URI of the request.
         * @param params The query parameters.
         * @return The response to the request.
         */
        [[nodiscard]] CMSResponse HandleGetRequestHTTP(const std::string& session_hash, const std::string& uri, const POCOQueryParameters& params) const;

        /**
         * @brief Handles a POST HTTP request.
         * @param session_hash The session hash.
         * @param uri The URI of the request.
         * @param params The form parameters.
         * @return The response to the request.
         */
        [[nodiscard]] CMSResponse HandlePostRequestHTTP(const std::string& session_hash, const std::string& uri, const Poco::Net::HTMLForm& params) const;

    private:
        CMS(); /**< Private constructor for singleton pattern. */
        ~CMS() = default;

    private:
        std::unique_ptr<RequestHandlers::RequestHandlerManager> m_RequestHandlerManager; /**< The request handler manager. */
        std::unique_ptr<Session::SessionManager>  m_SessionManager; /**< The session manager. */
        std::unique_ptr<WebPages::WebPageFactory> m_WebPageFactory; /**< The web page factory. */
        std::unique_ptr<Security::WebSecurityFiltersManager> m_WebSecurityFiltersManager; /**< The web security filters manager. */
    };
}

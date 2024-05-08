#pragma once

#include "WebPageNotFound.h"
#include "WebPageForbidden.h"
#include "WebPageRegistration.h"
#include "WebPageLogin.h"
#include "WebPageAccount.h"
#include "WebPagePost.h"
#include "WebPageIndex.h"
#include "../../DB/Post.h"
#include <memory>
#include <unordered_map>

namespace CMS::WebPages
{
    /**
     * @brief A class for creating and managing web pages.
     */
    class WebPageFactory final
    {
    public:
        /**
         * @brief Constructs a WebPageFactory object with the specified web root path.
         * @param web_root_path The path of the web root.
         */
        explicit WebPageFactory(const std::string& web_root_path);

        /**
         * @brief Retrieves the ID of the web page with the specified name.
         * @param name The name of the web page.
         * @return The ID of the web page.
         */
        [[nodiscard]] WebPageID GetWebPageID(const std::string& name) const noexcept;

        /**
         * @brief Creates a new instance of the WebPageNotFound class.
         * @return A new instance of the WebPageNotFound class.
         */
        [[nodiscard]] std::unique_ptr<WebPageNotFound> CreateWebPageNotFound();

        /**
         * @brief Creates a new instance of the WebPageForbidden class.
         * @return A new instance of the WebPageForbidden class.
         */
        [[nodiscard]] std::unique_ptr<WebPageForbidden> CreateWebPageForbidden();

        /**
         * @brief Creates a new instance of the WebPageRegistration class with the specified state.
         * @param state The state of the registration.
         * @return A new instance of the WebPageRegistration class.
         */
        [[nodiscard]] std::unique_ptr<WebPageRegistration> CreateWebPageRegistration(RegistrationState state);

        /**
         * @brief Creates a new instance of the WebPageLogin class with the specified state.
         * @param state The state of the login.
         * @return A new instance of the WebPageLogin class.
         */
        [[nodiscard]] std::unique_ptr<WebPageLogin> CreateWebPageLogin(LoginState state);

        /**
         * @brief Creates a new instance of the WebPageAccount class with the specified login and role.
         * @param login The login of the account.
         * @param role The role of the account.
         * @return A new instance of the WebPageAccount class.
         */
        [[nodiscard]] std::unique_ptr<WebPageAccount> CreateWebPageAccount(std::string_view login, std::string_view role);

        /**
         * @brief Creates a new instance of the WebPagePost class with the specified login and post.
         * @param login The login of the post.
         * @param post The post to create.
         * @return A new instance of the WebPagePost class.
         */
        [[nodiscard]] std::unique_ptr<WebPagePost> CreateWebPagePost(const std::string& login, const DB::Post& post);

        /**
         * @brief Creates a new instance of the WebPageIndex class with the specified login and posts.
         * @param login The login of the index.
         * @param posts The posts to create.
         * @return A new instance of the WebPageIndex class.
         */
        [[nodiscard]] std::unique_ptr<WebPageIndex> CreateWebPageIndex(const std::string& login, const DB::Posts& posts);

    private:
        std::unordered_map<WebPageID, std::unique_ptr<IWebPage>> m_WebPages; /**< Map of web page IDs to web pages. */
    };
}

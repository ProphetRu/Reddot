#pragma once

#include "IWebPage.h"

namespace CMS::WebPages
{
    /**
     * @brief A class representing a user account web page.
     */
    class WebPageAccount final : public IWebPage
    {
    public:
        /**
         * @brief Constructs a WebPageAccount object with the specified path.
         * @param path The path of the web page.
         */
        explicit WebPageAccount(const std::string& path);

        /**
         * @brief Default destructor.
         */
        virtual ~WebPageAccount() noexcept override = default;

        /**
         * @brief Sets the login for the user account.
         * @param login The user's login.
         */
        void SetLogin(std::string_view login) noexcept;

        /**
         * @brief Sets the role for the user account.
         * @param role The user's role.
         */
        void SetRole(std::string_view role) noexcept;

        /**
         * @brief Creates a clone of the WebPageAccount object.
         * @return A pointer to the cloned WebPageAccount object.
         */
        [[nodiscard]] virtual IWebPage* Clone() noexcept override;

        /**
         * @brief Generates the HTML content for the user account web page.
         * @return The generated HTML content.
         */
        [[nodiscard]] virtual std::string GenerateWebPage() override;

    private:
        std::string m_Login; /**< The user's login. */
        std::string m_Role; /**< The user's role. */
    };
}

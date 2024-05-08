#pragma once

#include "IWebPage.h"
#include "LoginState.h"

namespace CMS::WebPages
{
    /**
     * @brief Represents a web page for user login.
     */
    class WebPageLogin final : public IWebPage
    {
    public:
        /**
         * @brief Constructs a WebPageLogin object with the specified path.
         * @param path The path of the web page.
         */
        explicit WebPageLogin(const std::string& path);

        /**
         * @brief Default destructor.
         */
        virtual ~WebPageLogin() noexcept override = default;

        /**
         * @brief Sets the login state for the web page.
         * @param state The login state to set.
         */
        void SetLoginState(LoginState state) noexcept;

        /**
         * @brief Creates a clone of the WebPageLogin object.
         * @return A new instance of the WebPageLogin object.
         */
        [[nodiscard]] virtual IWebPage* Clone() noexcept override;

        /**
         * @brief Generates the content of the web page.
         * @return The generated web page content.
         */
        [[nodiscard]] virtual std::string GenerateWebPage() override;

    private:
        LoginState m_State{ LoginState::None }; /**< The login state for the web page. */
    };
}

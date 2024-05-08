#pragma once

#include "IWebPage.h"
#include "RegistrationState.h"

namespace CMS::WebPages
{
    /**
     * @brief Represents a web page for user registration.
     */
    class WebPageRegistration final : public IWebPage
    {
    public:
        /**
         * @brief Constructs a WebPageRegistration object with the specified path.
         * @param path The path of the web page.
         */
        explicit WebPageRegistration(const std::string& path);

        /**
         * @brief Default destructor.
         */
        virtual ~WebPageRegistration() noexcept override = default;

        /**
         * @brief Sets the registration state for the web page.
         * @param state The registration state to set.
         */
        void SetRegistrationState(RegistrationState state) noexcept;

        /**
         * @brief Creates a clone of the WebPageRegistration object.
         * @return A new instance of the WebPageRegistration object.
         */
        [[nodiscard]] virtual IWebPage* Clone() noexcept override;

        /**
         * @brief Generates the content of the web page.
         * @return The generated web page content.
         */
        [[nodiscard]] virtual std::string GenerateWebPage() override;

    private:
        RegistrationState m_State{ RegistrationState::None }; /**< The registration state for the web page. */
    };
}

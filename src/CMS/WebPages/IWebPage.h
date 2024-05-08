#pragma once

#include <string>

namespace CMS::WebPages
{
    /**
     * @brief An interface class for web pages in the CMS.
     */
    class IWebPage
    {
    public:
        /**
         * @brief Constructs an IWebPage object with the specified path and name.
         * @param path The path of the web page.
         * @param name The name of the web page.
         */
        explicit IWebPage(const std::string& path, const std::string& name);

        /**
         * @brief Virtual destructor.
         */
        virtual ~IWebPage() noexcept = default;

        /**
         * @brief Sets the login for the web page.
         * @param login The user's login.
         */
        void SetLogin(const std::string& login) noexcept;

        /**
         * @brief Retrieves the name of the web page.
         * @return The name of the web page.
         */
        [[nodiscard]] std::string GetName() const noexcept;

        /**
         * @brief Creates a clone of the web page.
         * @return A pointer to the cloned web page.
         */
        [[nodiscard]] virtual IWebPage* Clone() noexcept = 0;

        /**
         * @brief Generates the HTML content for the web page.
         * @return The generated HTML content.
         */
        [[nodiscard]] virtual std::string GenerateWebPage() = 0;

    protected:
        /**
         * @brief Finds and replaces a placeholder with a value in the web page content.
         * @param placeholder The placeholder to find.
         * @param value The value to replace the placeholder with.
         */
        void FindAndReplace(std::string_view placeholder, std::string_view value);

    protected:
        std::string m_Login; /**< The user's login. */
        std::string m_Name; /**< The name of the web page. */
        std::string m_Content; /**< The content of the web page. */
    };
}

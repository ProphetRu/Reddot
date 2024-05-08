#pragma once

#include "IWebPage.h"

namespace CMS::WebPages
{
    /**
     * @brief A class representing a web page that indicates a "Not Found" error.
     */
    class WebPageNotFound final : public IWebPage
    {
    public:
        /**
         * @brief Constructs a WebPageNotFound object with the specified path.
         * @param path The path of the web page.
         */
        explicit WebPageNotFound(const std::string& path);

        /**
         * @brief Default destructor.
         */
        virtual ~WebPageNotFound() noexcept override = default;

        /**
         * @brief Creates a clone of the WebPageNotFound object.
         * @return A pointer to the cloned WebPageNotFound object.
         */
        [[nodiscard]] virtual IWebPage* Clone() noexcept override;

        /**
         * @brief Generates the HTML content for the web page.
         * @return The generated HTML content.
         */
        [[nodiscard]] virtual std::string GenerateWebPage() override;
    };
}

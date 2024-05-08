#pragma once

#include "IWebPage.h"

namespace CMS::WebPages
{
    /**
     * @brief A class representing a web page that indicates a "Forbidden" error.
     */
    class WebPageForbidden final : public IWebPage
    {
    public:
        /**
         * @brief Constructs a WebPageForbidden object with the specified path.
         * @param path The path of the web page.
         */
        explicit WebPageForbidden(const std::string& path);

        /**
         * @brief Default destructor.
         */
        virtual ~WebPageForbidden() noexcept override = default;

        /**
         * @brief Creates a clone of the WebPageForbidden object.
         * @return A pointer to the cloned WebPageForbidden object.
         */
        [[nodiscard]] virtual IWebPage* Clone() noexcept override;

        /**
         * @brief Generates the HTML content for the web page.
         * @return The generated HTML content.
         */
        [[nodiscard]] virtual std::string GenerateWebPage() override;
    };
}

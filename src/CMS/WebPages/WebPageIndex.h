#pragma once

#include "IWebPage.h"
#include "../../DB/Post.h"

namespace CMS::WebPages
{
    /**
     * @brief Represents a web page for displaying an index page with posts.
     */
    class WebPageIndex final : public IWebPage
    {
    public:
        /**
         * @brief Constructs a WebPageIndex object with the specified path.
         * @param path The path of the web page.
         */
        explicit WebPageIndex(const std::string& path);

        /**
         * @brief Default destructor.
         */
        virtual ~WebPageIndex() noexcept override = default;

        /**
         * @brief Sets the posts to be displayed on the web page.
         * @param posts The posts to set.
         */
        void SetPosts(const DB::Posts& posts) noexcept;

        /**
         * @brief Creates a clone of the WebPageIndex object.
         * @return A new instance of the WebPageIndex object.
         */
        [[nodiscard]] virtual IWebPage* Clone() noexcept override;

        /**
         * @brief Generates the content of the web page.
         * @return The generated web page content.
         */
        [[nodiscard]] virtual std::string GenerateWebPage() override;

    private:
        DB::Posts m_Posts; /**< The posts to be displayed on the web page. */
    };
}

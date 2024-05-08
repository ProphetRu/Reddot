#pragma once

#include "IWebPage.h"
#include "../../DB/Post.h"

namespace CMS::WebPages
{
    /**
     * @brief Represents a web page for displaying a single post.
     */
    class WebPagePost final : public IWebPage
    {
    public:
        /**
         * @brief Constructs a WebPagePost object with the specified path.
         * @param path The path of the web page.
         */
        explicit WebPagePost(const std::string& path);

        /**
         * @brief Default destructor.
         */
        virtual ~WebPagePost() noexcept override = default;

        /**
         * @brief Sets the post to be displayed on the web page.
         * @param post The post to set.
         */
        void SetPost(const DB::Post& post) noexcept;

        /**
         * @brief Creates a clone of the WebPagePost object.
         * @return A new instance of the WebPagePost object.
         */
        [[nodiscard]] virtual IWebPage* Clone() noexcept override;

        /**
         * @brief Generates the content of the web page.
         * @return The generated web page content.
         */
        [[nodiscard]] virtual std::string GenerateWebPage() override;

    private:
        DB::Post m_Post; /**< The post to be displayed on the web page. */
    };
}

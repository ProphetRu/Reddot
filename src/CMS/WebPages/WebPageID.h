#pragma once

namespace CMS::WebPages
{
    /**
     * @brief Enum class representing the different types of web pages.
     */
    enum class WebPageID
    {
        /**
         * @brief The web page is not found.
         */
        NotFound = 0,

        /**
         * @brief The web page is forbidden.
         */
        Forbidden,

        /**
         * @brief The web page is for user registration.
         */
        Registration,

        /**
         * @brief The web page is for user login.
         */
        Login,

        /**
         * @brief The web page is for user account.
         */
        Account,

        /**
         * @brief The web page is for a single post.
         */
        Post,

        /**
         * @brief The web page is for an index of posts.
         */
        Index,
    };
}

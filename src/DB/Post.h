#pragma once

#include <string>
#include <vector>

namespace DB
{
    /**
     * @brief A struct representing a post in the database.
     */
    struct Post final
    {
        int ID{}; /**< The unique identifier of the post. */
        std::string Login; /**< The login of the user who created the post. */
        std::string Caption; /**< The caption of the post. */
        std::string Body; /**< The body content of the post. */

        /**
         * @brief Checks if the post is valid.
         * @return True if the post is valid, false otherwise.
         */
        [[nodiscard]] bool IsValid() const noexcept
        {
            return (!Login.empty() && !Caption.empty() && !Body.empty());
        }
    };

    /**
     * @brief A collection of posts.
     */
    using Posts = std::vector<Post>;
}

#pragma once

namespace CMS::WebPages
{
    /**
     * @brief Enum class representing the login state of a user.
     */
    enum class LoginState
    {
        /**
         * @brief The login state is none.
         */
        None = 0,

        /**
         * @brief The login state is OK.
         */
        OK,

        /**
         * @brief The login state is failed.
         */
        Failed,
    };
}

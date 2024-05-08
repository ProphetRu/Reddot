#pragma once

namespace CMS::WebPages
{
    /**
     * @brief Enum class representing the registration state of a user.
     */
    enum class RegistrationState
    {
        /**
         * @brief The registration state is none.
         */
        None = 0,

        /**
         * @brief The registration state is failed.
         */
        Failed,

        /**
         * @brief The registration state is OK.
         */
        OK,
    };
}

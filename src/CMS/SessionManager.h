#pragma once

#include <string>
#include <unordered_map>

namespace CMS::Session
{
    /**
     * @brief A class for managing user sessions.
     */
    class SessionManager final
    {
    public:
        /**
         * @brief Adds a new session for the specified login and hash.
         * @param login The login associated with the session.
         * @param hash The hash representing the session.
         */
        void AddSession(const std::string& login, const std::string& hash);

        /**
         * @brief Checks if the session with the given hash is active.
         * @param hash The hash of the session to check.
         * @return True if the session is active, false otherwise.
         */
        [[nodiscard]] bool IsActiveSession(const std::string& hash) const;

        /**
         * @brief Retrieves the login associated with the session hash.
         * @param hash The hash of the session.
         * @return The login associated with the session.
         */
        [[nodiscard]] std::string GetLogin(const std::string& hash);

        /**
         * @brief Deletes the session with the specified hash.
         * @param hash The hash of the session to delete.
         */
        void DeleteSession(const std::string& hash);

    private:
        std::unordered_map<std::string, std::string> m_Sessions; /**< Map of session hashes to logins. */
    };
}

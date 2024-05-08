#pragma once

#include <string>

namespace Config
{
    /**
     * @brief A class for managing the application configuration.
     */
    class Config final
    {
    public:
        /**
         * @brief Initializes the configuration with the specified configuration file.
         * @param config_file_name The name of the configuration file.
         */
        static void Init(std::string_view config_file_name);

        /**
         * @brief Retrieves the web root path.
         * @return The web root path.
         */
        [[nodiscard]] static std::string GetWebRootPath() noexcept;

        /**
         * @brief Retrieves the server port.
         * @return The server port.
         */
        [[nodiscard]] static int GetServerPort() noexcept;

        /**
         * @brief Retrieves the database login.
         * @return The database login.
         */
        [[nodiscard]] static std::string GetDBLogin() noexcept;

        /**
         * @brief Retrieves the database password.
         * @return The database password.
         */
        [[nodiscard]] static std::string GetDBPassword() noexcept;

        /**
         * @brief Retrieves the database server.
         * @return The database server.
         */
        [[nodiscard]] static std::string GetDBServer() noexcept;

        /**
         * @brief Retrieves the database port.
         * @return The database port.
         */
        [[nodiscard]] static int GetDBPort() noexcept;

        /**
         * @brief Retrieves the database name.
         * @return The database name.
         */
        [[nodiscard]] static std::string GetDBName() noexcept;

    private:
        static inline std::string m_WebRootPath; /**< The web root path. */
        static inline int m_ServerPort{}; /**< The server port. */
        static inline std::string m_DBLogin; /**< The database login. */
        static inline std::string m_DBPassword; /**< The database password. */
        static inline std::string m_DBServer; /**< The database server. */
        static inline int m_DBPort{}; /**< The database port. */
        static inline std::string m_DBName; /**< The database name. */
    };
}

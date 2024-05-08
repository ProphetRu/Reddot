#pragma once

#include <fstream>
#include <memory>
#include <mutex>

namespace Log
{
    /**
     * @brief Enum class representing the type of log message.
     */
    enum class LogType
    {
        /**
         * @brief Information log type.
         */
        Information = 0,

#ifdef _DEBUG
        /**
         * @brief Debug log type (only available in debug mode).
         */
        Debug,
#endif // _DEBUG

        /**
         * @brief Warning log type.
         */
        Warning,

        /**
         * @brief Error log type.
         */
        Error,
    };

    /**
     * @brief A class for thread-safe logging operations.
     */
    class LoggerSafe final
    {
    public:
        /**
         * @brief Initializes the logger with the specified log file name.
         * @param log_file_name The name of the log file.
         */
        static void Init(std::string_view log_file_name);

        /**
         * @brief Cleans up and closes the log file.
         */
        static void Cleanup() noexcept;

        /**
         * @brief Logs an information message.
         * @param log The information message to log.
         */
        static void LogInformation(std::string_view log);

#ifdef _DEBUG
        /**
         * @brief Logs a debug message (only available in debug mode).
         * @param log The debug message to log.
         */
        static void LogDebug(std::string_view log);
#endif // _DEBUG

        /**
         * @brief Logs a warning message.
         * @param log The warning message to log.
         */
        static void LogWarning(std::string_view log);

        /**
         * @brief Logs an error message.
         * @param log The error message to log.
         */
        static void LogError(std::string_view log);

    private:
        /**
         * @brief Logs a message of the specified type.
         * @param type The type of the log message.
         * @param log The message to log.
         */
        static void Log(LogType type, std::string_view log);

    private:
        inline static std::ofstream m_LogFile{}; /**< The log file stream. */
        inline static std::mutex    m_Mutex;     /**< Mutex for thread-safe logging. */
    };
}

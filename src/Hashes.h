#pragma once

#include <string>

namespace Hashes
{
    /**
     * @brief A class for generating MD5 and SHA-1 hashes.
     */
    class Hashes final
    {
    public:
        /**
         * @brief Calculates the MD5 hash of the input string.
         * @param str The input string to hash.
         * @return The MD5 hash of the input string.
         */
        [[nodiscard]] static std::string GetMD5(std::string_view str);

        /**
         * @brief Calculates the SHA-1 hash of the input string.
         * @param str The input string to hash.
         * @return The SHA-1 hash of the input string.
         */
        [[nodiscard]] static std::string GetSHA1(std::string_view str);
    };
}

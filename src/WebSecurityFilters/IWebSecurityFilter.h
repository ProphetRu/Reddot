#pragma once

#include <string>

namespace Security
{
    /**
     * @brief An interface class for web security filters.
     */
    class IWebSecurityFilter
    {
    public:
        /**
         * @brief Constructs an IWebSecurityFilter object with the specified filter.
         * @param filter The filter to apply.
         */
        explicit IWebSecurityFilter(std::string_view filter);

        /**
         * @brief Virtual destructor.
         */
        virtual ~IWebSecurityFilter() noexcept = default;

        /**
         * @brief Checks if the content contains any potentially dangerous elements.
         * @param content The content to check.
         * @return True if the content is considered dangerous, false otherwise.
         */
        [[nodiscard]] bool IsDanger(std::string_view content) const;

    protected:
        const std::string m_Filter; /**< The filter applied by the security filter. */
    };
}

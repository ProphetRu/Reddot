#pragma once

#include "IWebSecurityFilter.h"
#include <memory>
#include <vector>

namespace Security
{
    /**
     * @brief A class for managing web security filters.
     */
    class WebSecurityFiltersManager final
    {
    public:
        /**
         * @brief Constructs a WebSecurityFiltersManager object.
         */
        WebSecurityFiltersManager();

        /**
         * @brief Checks the given content against all registered web security filters.
         * @param content The content to check.
         */
        void Check(std::string_view content) const;

    private:
        std::vector<std::unique_ptr<IWebSecurityFilter>> m_Filters; /**< The collection of web security filters. */
    };
}

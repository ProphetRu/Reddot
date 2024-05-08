#pragma once

#include "IWebSecurityFilter.h"

namespace Security
{
    /**
     * @brief A class for filtering web content based on specified paths.
     */
    class FilterPaths final : public IWebSecurityFilter
    {
    public:
        /**
         * @brief Constructs a FilterPaths object with the specified path filter.
         * @param filter The path filter to apply.
         */
        explicit FilterPaths(std::string_view filter);

        /**
         * @brief Default destructor.
         */
        virtual ~FilterPaths() noexcept override = default;
    };
}

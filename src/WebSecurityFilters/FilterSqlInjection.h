#pragma once

#include "IWebSecurityFilter.h"

namespace Security
{
    /**
     * @brief A class for filtering web content to prevent SQL injection attacks.
     */
    class FilterSqlInjection final : public IWebSecurityFilter
    {
    public:
        /**
         * @brief Constructs a FilterSqlInjection object with the specified SQL injection filter.
         * @param filter The SQL injection filter to apply.
         */
        explicit FilterSqlInjection(std::string_view filter);

        /**
         * @brief Default destructor.
         */
        virtual ~FilterSqlInjection() noexcept override = default;
    };
}

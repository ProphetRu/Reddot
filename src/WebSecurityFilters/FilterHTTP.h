#pragma once

#include "IWebSecurityFilter.h"

namespace Security
{
    /**
     * @brief A class for filtering web content based on HTTP headers.
     */
    class FilterHTTP final : public IWebSecurityFilter
    {
    public:
        /**
         * @brief Constructs a FilterHTTP object with the specified HTTP filter.
         * @param filter The HTTP filter to apply.
         */
        explicit FilterHTTP(std::string_view filter);

        /**
         * @brief Default destructor.
         */
        virtual ~FilterHTTP() noexcept override = default;
    };
}

#pragma once

#include "IWebSecurityFilter.h"

namespace Security
{
    /**
     * @brief A class for filtering web content to prevent cross-site scripting (XSS) attacks.
     */
    class FilterXSS final : public IWebSecurityFilter
    {
    public:
        /**
         * @brief Constructs a FilterXSS object with the specified XSS filter.
         * @param filter The XSS filter to apply.
         */
        explicit FilterXSS(std::string_view filter);

        /**
         * @brief Default destructor.
         */
        virtual ~FilterXSS() noexcept override = default;
    };
}

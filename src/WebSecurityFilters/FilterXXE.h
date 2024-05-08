#pragma once

#include "IWebSecurityFilter.h"

namespace Security
{
    /**
     * @brief A class for filtering web content to prevent XML External Entity (XXE) attacks.
     */
    class FilterXXE final : public IWebSecurityFilter
    {
    public:
        /**
         * @brief Constructs a FilterXXE object with the specified XXE filter.
         * @param filter The XXE filter to apply.
         */
        explicit FilterXXE(std::string_view filter);

        /**
         * @brief Default destructor.
         */
        virtual ~FilterXXE() noexcept override = default;
    };
}

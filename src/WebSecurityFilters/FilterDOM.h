#pragma once

#include "IWebSecurityFilter.h"

namespace Security
{
    /**
     * @brief A class for filtering web content based on a Document Object Model (DOM) filter.
     */
    class FilterDOM final : public IWebSecurityFilter
    {
    public:
        /**
         * @brief Constructs a FilterDOM object with the specified DOM filter.
         * @param filter The DOM filter to apply.
         */
        explicit FilterDOM(std::string_view filter);

        /**
         * @brief Default destructor.
         */
        virtual ~FilterDOM() noexcept override = default;
    };
}

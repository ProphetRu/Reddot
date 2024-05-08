#include "IWebSecurityFilter.h"
#include <stdexcept>
#include <algorithm>

namespace Security
{
	IWebSecurityFilter::IWebSecurityFilter(std::string_view filter) :
		m_Filter{ filter }
	{
		if (m_Filter.empty())
		{
			throw std::invalid_argument("Filter is empty");
		}
	}

	bool IWebSecurityFilter::IsDanger(std::string_view content) const
	{
		if (content.empty())
		{
			throw std::invalid_argument("Content to filter is empty");
		}

		return std::ranges::find_first_of(content, m_Filter) != end(content);
	}
}
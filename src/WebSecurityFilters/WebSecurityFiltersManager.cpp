#include "WebSecurityFiltersManager.h"
#include "FilterDOM.h"
#include "FilterHTTP.h"
#include "FilterPaths.h"
#include "FilterSqlInjection.h"
#include "FilterXSS.h"
#include "FilterXXE.h"
#include <stdexcept>

namespace Security
{
	WebSecurityFiltersManager::WebSecurityFiltersManager()
	{
		m_Filters.emplace_back(std::make_unique<FilterDOM>(R"(<>&"'/()#)"));
		m_Filters.emplace_back(std::make_unique<FilterHTTP>("\r\n"));
		m_Filters.emplace_back(std::make_unique<FilterPaths>(R"(\/)"));
		m_Filters.emplace_back(std::make_unique<FilterSqlInjection>(R"('";{}[]$-`())"));
		m_Filters.emplace_back(std::make_unique<FilterXSS>(R"(<>&"'/()#)"));
		m_Filters.emplace_back(std::make_unique<FilterXXE>(R"(<![]&%)"));
	}

	void WebSecurityFiltersManager::Check(std::string_view content) const
	{
		if (content.empty())
		{
			throw std::invalid_argument("Content to web security filters is empty");
		}

		for (const auto& filter : m_Filters)
		{
			if (filter->IsDanger(content))
			{
				throw std::runtime_error("Detected danger content");
			}
		}
	}
}

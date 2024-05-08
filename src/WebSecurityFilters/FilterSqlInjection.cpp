#include "FilterSqlInjection.h"

namespace Security
{
	FilterSqlInjection::FilterSqlInjection(std::string_view filter) :
		IWebSecurityFilter{ filter }
	{
	}
}

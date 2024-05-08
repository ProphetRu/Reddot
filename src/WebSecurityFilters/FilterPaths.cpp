#include "FilterPaths.h"

namespace Security
{
	FilterPaths::FilterPaths(std::string_view filter) :
		IWebSecurityFilter{ filter }
	{
	}
}

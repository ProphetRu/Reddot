#include "FilterHTTP.h"

namespace Security
{
	FilterHTTP::FilterHTTP(std::string_view filter) :
		IWebSecurityFilter{ filter }
	{
	}
}

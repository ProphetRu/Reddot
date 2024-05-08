#include "FilterXSS.h"

namespace Security
{
	FilterXSS::FilterXSS(std::string_view filter) :
		IWebSecurityFilter{ filter }
	{
	}
}

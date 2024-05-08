#include "FilterDOM.h"

namespace Security
{
	FilterDOM::FilterDOM(std::string_view filter) :
		IWebSecurityFilter{ filter }
	{
	}
}

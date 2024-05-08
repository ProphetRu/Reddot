#include "FilterXXE.h"

namespace Security
{
	FilterXXE::FilterXXE(std::string_view filter) :
		IWebSecurityFilter{ filter }
	{
	}
}

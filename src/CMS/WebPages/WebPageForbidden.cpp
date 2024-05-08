#include "WebPageForbidden.h"

namespace CMS::WebPages
{
	WebPageForbidden::WebPageForbidden(const std::string& path) :
		IWebPage{ path, "/403.html" }
	{
	}

	IWebPage* WebPageForbidden::Clone() noexcept
	{
		return this;
	}

	std::string WebPageForbidden::GenerateWebPage()
	{
		return m_Content;
	}
}

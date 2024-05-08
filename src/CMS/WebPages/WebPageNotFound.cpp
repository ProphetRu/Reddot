#include "WebPageNotFound.h"

namespace CMS::WebPages
{
	WebPageNotFound::WebPageNotFound(const std::string& path) :
		IWebPage{ path, "/404.html" }
	{
	}

	IWebPage* WebPageNotFound::Clone() noexcept
	{
		return this;
	}

	std::string WebPageNotFound::GenerateWebPage()
	{
		return m_Content;
	}
}

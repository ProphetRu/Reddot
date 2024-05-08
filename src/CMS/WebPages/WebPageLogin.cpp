#include "WebPageLogin.h"
#include <stdexcept>

namespace CMS::WebPages
{
    WebPageLogin::WebPageLogin(const std::string& path) :
        IWebPage{ path, "/login.html" }
    {
    }

    void WebPageLogin::SetLoginState(LoginState state) noexcept
    {
        m_State = state;
    }

    IWebPage* WebPageLogin::Clone() noexcept
    {
        return this;
    }

    std::string WebPageLogin::GenerateWebPage()
    {
        static constexpr auto placeholder_login_status{ "%PLACEHOLDER_LOGIN_STATUS%" };

        if (m_State == LoginState::None)
        {
            FindAndReplace(placeholder_login_status, "Login");
        }
        else if (m_State == LoginState::OK)
        {
            FindAndReplace(placeholder_login_status, "<font color=\"#00AA00\">Login OK</font>");
        }
        else if (m_State == LoginState::Failed)
        {
            FindAndReplace(placeholder_login_status, "<font color=\"#FF0000\">Login failed</font>");
        }

        return m_Content;
    }
}

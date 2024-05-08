#include "WebPageAccount.h"
#include <stdexcept>

namespace CMS::WebPages
{
    WebPageAccount::WebPageAccount(const std::string& path) :
        IWebPage{ path, "/account.html" }
    {
    }

    void WebPageAccount::SetLogin(std::string_view login) noexcept
    {
        m_Login = login;
    }
    void WebPageAccount::SetRole(std::string_view role) noexcept
    {
        m_Role = role;
    }

    IWebPage* WebPageAccount::Clone() noexcept
    {
        return this;
    }

    std::string WebPageAccount::GenerateWebPage()
    {
        static constexpr auto placeholder_user_login{ "%PLACEHOLDER_USER_LOGIN%" };
        static constexpr auto placeholder_user_role { "%PLACEHOLDER_USER_ROLE%"  };

        FindAndReplace(placeholder_user_login, m_Login);
        FindAndReplace(placeholder_user_role,  m_Role);

        return m_Content;
    }
}

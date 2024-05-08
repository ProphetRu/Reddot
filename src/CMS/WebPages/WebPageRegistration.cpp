#include "WebPageRegistration.h"
#include <stdexcept>

namespace CMS::WebPages
{
    WebPageRegistration::WebPageRegistration(const std::string& path) :
        IWebPage{ path, "/reg.html" }
    {
    }

    void WebPageRegistration::SetRegistrationState(RegistrationState state) noexcept
    {
        m_State = state;
    }

    IWebPage* WebPageRegistration::Clone() noexcept
    {
        return this;
    }

    std::string WebPageRegistration::GenerateWebPage()
    {
        static constexpr auto placeholder_reg_status{ "%PLACEHOLDER_REG_STATUS%" };

        if (m_State == RegistrationState::None)
        {
            FindAndReplace(placeholder_reg_status, "Registration");
        }
        else if (m_State == RegistrationState::OK)
        {
            FindAndReplace(placeholder_reg_status, "<font color=\"#00AA00\">Registration OK</font>");
        }
        else if (m_State == RegistrationState::Failed)
        {
            FindAndReplace(placeholder_reg_status, "<font color=\"#FF0000\">Registration failed</font>");
        }

        return m_Content;
    }
}

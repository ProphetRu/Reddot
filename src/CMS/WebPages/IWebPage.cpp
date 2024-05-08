#include "IWebPage.h"
#include "../../Config.h"
#include <stdexcept>
#include <fstream>

namespace CMS::WebPages
{
    IWebPage::IWebPage(const std::string& path, const std::string& name) :
		m_Name{ name }
    {
        if (path.empty() || m_Name.empty())
        {
            throw std::invalid_argument("Web page path is empty");
        }

        const auto complete_path{ path + m_Name };
        std::ifstream file(complete_path.data());
        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open web page file");
        }

        m_Content.assign((std::istreambuf_iterator(file)), std::istreambuf_iterator<char>());
        file.close();

        if (m_Content.empty())
        {
            throw std::runtime_error("Can't read web page file");
        }
    }

    void IWebPage::SetLogin(const std::string& login) noexcept
    {
        m_Login = login;
    }

    std::string IWebPage::GetName() const noexcept
    {
        return m_Name;
    }

    void IWebPage::FindAndReplace(std::string_view placeholder, std::string_view value)
    {
        const auto pos{ m_Content.find(placeholder) };
        if (pos == std::string::npos)
        {
            throw std::runtime_error("Can't find placeholder for the web-page");
        }

        m_Content.replace(pos, placeholder.size(), value);
    }
}

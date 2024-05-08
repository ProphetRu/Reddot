#include "WebPageIndex.h"
#include <stdexcept>

namespace CMS::WebPages
{
    WebPageIndex::WebPageIndex(const std::string& path) :
        IWebPage{ path, "/index.html" }
    {
    }

    void WebPageIndex::SetPosts(const DB::Posts& posts) noexcept
    {
        m_Posts = posts;
    }

    IWebPage* WebPageIndex::Clone() noexcept
    {
        return this;
    }

    std::string WebPageIndex::GenerateWebPage()
    {
        static constexpr auto placeholder_index_username{ "%PLACEHOLDER_INDEX_USERNAME%"     };
        static constexpr auto placeholder_index_reg     { "%PLACEHOLDER_INDEX_REGISTRATION%" };
        static constexpr auto placeholder_index_login   { "%PLACEHOLDER_INDEX_LOGIN%"        };
        static constexpr auto placeholder_index_new_post{ "%PLACEHOLDER_INDEX_NEW_POST%"     };

        if (m_Login.empty())
        {
            FindAndReplace(placeholder_index_username, "Guest");
            FindAndReplace(placeholder_index_reg,      R"(<a href="reg.html" class="register-button">Registration</a>)");
            FindAndReplace(placeholder_index_login,    R"(<a href="login.html" class="login-button">Login</a>)");
            FindAndReplace(placeholder_index_new_post, "");
        }
        else
        {
            FindAndReplace(placeholder_index_username, m_Login);
            FindAndReplace(placeholder_index_reg,      R"(<a href="account.html" class="register-button">Account</a>)");
            FindAndReplace(placeholder_index_login,    R"(<a href="index.html?cmd=logout" class="logout-button">Logout</a>)");
            FindAndReplace(placeholder_index_new_post, R"(<a href="post.html" class="new-post-button">New post</a>)");
        }
        
        static const std::string placeholder_index_posts_list{ "%PLACEHOLDER_INDEX_POSTS_LIST%" };
        std::string value;

        for (const auto& [id, login, caption, body] : m_Posts)
        {
            std::string item{ "<li class = \"post-item\">\n" };
            item += "<p>#" + std::to_string(id) + " " + login + "</p>\n";
            item += "<h3>" + caption + "</h3>\n";
            item += "<a href=\"post.html?id=" + std::to_string(id) + "\">View Post</a>\n";
            item += "</li>\n";
            value.append(std::move(item));
        }

        FindAndReplace(placeholder_index_posts_list, value);

        return m_Content;
    }
}

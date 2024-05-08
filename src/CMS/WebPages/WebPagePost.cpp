#include "WebPagePost.h"
#include <stdexcept>

namespace CMS::WebPages
{
    WebPagePost::WebPagePost(const std::string& path) :
        IWebPage{ path, "/post.html" }
    {
    }

    void WebPagePost::SetPost(const DB::Post& post) noexcept
    {
        m_Post = post;
    }

    IWebPage* WebPagePost::Clone() noexcept
    {
        return this;
    }

    std::string WebPagePost::GenerateWebPage()
    {
        static constexpr auto placeholder_post_type     { "%PLACEHOLDER_POST_TYPE%"         };
        static constexpr auto placeholder_post_id       { "%PLACEHOLDER_POST_ID%"           };
        static constexpr auto placeholder_post_author   { "%PLACEHOLDER_POST_AUTHOR%"       };
        static constexpr auto placeholder_post_publish  { "%PLACEHOLDER_POST_PUBLISH%"      };
        static constexpr auto placeholder_post_edit     { "%PLACEHOLDER_POST_EDIT%"         };
        static constexpr auto placeholder_post_delete   { "%PLACEHOLDER_POST_DELETE%"       };
    	static constexpr auto placeholder_post_caption  { "%PLACEHOLDER_POST_CAPTION%"      };
        static constexpr auto placeholder_post_body     { "%PLACEHOLDER_POST_BODY%"         };
        static constexpr auto placeholder_post_username { "%PLACEHOLDER_POST_USERNAME%"     };
        static constexpr auto placeholder_post_reg      { "%PLACEHOLDER_POST_REGISTRATION%" };
        static constexpr auto placeholder_post_login    { "%PLACEHOLDER_POST_LOGIN%"        };

        if (m_Login.empty() && !m_Post.IsValid())
        {
            // not login
            // create post
            throw std::runtime_error("User is not login");
        }

        if (m_Login.empty() && m_Post.IsValid())
        {
            // not login
            // view post
            FindAndReplace(placeholder_post_type,     "Post View");
            FindAndReplace(placeholder_post_id,       std::to_string(m_Post.ID));
            FindAndReplace(placeholder_post_author,   m_Post.Login);
            FindAndReplace(placeholder_post_publish,  "");
            FindAndReplace(placeholder_post_edit,     "");
            FindAndReplace(placeholder_post_delete,   "");
            FindAndReplace(placeholder_post_caption,  m_Post.Caption);
            FindAndReplace(placeholder_post_body,     m_Post.Body);
            FindAndReplace(placeholder_post_username, "Guest");
            FindAndReplace(placeholder_post_reg,      R"(<a href="reg.html" class="register-button">Registration</a>)");
            FindAndReplace(placeholder_post_login,    R"(<a href="login.html" class="login-button">Login</a>)");
        }
        else if (!m_Login.empty() && !m_Post.IsValid())
        {
            // login
            // create post
            FindAndReplace(placeholder_post_type,     "Post Create");
            FindAndReplace(placeholder_post_id,       "");
            FindAndReplace(placeholder_post_author,   "");
            FindAndReplace(placeholder_post_publish,  "<button type=\"button\" class=\"publish-button\" onclick=\"submitForm('publish')\">Publish</button>");
            FindAndReplace(placeholder_post_edit,     "");
            FindAndReplace(placeholder_post_delete,   "");
            FindAndReplace(placeholder_post_caption,  "");
            FindAndReplace(placeholder_post_body,     "");
            FindAndReplace(placeholder_post_username, m_Login);
            FindAndReplace(placeholder_post_reg,      R"(<a href="account.html" class="register-button">Account</a>)");
            FindAndReplace(placeholder_post_login,    R"(<a href="index.html?cmd=logout" class="logout-button">Logout</a>)");
        }
        else if (!m_Login.empty() && m_Post.IsValid() && m_Login != m_Post.Login)
        {
	        // login
            // view post
            // not author
            FindAndReplace(placeholder_post_type,     "Post View");
            FindAndReplace(placeholder_post_id,       std::to_string(m_Post.ID));
            FindAndReplace(placeholder_post_author,   m_Post.Login);
            FindAndReplace(placeholder_post_publish,  "");
            FindAndReplace(placeholder_post_edit,     "");
            FindAndReplace(placeholder_post_delete,   "");
            FindAndReplace(placeholder_post_caption,  m_Post.Caption);
            FindAndReplace(placeholder_post_body,     m_Post.Body);
            FindAndReplace(placeholder_post_username, m_Login);
            FindAndReplace(placeholder_post_reg,      R"(<a href="account.html" class="register-button">Account</a>)");
            FindAndReplace(placeholder_post_login,    R"(<a href="index.html?cmd=logout" class="logout-button">Logout</a>)");
        }
        else if (!m_Login.empty() && m_Post.IsValid() && m_Login == m_Post.Login)
        {
	        // login
            // edit or delete post
            // post author
            FindAndReplace(placeholder_post_type,     "Post Edit");
            FindAndReplace(placeholder_post_id,       std::to_string(m_Post.ID));
            FindAndReplace(placeholder_post_author,   m_Post.Login);
            FindAndReplace(placeholder_post_publish,  "");
            FindAndReplace(placeholder_post_edit,     "<button type=\"button\" class=\"publish-button\" onclick=\"submitForm('edit')\">Edit</button>");
            FindAndReplace(placeholder_post_delete,   "<button type=\"button\" class=\"delete-button\" onclick=\"submitForm('delete')\">Delete</button>");
            FindAndReplace(placeholder_post_caption,  m_Post.Caption);
            FindAndReplace(placeholder_post_body,     m_Post.Body);
            FindAndReplace(placeholder_post_username, m_Login);
            FindAndReplace(placeholder_post_reg,      R"(<a href="account.html" class="register-button">Account</a>)");
            FindAndReplace(placeholder_post_login,    R"(<a href="index.html?cmd=logout" class="logout-button">Logout</a>)");
        }
        else
        {
            throw std::runtime_error("Generation page post is failed");
        }

        return m_Content;
    }
}

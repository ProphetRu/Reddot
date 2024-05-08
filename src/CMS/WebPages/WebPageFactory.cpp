#include "WebPageFactory.h"

namespace CMS::WebPages
{
	WebPageFactory::WebPageFactory(const std::string& web_root_path)
	{
		m_WebPages[WebPageID::NotFound]     = std::make_unique<WebPageNotFound>(web_root_path);
		m_WebPages[WebPageID::Forbidden]    = std::make_unique<WebPageForbidden>(web_root_path);
		m_WebPages[WebPageID::Registration] = std::make_unique<WebPageRegistration>(web_root_path);
		m_WebPages[WebPageID::Login]        = std::make_unique<WebPageLogin>(web_root_path);
		m_WebPages[WebPageID::Account]      = std::make_unique<WebPageAccount>(web_root_path);
		m_WebPages[WebPageID::Post]         = std::make_unique<WebPagePost>(web_root_path);
		m_WebPages[WebPageID::Index]        = std::make_unique<WebPageIndex>(web_root_path);
	}

	WebPageID WebPageFactory::GetWebPageID(const std::string& name) const noexcept
	{
		if (name == "/")
		{
			return WebPageID::Index;
		}

		for (const auto& [id, page] : m_WebPages)
		{
			if (page->GetName() == name)
			{
				return id;
			}
		}

		return WebPageID::NotFound;
	}

	std::unique_ptr<WebPageNotFound> WebPageFactory::CreateWebPageNotFound()
	{
		const auto clone{ dynamic_cast<WebPageNotFound*>(m_WebPages[WebPageID::NotFound]->Clone()) };
		return std::make_unique<WebPageNotFound>(*clone);
	}

	std::unique_ptr<WebPageForbidden> WebPageFactory::CreateWebPageForbidden()
	{
		const auto clone{ dynamic_cast<WebPageForbidden*>(m_WebPages[WebPageID::Forbidden]->Clone()) };
		return std::make_unique<WebPageForbidden>(*clone);
	}

	std::unique_ptr<WebPageRegistration> WebPageFactory::CreateWebPageRegistration(RegistrationState state)
	{
		const auto clone{ dynamic_cast<WebPageRegistration*>(m_WebPages[WebPageID::Registration]->Clone()) };
		auto page{ std::make_unique<WebPageRegistration>(*clone) };
		page->SetRegistrationState(state);
		return move(page);
	}

	std::unique_ptr<WebPageLogin> WebPageFactory::CreateWebPageLogin(LoginState state)
	{
		const auto clone{ dynamic_cast<WebPageLogin*>(m_WebPages[WebPageID::Login]->Clone()) };
		auto page{ std::make_unique<WebPageLogin>(*clone) };
		page->SetLoginState(state);
		return move(page);
	}

	std::unique_ptr<WebPageAccount> WebPageFactory::CreateWebPageAccount(std::string_view login, std::string_view role)
	{
		const auto clone{ dynamic_cast<WebPageAccount*>(m_WebPages[WebPageID::Account]->Clone()) };
		auto page{ std::make_unique<WebPageAccount>(*clone) };
		page->SetLogin(login);
		page->SetRole(role);
		return move(page);
	}

	std::unique_ptr<WebPagePost> WebPageFactory::CreateWebPagePost(const std::string& login, const DB::Post& post)
	{
		const auto clone{ dynamic_cast<WebPagePost*>(m_WebPages[WebPageID::Post]->Clone()) };
		auto page{ std::make_unique<WebPagePost>(*clone) };

		page->SetLogin(login);
		if (post.IsValid())
		{
			page->SetPost(post);
		}

		return move(page);
	}

	std::unique_ptr<WebPageIndex> WebPageFactory::CreateWebPageIndex(const std::string& login, const DB::Posts& posts)
	{
		const auto clone{ dynamic_cast<WebPageIndex*>(m_WebPages[WebPageID::Index]->Clone()) };
		auto page{ std::make_unique<WebPageIndex>(*clone) };
		page->SetLogin(login);
		page->SetPosts(posts);
		return move(page);
	}
}

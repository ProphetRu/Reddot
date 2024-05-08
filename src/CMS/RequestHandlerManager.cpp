#include "RequestHandlerManager.h"
#include "../Config.h"

namespace CMS::RequestHandlers
{
	RequestHandlerManager::RequestHandlerManager() :
		m_DBManager
		{
			std::make_unique<DB::DBManager>(Config::Config::GetDBServer(),
				Config::Config::GetDBPort(),
				Config::Config::GetDBLogin(),
				Config::Config::GetDBPassword(),
				Config::Config::GetDBName())
		}
	{
	}

	WebPages::RegistrationState RequestHandlerManager::RegisterUser(const std::string& login, const std::string& password) const noexcept
	{
		auto state{ WebPages::RegistrationState::Failed };

		try
		{
			if (m_DBManager->RegisterUser(login, password))
			{
				state = WebPages::RegistrationState::OK;
			}
		}
		catch (const std::exception&)
		{
			state = WebPages::RegistrationState::Failed;
		}

		return state;
	}

	WebPages::LoginState RequestHandlerManager::LoginUser(const std::string& login, const std::string& password) const noexcept
	{
		auto state{ WebPages::LoginState::Failed };

		try
		{
			if (m_DBManager->LoginUser(login, password))
			{
				state = WebPages::LoginState::OK;
			}
		}
		catch (const std::exception&)
		{
			state = WebPages::LoginState::Failed;
		}

		return state;
	}

	bool RequestHandlerManager::DeleteUser(const std::string& login) const noexcept
	{
		try
		{
			return m_DBManager->DeleteUser(login);
		}
		catch (const std::exception&)
		{
			return false;
		}
	}

	std::string RequestHandlerManager::GetUserRole(const std::string& login) const noexcept
	{
		try
		{
			return m_DBManager->GetUserRole(login);
		}
		catch (const std::exception&)
		{
			return {};
		}
	}

	DB::Posts RequestHandlerManager::GetPosts() const noexcept
	{
		try
		{
			return m_DBManager->GetPosts();
		}
		catch (const std::exception&)
		{
			return {};
		}
	}

	DB::Post RequestHandlerManager::GetPost(int id) const noexcept
	{
		try
		{
			return m_DBManager->GetPost(id);
		}
		catch (const std::exception&)
		{
			return {};
		}
	}

	void RequestHandlerManager::PublishPost(const DB::Post& post) const
	{
		if (!post.IsValid())
		{
			throw std::runtime_error("Invalid params for post publish");
		}

		try
		{
			if (!m_DBManager->PublishPost(post))
			{
				throw std::runtime_error("");
			}
		}
		catch (const std::exception&)
		{
			throw std::runtime_error("Failed to publish post");
		}
	}

	void RequestHandlerManager::EditPost(const std::string& login, const DB::Post& post) const
	{
		if (!post.IsValid())
		{
			throw std::runtime_error("Invalid params for post edit");
		}
		if (login != post.Login)
		{
			throw std::runtime_error("User is not author of the post");
		}

		try
		{
			if (!m_DBManager->EditPost(login, post))
			{
				throw std::runtime_error("");
			}
		}
		catch (const std::exception&)
		{
			throw std::runtime_error("Failed to edit post");
		}
	}

	void RequestHandlerManager::DeletePost(int post_id, const std::string& login) const
	{
		try
		{
			if (!m_DBManager->DeletePost(post_id, login))
			{
				throw std::runtime_error("");
			}
		}
		catch (const std::exception&)
		{
			throw std::runtime_error("Failed to delete post");
		}
	}
}

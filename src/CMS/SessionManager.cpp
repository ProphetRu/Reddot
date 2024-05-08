#include "SessionManager.h"
#include <stdexcept>

namespace CMS::Session
{
	void SessionManager::AddSession(const std::string& login, const std::string& hash)
	{
		if (login.empty() || hash.empty())
		{
			throw std::invalid_argument("Invalid add session argument");
		}

		m_Sessions[hash] = login;
	}

	bool SessionManager::IsActiveSession(const std::string& hash) const
	{
		return m_Sessions.contains(hash);
	}

	std::string SessionManager::GetLogin(const std::string& hash)
	{
		if (m_Sessions.contains(hash))
		{
			return m_Sessions[hash];
		}

		return {};
	}

	void SessionManager::DeleteSession(const std::string& hash)
	{
		if (hash.empty())
		{
			throw std::invalid_argument("Invalid delete session argument");
		}

		if (m_Sessions.contains(hash))
		{
			m_Sessions.erase(hash);
		}
	}
}

#include "DBManager.h"
#include "../LoggerSafe.h"
#include <stdexcept>
#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/Statement.h>

namespace DB
{
	using namespace Poco::Data::Keywords;
	using Poco::Data::Session;
	using Poco::Data::Statement;

	enum class Role
	{
		Admin = 1,
		User,
	};

	DBManager::DBManager(const std::string& host, int port, const std::string& user, const std::string& password, const std::string& db_name, bool is_compress, bool is_auto_reconnect)
	{
		auto bool_to_string = [](bool value) noexcept
		{
			return (value ? "true" : "false");
		};

		auto is_valid_port = [](int port) noexcept
		{
			return ((port > 0) && (port < 65535));
		};

		if (host.empty() || !is_valid_port(port) || user.empty() || password.empty() || db_name.empty())
		{
			throw std::invalid_argument("Invalid arg for DBManager");
		}

		Log::LoggerSafe::LogInformation("Init DB connection");
		Poco::Data::MySQL::Connector::registerConnector();

		std::string connection_string
		{
			"host="           + host                              + ";" +
			"port="           + std::to_string(port)              + ";" +
			"user="           + user                              + ";" +
			"password="       + password                          + ";" +
			"db="             + db_name                           + ";" +
			"compress="       + bool_to_string(is_compress)       + ";" +
			"auto-reconnect=" + bool_to_string(is_auto_reconnect) + ";"
		};

		m_Session = std::make_unique<Poco::Data::Session>(Poco::Data::MySQL::Connector::KEY, std::move(connection_string));
	}

	DBManager::~DBManager() noexcept
	{
		m_Session->close();
		Poco::Data::MySQL::Connector::unregisterConnector();
	}

	bool DBManager::LoginUser(const std::string& login, const std::string& password) const
	{
		if (login.empty() || password.empty())
		{
			throw std::invalid_argument("Invalid arg for login user");
		}

		if (!m_Session->isConnected())
		{
			throw std::runtime_error("DB connection is closed");
		}

		int count{};

		Statement select_count{ *m_Session };
		select_count << "SELECT COUNT(*) FROM users WHERE login = ? AND password = MD5(?)",
			into(count),
			useRef(login),
			useRef(password),
			now;

		return count > 0;
	}

	bool DBManager::RegisterUser(const std::string& login, const std::string& password) const
	{
		if (login.empty() || password.empty())
		{
			throw std::invalid_argument("Invalid arg for register user");
		}

		if (!m_Session->isConnected())
		{
			throw std::runtime_error("DB connection is closed");
		}

		constexpr int role_id = static_cast<int>(Role::User);

		Statement insert_into{ *m_Session };
		insert_into << "INSERT INTO users (login, password, role_id) VALUES (?, MD5(?), ?)",
			useRef(login),
			useRef(password),
			useRef(role_id);

		const auto rows_affected{ insert_into.execute() };
		return rows_affected > 0;
	}

	bool DBManager::DeleteUser(const std::string& login) const
	{
		if (login.empty())
		{
			throw std::invalid_argument("Invalid arg for delete user");
		}

		if (!m_Session->isConnected())
		{
			throw std::runtime_error("DB connection is closed");
		}

		Statement delete_from{ *m_Session };
		delete_from << "DELETE FROM users WHERE login = ?",
			useRef(login);

		const auto rows_affected{ delete_from.execute() };
		return rows_affected > 0;
	}

	std::string DBManager::GetUserRole(const std::string& login) const
	{
		if (!m_Session->isConnected())
		{
			throw std::runtime_error("DB connection is closed");
		}

		std::string role;

		Statement select{ *m_Session };
		select << "SELECT roles.description FROM users JOIN roles ON users.role_id = roles.id WHERE users.login = ?",
			useRef(login),
			into(role),
			now;

		return role;
	}

	Post DBManager::GetPost(int id) const
	{
		if (!m_Session->isConnected())
		{
			throw std::runtime_error("DB connection is closed");
		}

		Post post;

		Statement select{ *m_Session };
		select << "SELECT id, login, caption, body FROM posts WHERE id = ?",
			useRef(id),
			into(post.ID),
			into(post.Login),
			into(post.Caption),
			into(post.Body),
			now;
		
		return post;
	}

	int DBManager::GetPostsCount() const
	{
		if (!m_Session->isConnected())
		{
			throw std::runtime_error("DB connection is closed");
		}

		int posts_count{};

		Statement select{ *m_Session };
		select << "SELECT COUNT(*) FROM posts",
			into(posts_count),
			now;

		return posts_count;
	}

	Posts DBManager::GetPosts() const
	{
		if (!m_Session->isConnected())
		{
			throw std::runtime_error("DB connection is closed");
		}

		Posts posts;
		if (const auto posts_count{ GetPostsCount() }; posts_count > 0)
		{
			posts.reserve(posts_count);

			Post post;

			Statement select{ *m_Session };
			select << "SELECT id, login, caption, body FROM posts",
				into(post.ID),
				into(post.Login),
				into(post.Caption),
				into(post.Body),
				range(0, 1);

			while (!select.done())
			{
				if (select.execute())
				{
					if (post.ID > 0 && post.IsValid())
					{
						posts.emplace_back(post);
					}
				}
			}
		}

		return posts;
	}

	bool DBManager::PublishPost(const Post& post) const
	{
		if (!post.IsValid())
		{
			throw std::invalid_argument("Invalid arg for publish post");
		}

		if (!m_Session->isConnected())
		{
			throw std::runtime_error("DB connection is closed");
		}

		Statement insert_into{ *m_Session };
		insert_into << "INSERT INTO posts (login, caption, body) VALUES (?, ?, ?)",
			useRef(post.Login),
			useRef(post.Caption),
			useRef(post.Body);

		const auto rows_affected{ insert_into.execute() };
		return rows_affected > 0;
	}

	bool DBManager::EditPost(const std::string& login, const Post& post) const
	{
		if (login.empty() || !post.IsValid())
		{
			throw std::invalid_argument("Invalid arg for edit post");
		}

		if (!m_Session->isConnected())
		{
			throw std::runtime_error("DB connection is closed");
		}

		Statement insert_into{ *m_Session };
		insert_into << "UPDATE posts SET caption = ?, body = ? WHERE id = ? AND login = ?",
			useRef(post.Caption),
			useRef(post.Body),
			useRef(post.ID),
			useRef(login);

		const auto rows_affected{ insert_into.execute() };
		return rows_affected > 0;
	}

	bool DBManager::DeletePost(int post_id, const std::string& login) const
	{
		if (post_id <= 0 || login.empty())
		{
			throw std::invalid_argument("Invalid arg for delete post");
		}

		if (!m_Session->isConnected())
		{
			throw std::runtime_error("DB connection is closed");
		}

		Statement delete_from{ *m_Session };
		delete_from << "DELETE FROM posts WHERE id = ? AND login = ?",
			useRef(post_id),
			useRef(login);

		const auto rows_affected{ delete_from.execute() };
		return rows_affected > 0;
	}
}

#include "CMS.h"
#include <stdexcept>
#include "../Config.h"
#include "../LoggerSafe.h"
#include "../Hashes.h"

namespace CMS
{
	CMS::CMS() :
		m_RequestHandlerManager{ std::make_unique<RequestHandlers::RequestHandlerManager>() },
		m_SessionManager{ std::make_unique<Session::SessionManager>() },
		m_WebPageFactory{ std::make_unique<WebPages::WebPageFactory>(Config::Config::GetWebRootPath()) },
		m_WebSecurityFiltersManager{ std::make_unique<Security::WebSecurityFiltersManager>() }
	{
	}

	CMS& CMS::GetInstance()
	{
		static CMS instance;
		return instance;
	}

	CMSResponse CMS::HandleGetRequestHTTP(const std::string& session_hash, const std::string& uri, const POCOQueryParameters& params) const
	{
		CMSResponse response;
		
		Log::LoggerSafe::LogInformation("GET Request: " + uri);
		const auto web_page_id{ m_WebPageFactory->GetWebPageID(uri) };

		try
		{
			if (web_page_id == WebPages::WebPageID::Registration)
			{
				if (m_SessionManager->IsActiveSession(session_hash))
				{
					throw std::runtime_error("User is login");
				}

				response.Content = m_WebPageFactory->CreateWebPageRegistration(WebPages::RegistrationState::None)->GenerateWebPage();
				return response;
			}
			if (web_page_id == WebPages::WebPageID::Login)
			{
				if (m_SessionManager->IsActiveSession(session_hash))
				{
					throw std::runtime_error("User is login");
				}

				response.Content = m_WebPageFactory->CreateWebPageLogin(WebPages::LoginState::None)->GenerateWebPage();
				return response;
			}
			if (web_page_id == WebPages::WebPageID::Account)
			{
				if (!m_SessionManager->IsActiveSession(session_hash))
				{
					throw std::runtime_error("User is not login");
				}

				const auto login{ m_SessionManager->GetLogin(session_hash)    };
				const auto role { m_RequestHandlerManager->GetUserRole(login) };

				response.Content = m_WebPageFactory->CreateWebPageAccount(login, role)->GenerateWebPage();
				return response;
			}
			if (web_page_id == WebPages::WebPageID::Index)
			{
				for (const auto& [key, value] : params)
				{
					if (key == "cmd" && value == "logout")
					{
						if (m_SessionManager->IsActiveSession(session_hash))
						{
							m_SessionManager->DeleteSession(session_hash);
						}
						break;
					}
					if (key == "cmd" && value == "delete-account")
					{
						if (m_SessionManager->IsActiveSession(session_hash))
						{
							if (m_RequestHandlerManager->DeleteUser(m_SessionManager->GetLogin(session_hash)))
							{
								m_SessionManager->DeleteSession(session_hash);
							}
						}
						break;
					}
				}

				response.Content = m_WebPageFactory->CreateWebPageIndex(m_SessionManager->GetLogin(session_hash), m_RequestHandlerManager->GetPosts())->GenerateWebPage();
				return response;
			}
			if (web_page_id == WebPages::WebPageID::Post)
			{
				auto post_id{ 0 };

				for (const auto& [key, value] : params)
				{
					if (key == "id")
					{
						post_id = std::stoi(value);
						break;
					}
				}

				response.Content = m_WebPageFactory->CreateWebPagePost(m_SessionManager->GetLogin(session_hash), m_RequestHandlerManager->GetPost(post_id))->GenerateWebPage();
				return response;
			}
			if (web_page_id == WebPages::WebPageID::NotFound)
			{
				response.Status  = ResponseStatus::HTTP_NOT_FOUND;
				response.Content = m_WebPageFactory->CreateWebPageNotFound()->GenerateWebPage();
				return response;
			}
			if (web_page_id == WebPages::WebPageID::Forbidden)
			{
				response.Status  = ResponseStatus::HTTP_FORBIDDEN;
				response.Content = m_WebPageFactory->CreateWebPageForbidden()->GenerateWebPage();
				return response;
			}
			else
			{
				throw std::runtime_error("Endpoint for GET-request not found");
			}
		}
		catch (const std::exception& ex)
		{
			Log::LoggerSafe::LogWarning(ex.what());
			response.Status  = ResponseStatus::HTTP_FORBIDDEN;
			response.Content = m_WebPageFactory->CreateWebPageForbidden()->GenerateWebPage();
			return response;
		}
	}

	CMSResponse CMS::HandlePostRequestHTTP(const std::string& session_hash, const std::string& uri, const Poco::Net::HTMLForm& params) const
	{
		CMSResponse response;

		Log::LoggerSafe::LogInformation("POST Request: " + uri);
		const auto web_page_id{ m_WebPageFactory->GetWebPageID(uri) };

		try
		{
			if (web_page_id == WebPages::WebPageID::Registration)
			{
				if (m_SessionManager->IsActiveSession(session_hash))
				{
					throw std::runtime_error("User is login");
				}

				m_WebSecurityFiltersManager->Check(params["login"]);
				m_WebSecurityFiltersManager->Check(params["password"]);

				const auto state{ m_RequestHandlerManager->RegisterUser(params["login"], params["password"]) };
				response.Content = m_WebPageFactory->CreateWebPageRegistration(state)->GenerateWebPage();
				return response;
			}
			if (web_page_id == WebPages::WebPageID::Login)
			{
				if (m_SessionManager->IsActiveSession(session_hash))
				{
					throw std::runtime_error("User is login");
				}

				const auto login   { params["login"]    };
				const auto password{ params["password"] };

				m_WebSecurityFiltersManager->Check(login);
				m_WebSecurityFiltersManager->Check(password);

				const auto state{ m_RequestHandlerManager->LoginUser(login, password) };
				if (state == WebPages::LoginState::OK)
				{
					const auto password_hash{ Hashes::Hashes::GetMD5(password) };
					const auto ses_hash{ Hashes::Hashes::GetSHA1(login + password_hash) };
					m_SessionManager->AddSession(login, ses_hash);
					response.SessionHash = ses_hash;
				}

				response.Content = m_WebPageFactory->CreateWebPageLogin(state)->GenerateWebPage();
				return response;
			}
			if (web_page_id == WebPages::WebPageID::Post)
			{
				if (!m_SessionManager->IsActiveSession(session_hash))
				{
					throw std::runtime_error("User is not login");
				}
				
				if (const auto action{ params["action"] }; action == "publish")
				{
					const DB::Post post
					{
						.Login   = m_SessionManager->GetLogin(session_hash),
						.Caption = params["caption"],
						.Body    = params["body"]
					};

					m_WebSecurityFiltersManager->Check(post.Caption);
					m_WebSecurityFiltersManager->Check(post.Body);

					m_RequestHandlerManager->PublishPost(post);
					response.Content = m_WebPageFactory->CreateWebPageIndex(m_SessionManager->GetLogin(session_hash), m_RequestHandlerManager->GetPosts())->GenerateWebPage();
					return response;
				}
				else if (action == "edit")
				{
					const DB::Post post
					{
						.ID      = std::stoi(params["id"]),
						.Login   = params["author"],
						.Caption = params["caption"],
						.Body    = params["body"]
					};

					m_WebSecurityFiltersManager->Check(post.Login);
					m_WebSecurityFiltersManager->Check(post.Caption);
					m_WebSecurityFiltersManager->Check(post.Body);
					
					m_RequestHandlerManager->EditPost(m_SessionManager->GetLogin(session_hash), post);
					response.Content = m_WebPageFactory->CreateWebPageIndex(m_SessionManager->GetLogin(session_hash), m_RequestHandlerManager->GetPosts())->GenerateWebPage();
					return response;
				}
				else if (action == "delete")
				{
					m_RequestHandlerManager->DeletePost(std::stoi(params["id"]), m_SessionManager->GetLogin(session_hash));
					response.Content = m_WebPageFactory->CreateWebPageIndex(m_SessionManager->GetLogin(session_hash), m_RequestHandlerManager->GetPosts())->GenerateWebPage();
					return response;
				}
				else
				{
					throw std::runtime_error("Invalid POST action");
				}
			}
			else
			{
				throw std::runtime_error("Endpoint for POST-request not found");
			}
		}
		catch (const std::exception& ex)
		{
			Log::LoggerSafe::LogWarning(ex.what());
			response.Status  = ResponseStatus::HTTP_FORBIDDEN;
			response.Content = m_WebPageFactory->CreateWebPageForbidden()->GenerateWebPage();
			return response;
		}
	}
}

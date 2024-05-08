#pragma once

#include "WebPages/RegistrationState.h"
#include "WebPages/LoginState.h"
#include "../DB/DBManager.h"
#include "../DB/Post.h"
#include <memory>
#include <string>

namespace CMS::RequestHandlers
{
    /**
     * @brief A class for managing user requests and interactions.
     */
    class RequestHandlerManager
    {
    public:
        /**
         * @brief Constructs a RequestHandlerManager object.
         */
        RequestHandlerManager();

        /**
         * @brief Registers a new user with the specified login and password.
         * @param login The user's login.
         * @param password The user's password.
         * @return The registration state of the user.
         */
        [[nodiscard]] WebPages::RegistrationState RegisterUser(const std::string& login, const std::string& password) const noexcept;

        /**
         * @brief Logs in a user with the specified login and password.
         * @param login The user's login.
         * @param password The user's password.
         * @return The login state of the user.
         */
        [[nodiscard]] WebPages::LoginState LoginUser(const std::string& login, const std::string& password) const noexcept;

        /**
         * @brief Deletes a user with the specified login.
         * @param login The user's login.
         * @return True if the user was successfully deleted, false otherwise.
         */
        [[nodiscard]] bool DeleteUser(const std::string& login) const noexcept;

        /**
         * @brief Retrieves the role of the user with the specified login.
         * @param login The user's login.
         * @return The role of the user.
         */
        [[nodiscard]] std::string GetUserRole(const std::string& login) const noexcept;

        /**
         * @brief Retrieves all posts from the database.
         * @return A collection of posts.
         */
        [[nodiscard]] DB::Posts GetPosts() const noexcept;

        /**
         * @brief Retrieves a post with the specified ID from the database.
         * @param id The ID of the post.
         * @return The post with the specified ID.
         */
        [[nodiscard]] DB::Post GetPost(int id) const noexcept;

        /**
         * @brief Publishes a new post to the database.
         * @param post The post to publish.
         */
        void PublishPost(const DB::Post& post) const;

        /**
         * @brief Edits an existing post in the database.
         * @param login The user's login.
         * @param post The post to edit.
         */
        void EditPost(const std::string& login, const DB::Post& post) const;

        /**
         * @brief Deletes a post with the specified ID from the database.
         * @param post_id The ID of the post to delete.
         * @param login The user's login.
         */
        void DeletePost(int post_id, const std::string& login) const;

    private:
        std::unique_ptr<DB::DBManager> m_DBManager; /**< The database manager for handling database operations. */
    };
}

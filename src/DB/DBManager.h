#pragma once

#include <Poco/Data/Session.h>
#include "Post.h"
#include <memory>

namespace DB
{
    /**
     * @brief A class for managing database operations.
     */
    class DBManager final
    {
    public:
        /**
         * @brief Constructs a DBManager object with the specified database connection details.
         * @param host The database host.
         * @param port The database port.
         * @param user The database user.
         * @param password The database password.
         * @param db_name The database name.
         * @param is_compress Flag for compression.
         * @param is_auto_reconnect Flag for auto-reconnect.
         */
        DBManager(const std::string& host, int port, const std::string& user, const std::string& password, const std::string& db_name, bool is_compress = true, bool is_auto_reconnect = true);

        /**
         * @brief Destructor.
         */
        ~DBManager() noexcept;

        /**
         * @brief Validates user login credentials.
         * @param login The user's login.
         * @param password The user's password.
         * @return True if the login is successful, false otherwise.
         */
        [[nodiscard]] bool LoginUser(const std::string& login, const std::string& password) const;

        /**
         * @brief Registers a new user.
         * @param login The user's login.
         * @param password The user's password.
         * @return True if registration is successful, false otherwise.
         */
        [[nodiscard]] bool RegisterUser(const std::string& login, const std::string& password) const;

        /**
         * @brief Deletes a user.
         * @param login The user's login.
         * @return True if deletion is successful, false otherwise.
         */
        [[nodiscard]] bool DeleteUser(const std::string& login) const;

        /**
         * @brief Retrieves the role of a user.
         * @param login The user's login.
         * @return The role of the user.
         */
        [[nodiscard]] std::string GetUserRole(const std::string& login) const;

        /**
         * @brief Retrieves a post by ID.
         * @param id The ID of the post.
         * @return The post with the specified ID.
         */
        [[nodiscard]] Post GetPost(int id) const;

        /**
         * @brief Retrieves the total number of posts.
         * @return The count of posts.
         */
        [[nodiscard]] int GetPostsCount() const;

        /**
         * @brief Retrieves all posts.
         * @return A collection of posts.
         */
        [[nodiscard]] Posts GetPosts() const;

        /**
         * @brief Publishes a new post.
         * @param post The post to publish.
         * @return True if publishing is successful, false otherwise.
         */
        [[nodiscard]] bool PublishPost(const Post& post) const;

        /**
         * @brief Edits an existing post.
         * @param login The user's login.
         * @param post The post to edit.
         * @return True if editing is successful, false otherwise.
         */
        [[nodiscard]] bool EditPost(const std::string& login, const Post& post) const;

        /**
         * @brief Deletes a post.
         * @param post_id The ID of the post to delete.
         * @param login The user's login.
         * @return True if deletion is successful, false otherwise.
         */
        [[nodiscard]] bool DeletePost(int post_id, const std::string& login) const;

    private:
        std::unique_ptr<Poco::Data::Session> m_Session{ nullptr }; /**< The database session. */
    };
}

#pragma once

#include <stdexcept>
#include "user.hpp"
#include "username.hpp"
#include "email.hpp"

enum class database_repository_error_codes {
  ERROR_INSERT_USER,
  GENERIC
};

class database_repository_exception : public std::runtime_error
{
public:
  explicit database_repository_exception(database_repository_error_codes error_code)
    : std::runtime_error{""},
      _error_code{error_code}
  {}

  database_repository_exception(database_repository_error_codes error_code, std::string const& message)
    : std::runtime_error{message},
      _error_code{error_code}
  {}

  auto error_code() const { return _error_code; }

private:
  database_repository_error_codes _error_code;
};

class database_repository {
public:
  virtual ~database_repository() = default;

  virtual void user_insert(user const& user) = 0;
  virtual bool user_username_exists(username const& username) const  = 0;
  virtual bool user_email_exists(email const& email) const  = 0;
  virtual std::string user_get_password(username const& username) const = 0;
};

#pragma once

#include "database_repository.hpp"
#include "jwt_service.hpp"
#include "password_encryptor.hpp"
#include <stdexcept>
#include <string_view>

enum class user_usecase_login_error_codes { user_does_not_exist, invalid_password };

class user_usecase_login_exception : public std::runtime_error {
public:
  user_usecase_login_exception(user_usecase_login_error_codes error_code)
      : std::runtime_error{""}, _error_code{error_code} {}

  auto error_code() const { return _error_code; }

private:
  user_usecase_login_error_codes _error_code;
};

class user_usecase_login {
public:
  user_usecase_login(password_encryptor &password_encryptor,
                     database_repository &database_repository,
                     jwt_service &jwt_service);

  std::string execute(std::string_view const &string_username,
                      std::string_view const &string_password) const;

private:
  password_encryptor &_password_encryptor;
  database_repository &_database_repository;
  jwt_service &_jwt_service;
};

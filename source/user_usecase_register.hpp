#pragma once

#include "database_repository.hpp"
#include "password_encryptor.hpp"
#include <stdexcept>
#include <string_view>

enum class user_usecase_register_error_codes {
  username_already_exists,
  email_already_exists,
};

class user_usecase_register_exception : std::runtime_error {
public:
  user_usecase_register_exception(user_usecase_register_error_codes error_code)
      : std::runtime_error{""}, _error_code{error_code} {}

  auto error_code() const { return _error_code; }

private:
  user_usecase_register_error_codes _error_code;
};

class user_usecase_register {
public:
  user_usecase_register(password_encryptor &password_encryptor,
                        database_repository &database_repository);

  std::string execute(std::string_view const &username,
                      std::string_view const &password,
                      std::string_view const &email) const;

private:
  password_encryptor &_password_encryptor;
  database_repository &_database_repository;
};

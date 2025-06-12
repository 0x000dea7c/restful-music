#pragma once

#include "database_repository.hpp"
#include "email.hpp"
#include "password.hpp"
#include "password_encryptor.hpp"
#include "user_usecase_login.hpp"
#include "user_usecase_register.hpp"
#include "username.hpp"
#include <crow/http_request.h>
#include <crow/http_response.h>

class password_encryptor;
class database_repository;
class jwt_service;

class user_controller {
public:
  user_controller(password_encryptor &password_encryptor,
                  database_repository &database_repository,
                  jwt_service &jwt_service);

  void user_register(crow::request const &request, crow::response &response);

  void user_login(crow::request const &request, crow::response &response);

  std::string get_error_message_invalid_json() const { return "Invalid JSON"; }

  std::string get_error_message_username_empty() const {
    return "Username not provided";
  }

  std::string get_error_message_password_empty() const {
    return "Password not provided";
  }

  std::string get_error_message_email_empty() const {
    return "Email not provided";
  }

  std::string get_error_message_username_malformed() const {
    return "Username must be a string";
  }

  std::string get_error_message_password_malformed() const {
    return "Password must be a string";
  }

  std::string get_error_message_email_malformed() const {
    return "Email must be a string";
  }

  std::string get_message_login_successful() const {
    return "Login successful";
  }

  std::string get_error_message_validating_password() const {
    return "Error validating password";
  }

  std::string
  get_password_error_message(password_validation_error_codes error_code) const {
    switch (error_code) {
    case password_validation_error_codes::password_is_empty:
      return "Password can not be empty";
    case password_validation_error_codes::password_is_too_short:
      return "Password is too short";
    case password_validation_error_codes::password_is_too_long:
      return "Password is too long";
    }
  }

  std::string
  get_username_error_message(username_validation_error_codes error_code) const {
    switch (error_code) {
    case username_validation_error_codes::username_is_empty:
      return "Username can not be empty";
    case username_validation_error_codes::username_is_too_short:
      return "Username is too short";
    case username_validation_error_codes::username_is_too_long:
      return "Username is too long";
    case username_validation_error_codes::username_contains_invalid_characters:
      return "Username must contain only letters";
    }
  }

  std::string
  get_email_error_message(email_validation_error_codes error_code) const {
    switch (error_code) {
    case email_validation_error_codes::email_is_empty:
      return "Email can not be empty";
    case email_validation_error_codes::email_is_not_valid:
      return "Email is not valid";
    }
  }

  std::string get_password_encryptor_error_message(
      password_encryptor_error_codes error_code) const {
    switch (error_code) {
    case password_encryptor_error_codes::ERROR_HASHING_FAILED:
      return "Internal server error: password hashing failed. Try again later";
    default:
      return "Unknown error";
    }
  }

  std::string get_database_repository_error_message(
      database_repository_error_codes error_code) const {
    switch (error_code) {
    case database_repository_error_codes::ERROR_INSERT_USER:
      return "Error creating user. Try again later";
    case database_repository_error_codes::GENERIC:
      return "Generic error. Try again later";
    }
  }

  std::string get_credentials_already_in_use_message() const {
    return "The provided credentials are already in use";
  }

  std::string get_register_usecase_error_message(
      user_usecase_register_error_codes error_code) const {
    switch (error_code) {
    case user_usecase_register_error_codes::username_already_exists:
      return "Username already exists";
    case user_usecase_register_error_codes::email_already_exists:
      return "Email already exists";
    }
  }

  std::string get_login_usecase_error_message(user_usecase_login_error_codes error_code) const {
    switch (error_code) {
    case user_usecase_login_error_codes::user_does_not_exist:
      return "Invalid credentials";
    case user_usecase_login_error_codes::invalid_password:
      return "Invalid credentials";
    }
  }

private:
  password_encryptor &_password_encryptor;
  database_repository &_database_repository;
  jwt_service &_jwt_service;
};

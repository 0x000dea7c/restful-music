#pragma once

#include <stdexcept>
#include <string>
#include <string_view>

enum class password_validation_error_codes {
  password_is_empty,
  password_is_too_short,
  password_is_too_long
};

class password_exception : public std::runtime_error {
public:
  password_exception(password_validation_error_codes error_code)
      : std::runtime_error{""}, _error_code{error_code} {}

  auto error_code() const { return _error_code; }

private:
  password_validation_error_codes _error_code;
};

class password {
public:
  explicit password(std::string_view const &plain_text_password);

  auto value() const { return _password; }

  // NOTE: this violates DDD principles (value objects should be immutable), but
  // I don't know how to approach this
  void set_password(std::string const &encrypted_password) {
    _password = encrypted_password;
  }

private:
  std::string _password;
};

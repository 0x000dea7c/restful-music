#pragma once

#include <stdexcept>
#include <string>

enum class email_validation_error_codes {
  email_is_empty,
  email_is_not_valid
};

class email_exception : public std::runtime_error {
public:
  email_exception(email_validation_error_codes error_code)
    : std::runtime_error{""},
      _error_code {error_code}
  {}

  auto error_code() const { return _error_code; }

private:
  email_validation_error_codes _error_code;
};

class email
{
public:
  explicit email(std::string const& email);

  auto value() const { return _email; }

private:
  std::string const _email;
};

#pragma once

#include <stdexcept>
#include <string>
#include <string_view>

enum class username_validation_error_codes {
  username_is_empty,
  username_is_too_short,
  username_is_too_long,
  username_contains_invalid_characters
};

class username_exception : public std::runtime_error
{
public:
  username_exception(username_validation_error_codes error_code)
    : std::runtime_error{""},
      _error_code{error_code}
  {}

  auto error_code() const { return _error_code; }

private:
  username_validation_error_codes _error_code;
};

class username
{
public:
  explicit username(std::string_view const& username);

  auto value() const { return _username; }

private:
  std::string const _username;
};

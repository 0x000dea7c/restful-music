#include "username.hpp"
#include <string_view>
#include <regex>

int constexpr username_minimum_length{4};
int constexpr username_maximum_length{16};

username::username(std::string_view const& username)
  : _username{username}
{
  if (_username.empty()) {
    throw username_exception{username_validation_error_codes::username_is_empty};
  }

  if (_username.length() < username_minimum_length) {
    throw username_exception{username_validation_error_codes::username_is_too_short};
  }

  if (_username.length() > username_maximum_length) {
    throw username_exception{username_validation_error_codes::username_is_too_long};
  }

  std::regex const pattern(R"(^[a-zA-Z]+$)");

  if (!std::regex_match(_username, pattern)) {
    throw username_exception{username_validation_error_codes::username_contains_invalid_characters};
  }
}

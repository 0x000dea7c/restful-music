#include "password.hpp"
#include <string_view>

int constexpr password_minimum_length{6};
int constexpr password_maximum_length{128};

password::password(std::string_view const &plain_text_password) {
  if (plain_text_password.empty()) {
    throw password_exception{
        password_validation_error_codes::password_is_empty};
  }

  if (plain_text_password.length() < password_minimum_length) {
    throw password_exception{
        password_validation_error_codes::password_is_too_short};
  }

  if (plain_text_password.length() > password_maximum_length) {
    throw password_exception{
        password_validation_error_codes::password_is_too_long};
  }

  _password = plain_text_password;
}

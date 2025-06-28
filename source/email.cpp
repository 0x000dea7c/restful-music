#include "email.hpp"

#include <regex>

email::email(std::string const& email)
  : _email{email}
{
  if (email.empty()) {
    throw email_exception{email_validation_error_codes::email_is_empty};
  }

  std::regex const pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");

  if (!std::regex_match(email, pattern)) {
    throw email_exception{email_validation_error_codes::email_is_not_valid};
  }
}

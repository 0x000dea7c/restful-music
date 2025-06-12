#pragma once

#include <stdexcept>
#include <string_view>

enum class password_encryptor_error_codes {
  ERROR_INITIALISATION,
  ERROR_HASHING_FAILED
};

class password_encryptor_exception : public std::runtime_error {
public:
  password_encryptor_exception(password_encryptor_error_codes error_code)
      : std::runtime_error{""}, _error_code{error_code} {}

  auto error_code() const { return _error_code; }

private:
  password_encryptor_error_codes _error_code;
};

class password_encryptor {
public:
  virtual ~password_encryptor() = default;

  virtual std::string encrypt(std::string_view const &password) const = 0;

  virtual bool passwords_match(std::string_view const &stored_hash,
                               std::string_view const &password) const = 0;
};

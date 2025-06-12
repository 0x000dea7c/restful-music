#pragma once

#include "password_encryptor.hpp"

class password_encryptor_sodium : public password_encryptor {
public:
  password_encryptor_sodium();

  std::string encrypt(std::string_view const &password) const override;

  bool passwords_match(std::string_view const &stored_hash,
                       std::string_view const &password) const override;

private:
  std::size_t const _hash_length;
};

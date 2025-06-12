#include "password_encryptor_sodium.hpp"
#include <sodium.h>
#include <vector>

password_encryptor_sodium::password_encryptor_sodium()
    : _hash_length{crypto_pwhash_STRBYTES} {
  if (sodium_init() < 0) {
    throw password_encryptor_exception{
        password_encryptor_error_codes::ERROR_INITIALISATION};
  }
}

std::string
password_encryptor_sodium::encrypt(std::string_view const &password) const {
  std::vector<char> hashed_password(_hash_length);

  if (crypto_pwhash_str(hashed_password.data(), password.data(),
                        password.length(), crypto_pwhash_OPSLIMIT_INTERACTIVE,
                        crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {
    throw password_encryptor_exception{
        password_encryptor_error_codes::ERROR_HASHING_FAILED};
  }

  return std::string(hashed_password.data());
}

bool password_encryptor_sodium::passwords_match(
    std::string_view const &stored_hash,
    std::string_view const &password) const {
  if (crypto_pwhash_str_verify(stored_hash.data(), password.data(), password.length()) == 0) {
    return true;
  }

  return false;
}

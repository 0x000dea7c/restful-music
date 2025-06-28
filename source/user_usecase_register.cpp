#include "user_usecase_register.hpp"
#include "database_repository.hpp"
#include "user.hpp"
#include "username.hpp"
#include "uuid.hpp"

user_usecase_register::user_usecase_register(
    password_encryptor &password_encryptor,
    database_repository &database_repository)
    : _password_encryptor{password_encryptor},
      _database_repository{database_repository} {}

std::string
user_usecase_register::execute(std::string_view const &string_username,
                               std::string_view const &string_password,
                               std::string_view const &string_email) const {
  auto validated_password = password(string_password.data());
  auto validated_username = username(string_username.data());
  auto validated_email = email(string_email.data());
  auto new_uuid = uuid();

  validated_password.set_password(_password_encryptor.encrypt(validated_password.value()));

  user user(validated_username, validated_password, validated_email, new_uuid);

  if (_database_repository.user_username_exists(validated_username)) {
    throw user_usecase_register_exception{
        user_usecase_register_error_codes::username_already_exists};
  }

  if (_database_repository.user_email_exists(validated_email)) {
    throw user_usecase_register_exception{
        user_usecase_register_error_codes::email_already_exists};
  }

  _database_repository.user_insert(user);

  return new_uuid.value();
}

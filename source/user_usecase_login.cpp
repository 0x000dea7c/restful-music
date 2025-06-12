#include "user_usecase_login.hpp"
#include "password.hpp"
#include "username.hpp"
#include "uuid.hpp"
#include <string_view>

user_usecase_login::user_usecase_login(password_encryptor &password_encryptor,
                                       database_repository &database_repository,
                                       jwt_service &jwt_service)
    : _password_encryptor{password_encryptor},
      _database_repository{database_repository}, _jwt_service{jwt_service} {}

std::string
user_usecase_login::execute(std::string_view const &string_username,
                            std::string_view const &string_password) const {
  username const validated_username(string_username);
  password const validated_password(string_password);

  auto database_password =
      _database_repository.user_get_password(validated_username);

  if (database_password.empty()) {
    throw user_usecase_login_exception{
        user_usecase_login_error_codes::user_does_not_exist};
  }

  if (!_password_encryptor.passwords_match(database_password,
                                           string_password.data())) {
    throw user_usecase_login_exception{
        user_usecase_login_error_codes::invalid_password};
  }

  auto uuid = uuid::generate();

  auto expires_at = std::chrono::system_clock::now() + std::chrono::minutes{30};

  return _jwt_service.create_token(validated_username.value(), uuid,
                                   expires_at);
}

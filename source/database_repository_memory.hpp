#include "database_repository.hpp"
#include <unordered_map>

class database_repository_memory : public database_repository {
public:
  void user_insert(user const &user) override {
    _username_password[user.username_value().value()] =
        user.password_value().value();
    _email_username[user.email_value().value()] = user.username_value().value();
  }

  bool user_username_exists(username const &username) const override {
    if (_username_password.find(username.value()) != _username_password.end()) {
      return true;
    }

    return false;
  }

  bool user_email_exists(email const &email) const override {
    if (_email_username.find(email.value()) != _email_username.end()) {
      return true;
    }

    return false;
  }

  std::string user_get_password(username const &username) const override {
    if (_username_password.find(username.value()) == _username_password.end()) {
      return "";
    }

    return _username_password.at(username.value());
  }

  std::unordered_map<std::string, std::string> _username_password;
  std::unordered_map<std::string, std::string> _email_username;
};

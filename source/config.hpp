#pragma once

#include <stdexcept>
#include <string>

class config_exception : public std::runtime_error {
public:
  config_exception(std::string const &message) : std::runtime_error(message) {}
};

class config {
public:
  explicit config();

  auto database_name() const { return _database_name; }

  auto jwt_secret() const { return _jwt_secret; }

  auto port() const { return _port; }

  auto jwt_issuer() const { return _jwt_issuer; }

private:
  std::string _database_name;
  std::string _jwt_secret;
  std::string _jwt_issuer;
  int _port;
};

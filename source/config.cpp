#include "config.hpp"
#include <cstdlib>

config::config()
{
  auto database_name = std::getenv("RESTMUSIC_DATABASE_NAME");
  auto jwt_secret = std::getenv("RESTMUSIC_JWT_SECRET");
  auto jwt_issuer = std::getenv("RESTMUSIC_JWT_ISSUER");

  if (!database_name) {
    throw config_exception{"Error: environment variable RESTMUSIC_DATABASE_NAME not found"};
  }

  if (!jwt_secret) {
    throw config_exception{"Error: environment variable RESTMUSIC_JWT_SECRET not found"};
  }

  if (!jwt_issuer) {
    throw config_exception{"Error: environment variable RESTMUSIC_JWT_ISSUER not found"};
  }

  auto string_port = std::getenv("RESTMUSIC_LISTEN_PORT");

  if (!string_port) {
    throw config_exception{"Error: environment variable RESTMUSIC_LISTEN_PORT not found"};
  }

  _database_name = database_name;
  _jwt_secret = jwt_secret;
  _jwt_issuer = jwt_issuer;
  _port = std::atoi(string_port);
}

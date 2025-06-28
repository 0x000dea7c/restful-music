#include "database_repository_sqlite.hpp"
#include "database_repository.hpp"
#include "email.hpp"
#include "user.hpp"
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Statement.h>
#include <stdexcept>

database_repository_sqlite::database_repository_sqlite(
    std::string const &database_name)
    : _database(database_name, SQLite::OPEN_READWRITE) {}

void database_repository_sqlite::user_insert(user const &user) {
  try {
    SQLite::Statement query(
        _database,
        R"(INSERT INTO users (uuid, username, password, email)
                             VALUES (?, ?, ?, ?))");

    query.bind(1, user.uuid_value().value());
    query.bind(2, user.username_value().value());
    query.bind(3, user.password_value().value());
    query.bind(4, user.email_value().value());
    query.exec();
  } catch (std::runtime_error const &ex) {
    throw database_repository_exception{
        database_repository_error_codes::ERROR_INSERT_USER, ex.what()};
  }
}

bool database_repository_sqlite::user_email_exists(email const &email) const {
  try {
    int exists{0};
    SQLite::Statement query(_database,
                            R"(SELECT 1 FROM users WHERE email = ?)");

    query.bind(1, email.value());

    if (query.executeStep()) {
      exists = query.getColumn(0).getInt();
    }

    return exists;
  } catch (std::runtime_error const &ex) {
    throw database_repository_exception{
        database_repository_error_codes::GENERIC, ex.what()};
  }
}

bool database_repository_sqlite::user_username_exists(
    username const &username) const {
  try {
    int exists{0};
    SQLite::Statement query(_database,
                            R"(SELECT 1 FROM users WHERE username = ?)");
    query.bind(1, username.value());

    if (query.executeStep()) {
      exists = query.getColumn(0).getInt();
    }

    return exists;
  } catch (std::runtime_error const &ex) {
    // TODO: logging
    throw database_repository_exception{
        database_repository_error_codes::GENERIC, ex.what()};
  }
}

std::string
database_repository_sqlite::user_get_password(username const &username) const {
  try {
    SQLite::Statement query(_database,
                            R"(SELECT password FROM users WHERE username = ?)");
    query.bind(1, username.value());

    if (query.executeStep()) {
      return query.getColumn(0).getString();
    }

    return "";
  } catch (std::runtime_error const &ex) {
    throw database_repository_exception{
        database_repository_error_codes::GENERIC, ex.what()};
  }
}

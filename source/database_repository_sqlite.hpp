#include "database_repository.hpp"
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/SQLiteCpp.h>

class database_repository_sqlite : public database_repository
{
public:
  explicit database_repository_sqlite(std::string const& database_name);

  void user_insert(user const& user) override;
  bool user_username_exists(username const& username) const override;
  bool user_email_exists(email const& email) const override;
  std::string user_get_password(username const& username) const override;

private:
  SQLite::Database _database;
};

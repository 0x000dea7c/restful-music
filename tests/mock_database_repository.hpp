#pragma once

#include "database_repository.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class mock_database_repository : public database_repository {
public:
  MOCK_METHOD(bool, user_username_exists, (username const &username),
              (const, override));
  MOCK_METHOD(bool, user_email_exists, (email const &email), (const, override));
  MOCK_METHOD(void, user_insert, (user const &user), (override));
  MOCK_METHOD(std::string, user_get_password, (username const &username),
              (const, override));
};

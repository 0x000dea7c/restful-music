#include "database_repository_memory.hpp"
#include "jwt_service_fake.hpp"
#include "password.hpp"
#include "password_encryptor.hpp"
#include "password_encryptor_sodium.hpp"
#include "user_usecase_login.hpp"
#include "username.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class user_login_integration_test : public ::testing::Test {
protected:
  void SetUp() override {
    _database = std::make_unique<database_repository_memory>();
    _encryptor = std::make_unique<password_encryptor_sodium>();
    _jwt = std::make_unique<fake_jwt_service>();

    _database->_username_password["validuser"] =
        _encryptor->encrypt("validpassword");

    _usecase =
        std::make_unique<user_usecase_login>(*_encryptor, *_database, *_jwt);
  }

  std::unique_ptr<database_repository_memory> _database;
  std::unique_ptr<password_encryptor> _encryptor;
  std::unique_ptr<jwt_service> _jwt;
  std::unique_ptr<user_usecase_login> _usecase;
};

TEST_F(user_login_integration_test, should_throw_with_malformed_username) {
  std::string const malformed_username{"a"};
  std::string const password{"abceasyas123"};

  try {
    _usecase->execute(malformed_username, password);
    FAIL() << "Exception expected";
  } catch (username_exception const& ex) {
    ASSERT_EQ(ex.error_code(), username_validation_error_codes::username_is_too_short);
  }
}

TEST_F(user_login_integration_test, should_throw_with_malformed_password) {
  std::string const username{"goodusername"};
  std::string const malformed_password{"a"};

  try {
    _usecase->execute(username, malformed_password);
    FAIL() << "Exception expected";
  } catch (password_exception const& ex) {
    ASSERT_EQ(ex.error_code(), password_validation_error_codes::password_is_too_short);
  }
}

TEST_F(user_login_integration_test, should_throw_with_non_existent_username) {
  std::string const username{"unnamed"};
  std::string const password{"goodpassword"};

  try {
    _usecase->execute(username, password);
    FAIL() << "Exception expected";
  } catch (user_usecase_login_exception const& ex) {
    ASSERT_EQ(ex.error_code(), user_usecase_login_error_codes::user_does_not_exist);
  }
}

TEST_F(user_login_integration_test, should_throw_with_invalid_username_password) {
  std::string const username{"validuser"};
  std::string const password{"invalidpassword"};

  try {
    _usecase->execute(username, password);
    FAIL() << "Exception expected";
  } catch (user_usecase_login_exception const& ex) {
    ASSERT_EQ(ex.error_code(), user_usecase_login_error_codes::invalid_password);
  }
}

TEST_F(user_login_integration_test, should_return_token_with_valid_input) {
  std::string const username{"validuser"};
  std::string const password{"validpassword"};

  auto const token = _usecase->execute(username, password);

  ASSERT_THAT(token, testing::StartsWith("fake_token_"));
}

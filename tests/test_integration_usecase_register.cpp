#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "database_repository_memory.hpp"
#include "email.hpp"
#include "password.hpp"
#include "password_encryptor_sodium.hpp"
#include "user_usecase_register.hpp"
#include "username.hpp"

class user_register_integration_test : public ::testing::Test {
protected:
  void SetUp() override {
    _database = std::make_unique<database_repository_memory>();
    _encryptor = std::make_unique<password_encryptor_sodium>();

    _database->_username_password["validuser"] =
        _encryptor->encrypt("validpassword");

    _database->_email_username["valid@email.com"] = "validuser";

    _usecase =
        std::make_unique<user_usecase_register>(*_encryptor, *_database);
  }

  std::unique_ptr<database_repository_memory> _database;
  std::unique_ptr<password_encryptor> _encryptor;
  std::unique_ptr<user_usecase_register> _usecase;
};

TEST_F(user_register_integration_test, should_throw_with_malformed_username) {
  std::string const malformed_username{"a"};
  std::string const password{"goodpassword"};
  std::string const email{"test@test.com"};

  try {
    _usecase->execute(malformed_username, password, email);
    FAIL() << "Exception expected";
  } catch (username_exception const& ex) {
    ASSERT_EQ(ex.error_code(), username_validation_error_codes::username_is_too_short);
  }
}

TEST_F(user_register_integration_test, should_throw_with_malformed_password) {
  std::string const username{"goodusername"};
  std::string const malformed_password{"a"};
  std::string const email{"test@test.com"};

  try {
    _usecase->execute(username, malformed_password, email);
    FAIL() << "Exception expected";
  } catch (password_exception const& ex) {
    ASSERT_EQ(ex.error_code(), password_validation_error_codes::password_is_too_short);
  }
}

TEST_F(user_register_integration_test, should_throw_with_malformed_email) {
  std::string const username{"goodusername"};
  std::string const password{"goodpassword"};
  std::string const malformed_email{"a$ab@"};

  try {
    _usecase->execute(username, password, malformed_email);
    FAIL() << "Exception expected";
  } catch (email_exception const &ex) {
    ASSERT_EQ(ex.error_code(), email_validation_error_codes::email_is_not_valid);
  }
}

TEST_F(user_register_integration_test, should_throw_with_existing_username) {
  std::string const username{"validuser"};
  std::string const password{"goodpassword"};
  std::string const email{"different@email.com"};

  try {
    _usecase->execute(username, password, email);
    FAIL() << "Exception expected";
  } catch (user_usecase_register_exception const &ex) {
    ASSERT_EQ(ex.error_code(), user_usecase_register_error_codes::username_already_exists);
  }
}

TEST_F(user_register_integration_test, should_throw_with_existing_email) {
  std::string const username{"newusername"};
  std::string const password{"goodpassword"};
  std::string const email{"valid@email.com"};

  try {
    _usecase->execute(username, password, email);
    FAIL() << "Exception expected";
  } catch (user_usecase_register_exception const &ex) {
    ASSERT_EQ(ex.error_code(), user_usecase_register_error_codes::email_already_exists);
  }
}

TEST_F(user_register_integration_test, should_insert_user_with_valid_input) {
  std::string const username{"newusername"};
  std::string const password{"goodpassword"};
  std::string const email{"new@email.com"};

  auto uuid = _usecase->execute(username, password, email);

  ASSERT_FALSE(uuid.empty());
}

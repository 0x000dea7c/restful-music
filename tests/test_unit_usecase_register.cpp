#include "email.hpp"
#include "password.hpp"
#include "user_usecase_register.hpp"
#include "mock_password_encryptor.hpp"
#include "mock_database_repository.hpp"
#include "username.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Return;
using ::testing::Throw;

class user_unit_usecase_register_test : public ::testing::Test {
protected:
  mock_password_encryptor _mock_encryptor;
  mock_database_repository _mock_repository;
  user_usecase_register _usecase{_mock_encryptor, _mock_repository};
};

TEST_F(user_unit_usecase_register_test, should_throw_with_invalid_username) {
  std::string const username_short{"a"};
  std::string const password{"test123abc"};
  std::string const email{"test@test.com"};

  EXPECT_CALL(_mock_encryptor, encrypt(_)).Times(0);
  EXPECT_CALL(_mock_repository, user_username_exists(_)).Times(0);
  EXPECT_CALL(_mock_repository, user_email_exists(_)).Times(0);
  EXPECT_CALL(_mock_repository, user_insert(_)).Times(0);

  try {
    _usecase.execute(username_short, password, email);
    FAIL() << "Exception expected";
  } catch (username_exception const& ex) {
    ASSERT_EQ(ex.error_code(), username_validation_error_codes::username_is_too_short);
  }
}

TEST_F(user_unit_usecase_register_test, should_throw_with_invalid_password) {
  std::string const username("goodusername");
  std::string const password_long{std::string(129, 'a')};
  std::string const email{"test@test.com"};

  EXPECT_CALL(_mock_encryptor, encrypt(_)).Times(0);
  EXPECT_CALL(_mock_repository, user_username_exists(_)).Times(0);
  EXPECT_CALL(_mock_repository, user_email_exists(_)).Times(0);
  EXPECT_CALL(_mock_repository, user_insert(_)).Times(0);

  try {
    _usecase.execute(username, password_long, email);
    FAIL() << "Exception expected";
  } catch (password_exception const& ex) {
    ASSERT_EQ(ex.error_code(), password_validation_error_codes::password_is_too_long);
  }
}

TEST_F(user_unit_usecase_register_test, should_throw_with_invalid_email) {
  std::string const username("goodusername");
  std::string const password{"goodpassword"};
  std::string const email_without_domain{"test@"};

  EXPECT_CALL(_mock_encryptor, encrypt(_)).Times(0);
  EXPECT_CALL(_mock_repository, user_username_exists(_)).Times(0);
  EXPECT_CALL(_mock_repository, user_email_exists(_)).Times(0);
  EXPECT_CALL(_mock_repository, user_insert(_)).Times(0);

  try {
    _usecase.execute(username, password, email_without_domain);
    FAIL() << "Exception expected";
  } catch (email_exception const& ex) {
    ASSERT_EQ(ex.error_code(), email_validation_error_codes::email_is_not_valid);
  }
}

TEST_F(user_unit_usecase_register_test, should_throw_with_used_username) {
  std::string const username("goodusername");
  std::string const password{"goodpassword"};
  std::string const email{"test@domain.com"};

  EXPECT_CALL(_mock_encryptor, encrypt(_)).WillOnce(Return("encrypted_password"));
  EXPECT_CALL(_mock_repository, user_username_exists(_)).WillOnce(Return(true));
  EXPECT_CALL(_mock_repository, user_email_exists(_)).Times(0);
  EXPECT_CALL(_mock_repository, user_insert(_)).Times(0);

  try {
    _usecase.execute(username, password, email);
    FAIL() << "Exception expected";
  } catch (user_usecase_register_exception const& ex) {
    ASSERT_EQ(ex.error_code(), user_usecase_register_error_codes::username_already_exists);
  }
}

TEST_F(user_unit_usecase_register_test, should_throw_with_used_email) {
  std::string const username("goodusername");
  std::string const password{"goodpassword"};
  std::string const email{"test@domain.com"};

  EXPECT_CALL(_mock_encryptor, encrypt(_)).WillOnce(Return("encrypted_password"));
  EXPECT_CALL(_mock_repository, user_username_exists(_)).WillOnce(Return(false));
  EXPECT_CALL(_mock_repository, user_email_exists(_)).WillOnce(Return(true));
  EXPECT_CALL(_mock_repository, user_insert(_)).Times(0);

  try {
    _usecase.execute(username, password, email);
    FAIL() << "Exception expected";
  } catch (user_usecase_register_exception const& ex) {
    ASSERT_EQ(ex.error_code(), user_usecase_register_error_codes::email_already_exists);
  }
}

TEST_F(user_unit_usecase_register_test, should_throw_when_password_encryption_fails) {
  std::string const username("goodusername");
  std::string const password{"goodpassword"};
  std::string const email{"test@domain.com"};

  EXPECT_CALL(_mock_encryptor, encrypt(_))
    .WillOnce(Throw(password_encryptor_exception(password_encryptor_error_codes::ERROR_HASHING_FAILED)));
  EXPECT_CALL(_mock_repository, user_username_exists(_)).Times(0);
  EXPECT_CALL(_mock_repository, user_email_exists(_)).Times(0);
  EXPECT_CALL(_mock_repository, user_insert(_)).Times(0);

  try {
    _usecase.execute(username, password, email);
    FAIL() << "Exception expected";
  } catch (password_encryptor_exception const& ex) {
    ASSERT_EQ(ex.error_code(), password_encryptor_error_codes::ERROR_HASHING_FAILED);
  }
}

TEST_F(user_unit_usecase_register_test, should_throw_when_persistence_fails) {
  std::string const username("goodusername");
  std::string const password{"goodpassword"};
  std::string const email{"test@domain.com"};

  EXPECT_CALL(_mock_encryptor, encrypt(_)).WillOnce(Return("encrypted_password"));
  EXPECT_CALL(_mock_repository, user_username_exists(_)).Times(1);
  EXPECT_CALL(_mock_repository, user_email_exists(_)).Times(1);
  EXPECT_CALL(_mock_repository, user_insert(_))
    .WillOnce(Throw(database_repository_exception(database_repository_error_codes::ERROR_INSERT_USER)));

  try {
    _usecase.execute(username, password, email);
    FAIL() << "Exception expected";
  } catch (database_repository_exception const& ex) {
    ASSERT_EQ(ex.error_code(), database_repository_error_codes::ERROR_INSERT_USER);
  }
}

TEST_F(user_unit_usecase_register_test, should_return_uuid_with_valid_input) {
  std::string const username("goodusername");
  std::string const password{"goodpassword"};
  std::string const email{"test@domain.com"};

  EXPECT_CALL(_mock_encryptor, encrypt(_)).WillOnce(Return("encrypted_password"));
  EXPECT_CALL(_mock_repository, user_username_exists(_)).Times(1);
  EXPECT_CALL(_mock_repository, user_email_exists(_)).Times(1);
  EXPECT_CALL(_mock_repository, user_insert(_)).WillOnce(Return());

  try {
    auto uuid = _usecase.execute(username, password, email);
    ASSERT_FALSE(uuid.empty());
  } catch (std::runtime_error const& ex) {
    FAIL() << "No exception expected";
  }
}

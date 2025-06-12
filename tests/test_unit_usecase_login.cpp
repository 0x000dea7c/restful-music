#include "database_repository.hpp"
#include "mock_database_repository.hpp"
#include "mock_jwt_service.hpp"
#include "mock_password_encryptor.hpp"
#include "password.hpp"
#include "user_usecase_login.hpp"
#include "username.hpp"
#include "gmock/gmock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Return;
using ::testing::Throw;

class user_unit_usecase_login_test : public ::testing::Test {
protected:
  mock_password_encryptor _mock_encryptor;
  mock_database_repository _mock_repository;
  mock_jwt_service _mock_jwt_service;
  user_usecase_login _usecase{_mock_encryptor, _mock_repository,
                              _mock_jwt_service};
};

TEST_F(user_unit_usecase_login_test, should_throw_with_invalid_username) {
  std::string const invalid_username{"a"};
  std::string const password{"abcabc123"};

  EXPECT_CALL(_mock_repository, user_get_password(_)).Times(0);
  EXPECT_CALL(_mock_jwt_service, create_token(_, _, _)).Times(0);
  EXPECT_CALL(_mock_encryptor, passwords_match(_, _)).Times(0);

  try {
    _usecase.execute(invalid_username, password);
    FAIL() << "Exception expected";
  } catch (username_exception const &ex) {
    ASSERT_EQ(ex.error_code(),
              username_validation_error_codes::username_is_too_short);
  }
}

TEST_F(user_unit_usecase_login_test, should_throw_with_invalid_password) {
  std::string const username{"goodusername"};
  std::string const invalid_password{"a"};

  EXPECT_CALL(_mock_repository, user_get_password(_)).Times(0);
  EXPECT_CALL(_mock_jwt_service, create_token(_, _, _)).Times(0);
  EXPECT_CALL(_mock_encryptor, passwords_match(_, _)).Times(0);

  try {
    _usecase.execute(username, invalid_password);
    FAIL() << "Exception expected";
  } catch (password_exception const &ex) {
    ASSERT_EQ(ex.error_code(),
              password_validation_error_codes::password_is_too_short);
  }
}

TEST_F(user_unit_usecase_login_test, should_throw_with_non_existing_username) {
  std::string const username{"goodusername"};
  std::string const password{"abcabc123"};

  EXPECT_CALL(_mock_repository, user_get_password(_)).WillOnce(Return(""));
  EXPECT_CALL(_mock_jwt_service, create_token(_, _, _)).Times(0);
  EXPECT_CALL(_mock_encryptor, passwords_match(_, _)).Times(0);

  try {
    _usecase.execute(username, password);
    FAIL() << "Exception expected";
  } catch (user_usecase_login_exception const &ex) {
    ASSERT_EQ(ex.error_code(),
              user_usecase_login_error_codes::user_does_not_exist);
  }
}

TEST_F(user_unit_usecase_login_test, should_throw_with_non_matching_passwords) {
  std::string const username{"goodusername"};
  std::string const password{"abcabc123"};

  EXPECT_CALL(_mock_repository, user_get_password(_))
      .WillOnce(Return("valid-password"));
  EXPECT_CALL(_mock_encryptor, passwords_match(_, _)).Times(1);
  EXPECT_CALL(_mock_jwt_service, create_token(_, _, _)).Times(0);

  try {
    _usecase.execute(username, password);
    FAIL() << "Exception expected";
  } catch (user_usecase_login_exception const &ex) {
    ASSERT_EQ(ex.error_code(),
              user_usecase_login_error_codes::invalid_password);
  }
}

TEST_F(user_unit_usecase_login_test,
       should_throw_with_database_repository_error) {
  std::string const username{"goodusername"};
  std::string const password{"abcabc123"};

  EXPECT_CALL(_mock_repository, user_get_password(_))
      .WillOnce(Throw(database_repository_exception{
          database_repository_error_codes::GENERIC}));
  EXPECT_CALL(_mock_jwt_service, create_token(_, _, _)).Times(0);

  try {
    _usecase.execute(username, password);
    FAIL() << "Exception expected";
  } catch (database_repository_exception const &ex) {
    ASSERT_EQ(ex.error_code(), database_repository_error_codes::GENERIC);
  }
}

TEST_F(user_unit_usecase_login_test, should_return_token_with_valid_input) {
  std::string const username{"goodusername"};
  std::string const password{"valid-password"};

  EXPECT_CALL(_mock_repository, user_get_password(_)).WillOnce(Return("valid-password"));
  EXPECT_CALL(_mock_encryptor, passwords_match(_, _)).WillOnce(Return(true));
  EXPECT_CALL(_mock_jwt_service, create_token(_, _, _)).Times(1);

  _usecase.execute(username, password);
}

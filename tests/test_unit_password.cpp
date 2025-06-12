#include <gtest/gtest.h>
#include "password.hpp"

TEST(PasswordTests, should_throw_exception_with_empty_password) {
  try {
    password password_empty("");
    FAIL() << "Expected exception\n";
  } catch (password_exception const& ex) {
    ASSERT_EQ(ex.error_code(), password_validation_error_codes::password_is_empty);
  }
}

TEST(PasswordTests, should_throw_exception_with_short_password) {
  try {
    password password_short("abcdf");
   FAIL() << "Expected exception\n";
  } catch (password_exception const& ex) {
    ASSERT_EQ(ex.error_code(), password_validation_error_codes::password_is_too_short);
  }
}

TEST(PasswordTests, should_throw_exception_with_long_password) {
  try {
    password password_long(std::string(129, 'a'));
   FAIL() << "Expected exception\n";
  } catch (password_exception const& ex) {
    ASSERT_EQ(ex.error_code(), password_validation_error_codes::password_is_too_long);
  }
}

TEST(PasswordTests, should_create_password_with_valid_input_and_returns_its_value) {
  password password_valid("test123abc_easyas_123");
  ASSERT_EQ(password_valid.value(), "test123abc_easyas_123");
}

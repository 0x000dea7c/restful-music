#include <gtest/gtest.h>
#include "username.hpp"

TEST(UsernameTests, should_throw_exception_with_empty_username) {
  try {
    username username_empty("");
    FAIL() << "Expected exception\n";
  } catch (username_exception const& ex) {
    ASSERT_EQ(ex.error_code(), username_validation_error_codes::username_is_empty);
  }
}

TEST(UsernameTests, should_throw_exception_with_short_username) {
  try {
    username username_short("abc");
    FAIL() << "Expected exception\n";
  } catch (username_exception const& ex) {
    ASSERT_EQ(ex.error_code(), username_validation_error_codes::username_is_too_short);
  }
}

TEST(UsernameTests, should_throw_exception_with_long_username) {
  try {
    username username_very_long("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    FAIL() << "Expected exception\n";
  } catch (username_exception const& ex) {
    ASSERT_EQ(ex.error_code(), username_validation_error_codes::username_is_too_long);
  }

  try {
    username username_long_by_1("qwertyuiopasdfgh0");
    FAIL() << "Expected exception\n";
  } catch (username_exception const& ex) {
    ASSERT_EQ(ex.error_code(), username_validation_error_codes::username_is_too_long);
  }
}

TEST(UsernameTests, should_throw_exception_with_invalid_characters) {
  try {
    username username_with_numbers("test123");
    FAIL() << "Expected exception\n";
  } catch (username_exception const& ex) {
    ASSERT_EQ(ex.error_code(), username_validation_error_codes::username_contains_invalid_characters);
  }

  try {
    username username_with_invalid_characters("test_@{[]}");
    FAIL() << "Expected exception\n";
  } catch (username_exception const& ex) {
    ASSERT_EQ(ex.error_code(), username_validation_error_codes::username_contains_invalid_characters);
  }
}

TEST(UsernameTests, should_create_username_with_valid_input_and_return_its_value) {
  username username_with_minimum_length("lain");
  username username_with_maximum_length("jamesjamesjamesp");
  username username_typical("eileen");

  EXPECT_EQ(username_with_minimum_length.value(), "lain");
  EXPECT_EQ(username_with_maximum_length.value(), "jamesjamesjamesp");
  EXPECT_EQ(username_typical.value(), "eileen");
}

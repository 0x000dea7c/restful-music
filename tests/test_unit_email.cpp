#include "email.hpp"
#include <gtest/gtest.h>

TEST(EmailTests, should_throw_exception_with_empty_email) {
  try {
    email email_empty("");
    FAIL() << "Expected exception\n";
  } catch (email_exception const &ex) {
    ASSERT_EQ(ex.error_code(), email_validation_error_codes::email_is_empty);
  }
}

TEST(EmailTests, should_throw_exception_with_email_without_domain) {
  try {
    email email_no_domain("test_email");
    FAIL() << "Expected exception\n";
  } catch (email_exception const &ex) {
    ASSERT_EQ(ex.error_code(),
              email_validation_error_codes::email_is_not_valid);
  }

  try {
    email email_no_domain("test_email@");
    FAIL() << "Expected exception\n";
  } catch (email_exception const &ex) {
    ASSERT_EQ(ex.error_code(),
              email_validation_error_codes::email_is_not_valid);
  }
}

TEST(EmailTests, should_throw_exception_with_email_without_username) {
  try {
    email email_no_username("@yeehaw.com");
    FAIL() << "Expected exception\n";
  } catch (email_exception const &ex) {
    ASSERT_EQ(ex.error_code(),
              email_validation_error_codes::email_is_not_valid);
  }
}

TEST(EmailTests, should_throw_exception_with_email_with_invalid_characters) {
  try {
    email email_invalid("abc$@yeehaw.com");
    FAIL() << "Expected exception\n";
  } catch (email_exception const &ex) {
    ASSERT_EQ(ex.error_code(),
              email_validation_error_codes::email_is_not_valid);
  }
}

TEST(EmailTests, should_create_email_with_valid_input_and_return_its_value) {
  email email_valid("cowboy@yeehaw.com");
  ASSERT_EQ(email_valid.value(), "cowboy@yeehaw.com");
}

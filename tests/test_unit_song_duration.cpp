#include "song_duration.hpp"
#include <gtest/gtest.h>

TEST(song_duration_unit_test, should_throw_with_no_duration) {
  try {
    song_duration duration(0);
    FAIL() << "Exception expected";
  } catch (song_duration_exception const &ex) {
    ASSERT_EQ(ex.error_code(),
              song_duration_validation_error_codes::song_duration_zero);
  }
}

TEST(song_duration_unit_test, should_throw_with_long_duration) {
  try {
    song_duration duration(86401);
    FAIL() << "Exception expected";
  } catch (song_duration_exception const &ex) {
    ASSERT_EQ(ex.error_code(),
              song_duration_validation_error_codes::song_duration_too_long);
  }
}

TEST(song_duration_unit_test, should_create_duration_with_valid_input) {
  song_duration duration(3600);
  ASSERT_EQ(duration.value(), 3600);
}

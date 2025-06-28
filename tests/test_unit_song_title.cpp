#include <gtest/gtest.h>
#include "song_title.hpp"

TEST(song_title_unit_test, should_throw_with_empty_title) {
  std::string empty_title{""};

  try {
    song_title title(empty_title);
    FAIL() << "Exception expected";
  } catch (song_title_exception const& ex) {
    ASSERT_EQ(ex.error_code(), song_title_validation_error_codes::song_title_empty);
  }
}

TEST(song_title_unit_test, should_throw_with_long_title) {
  std::string long_title(129, 'a');

  try {
    song_title title(long_title);
    FAIL() << "Exception expected";
  } catch (song_title_exception const& ex) {
    ASSERT_EQ(ex.error_code(), song_title_validation_error_codes::song_title_too_long);
  }
}

TEST(song_title_unit_test, should_create_title_with_valid_input) {
  std::string valid_title{"I want a job"};

  song_title title(valid_title);

  ASSERT_EQ(title.value(), valid_title);
}

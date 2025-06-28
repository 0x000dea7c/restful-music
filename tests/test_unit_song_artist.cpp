#include "song_artist.hpp"
#include <gtest/gtest.h>

TEST(song_artist_unit_test, should_throw_with_empty_artist) {
  std::string empty_artist{""};

  try {
    song_artist title(empty_artist);
    FAIL() << "Exception expected";
  } catch (song_artist_exception const &ex) {
    ASSERT_EQ(ex.error_code(),
              song_artist_validation_error_codes::song_artist_empty);
  }
}

TEST(song_artist_unit_test, should_throw_with_long_artist) {
  std::string long_artist_name(129, 'a');

  try {
    song_artist title(long_artist_name);
    FAIL() << "Exception expected";
  } catch (song_artist_exception const &ex) {
    ASSERT_EQ(ex.error_code(),
              song_artist_validation_error_codes::song_artist_too_long);
  }
}

TEST(song_artist_unit_test, should_create_artist_with_valid_input) {
  std::string valid_title{"I want a job"};

  song_artist title(valid_title);

  ASSERT_EQ(title.value(), valid_title);
}

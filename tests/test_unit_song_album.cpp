#include "song_album.hpp"
#include <gtest/gtest.h>

TEST(song_album_unit_test, should_throw_with_empty_album) {
  std::string empty_album{""};

  try {
    song_album title(empty_album);
    FAIL() << "Exception expected";
  } catch (song_album_exception const &ex) {
    ASSERT_EQ(ex.error_code(),
              song_album_validation_error_codes::song_album_empty);
  }
}

TEST(song_album_unit_test, should_throw_with_long_album) {
  std::string long_album_name(129, 'a');

  try {
    song_album title(long_album_name);
    FAIL() << "Exception expected";
  } catch (song_album_exception const &ex) {
    ASSERT_EQ(ex.error_code(),
              song_album_validation_error_codes::song_album_too_long);
  }
}

TEST(song_album_unit_test, should_create_album_with_valid_input) {
  std::string valid_title{"I want a job"};

  song_album title(valid_title);

  ASSERT_EQ(title.value(), valid_title);
}

#include "song_release_date.hpp"
#include <gtest/gtest.h>

TEST(song_artist_unit_test, should_throw_with_invalid_date) {
  try {
    song_release_date date(1, 0, 0);
    FAIL() << "Exception expected";
  } catch (song_release_date_exception const &ex) {
    ASSERT_EQ(ex.error_code(), song_release_date_validation_error_codes::
                                   song_release_date_invalid_date);
  }
}

TEST(song_artist_unit_test, should_create_release_date_with_valid_input) {
  using namespace std::chrono;

  song_release_date date(2005, 1, 10);

  ASSERT_EQ(date.value(), std::chrono::year_month_day(2005y, std::chrono::January, 10d));
}

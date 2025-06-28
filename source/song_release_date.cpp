#include "song_release_date.hpp"
#include <chrono>

song_release_date::song_release_date(int year, unsigned int month,
                                     unsigned int day) {
  if (year < 0) {
    throw song_release_date_exception{song_release_date_validation_error_codes::
                                          song_release_date_invalid_date};
  }

  _release_date = std::chrono::year_month_day(std::chrono::year(year),
                                              std::chrono::month(month),
                                              std::chrono::day(day));

  if (!_release_date.ok()) {
    throw song_release_date_exception{song_release_date_validation_error_codes::
                                          song_release_date_invalid_date};
  }
}

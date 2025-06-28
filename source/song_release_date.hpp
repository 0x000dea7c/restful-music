#pragma once

#include <chrono>

enum class song_release_date_validation_error_codes {
  song_release_date_invalid_date
};

class song_release_date_exception : public std::runtime_error {
public:
  explicit song_release_date_exception(song_release_date_validation_error_codes error_code)
      : std::runtime_error(""), _error_code{error_code} {}

  auto error_code() const { return _error_code; }

private:
  song_release_date_validation_error_codes _error_code;
};

class song_release_date {
public:
  song_release_date(int year, unsigned int month, unsigned int day);

  auto value() const { return _release_date; }

private:
  std::chrono::year_month_day _release_date;
};

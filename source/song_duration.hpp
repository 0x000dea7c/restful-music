#pragma once

#include <stdexcept>

enum class song_duration_validation_error_codes {
  song_duration_zero,
  song_duration_too_long,
};

class song_duration_exception : public std::runtime_error {
public:
  explicit song_duration_exception(song_duration_validation_error_codes error_code)
      : std::runtime_error(""), _error_code{error_code} {}

  auto error_code() const { return _error_code; }

private:
  song_duration_validation_error_codes _error_code;
};

class song_duration {
public:
  explicit song_duration(unsigned int duration);

  auto value() const { return _duration; }

private:
  unsigned int _duration;
};

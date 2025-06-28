#pragma once

#include <stdexcept>
#include <string>

enum class song_title_validation_error_codes {
  song_title_empty,
  song_title_too_long,
};

class song_title_exception : public std::runtime_error {
public:
  explicit song_title_exception(song_title_validation_error_codes error_code)
      : std::runtime_error(""), _error_code{error_code} {}

  auto error_code() const { return _error_code; }

private:
  song_title_validation_error_codes _error_code;
};

class song_title {
public:
  explicit song_title(std::string_view const &title);

  auto value() const { return _title; }

private:
  std::string _title;
};

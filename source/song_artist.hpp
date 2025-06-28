#pragma once

#include <string_view>
#include <string>
#include <stdexcept>

enum class song_artist_validation_error_codes {
  song_artist_empty,
  song_artist_too_long,
};

class song_artist_exception : public std::runtime_error {
public:
  explicit song_artist_exception(song_artist_validation_error_codes error_code)
      : std::runtime_error(""), _error_code{error_code} {}

  auto error_code() const { return _error_code; }

private:
  song_artist_validation_error_codes _error_code;
};

class song_artist {
public:
  explicit song_artist(std::string_view const& artist);

  auto value() const { return _artist; }

private:
  std::string _artist;
};

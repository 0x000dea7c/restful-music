#pragma once

#include <stdexcept>
#include <string_view>

enum class song_album_validation_error_codes {
  song_album_empty,
  song_album_too_long,
};

class song_album_exception : public std::runtime_error {
public:
  explicit song_album_exception(song_album_validation_error_codes error_code)
      : std::runtime_error(""), _error_code{error_code} {}

  auto error_code() const { return _error_code; }

private:
  song_album_validation_error_codes _error_code;
};

class song_album {
public:
  explicit song_album(std::string_view const &album);

  auto value() const { return _album; }

private:
  std::string _album;
};

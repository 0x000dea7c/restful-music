#include "song_album.hpp"

int constexpr song_album_maximum_length{128};

song_album::song_album(std::string_view const &album) {
  if (album.empty()) {
    throw song_album_exception{
        song_album_validation_error_codes::song_album_empty};
  }

  if (album.length() > song_album_maximum_length) {
    throw song_album_exception{
        song_album_validation_error_codes::song_album_too_long};
  }

  _album = album;
}

#include "song_artist.hpp"

int constexpr song_artist_maximum_length{128};

song_artist::song_artist(std::string_view const &artist) {
  if (artist.empty()) {
    throw song_artist_exception{
        song_artist_validation_error_codes::song_artist_empty};
  }

  if (artist.length() > song_artist_maximum_length) {
    throw song_artist_exception{song_artist_validation_error_codes::song_artist_too_long};
  }

  _artist = artist;
}

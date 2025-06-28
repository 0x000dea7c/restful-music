#include "song_duration.hpp"

unsigned int constexpr song_duration_maximum{86400};

song_duration::song_duration(unsigned int duration) {
  if (duration == 0) {
    throw song_duration_exception{
        song_duration_validation_error_codes::song_duration_zero};
  }

  if (duration > song_duration_maximum) {
    throw song_duration_exception{
        song_duration_validation_error_codes::song_duration_too_long};
  }

  _duration = duration;
}

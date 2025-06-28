#include "song_title.hpp"

int constexpr song_title_maximum_length{128};

song_title::song_title(std::string_view const &title)
{
  if (title.empty()) {
    throw song_title_exception{song_title_validation_error_codes::song_title_empty};
  }

  if (title.length() > song_title_maximum_length) {
    throw song_title_exception{song_title_validation_error_codes::song_title_too_long};
  }

  _title = title;
}

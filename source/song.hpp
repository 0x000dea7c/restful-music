#pragma once

#include "song_album.hpp"
#include "song_artist.hpp"
#include "song_duration.hpp"
#include "song_release_date.hpp"
#include "song_title.hpp"
#include "uuid.hpp"

class song
{
public:

private:
  uuid _uuid;
  song_title _title;
  song_artist _artist;
  song_album _album;
  song_release_date _release_date;
  song_duration _duration;
};

#pragma once

#include <string>
#include <chrono>

class song
{
public:

private:
  std::string _title;
  std::string _artist;
  std::string _album;
  std::chrono::year_month_day _release_date;
  std::chrono::seconds _duration;
};

#pragma once

#include <string>

// TODO: I think this class is not well designed
class uuid
{
public:
  explicit uuid();

  auto value() const { return _uuid; }

  static std::string generate();

private:
  std::string _uuid;
};

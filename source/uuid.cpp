#include "uuid.hpp"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

uuid::uuid() {
  // OPTIMISE: the random generator can be static maybe?
  boost::uuids::random_generator gen;
  boost::uuids::uuid user_uuid = gen();
  _uuid = boost::uuids::to_string(user_uuid);
}

std::string uuid::generate() {
  return std::string(
      boost::uuids::to_string(boost::uuids::random_generator()()));
}

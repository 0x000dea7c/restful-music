#include "user.hpp"
#include <boost/uuid/uuid_generators.hpp>

user::user(username const& username,
           password const& password,
           email const& email,
           uuid const& uuid)
  : _username{username},
    _password{password},
    _email{email},
    _uuid{uuid}
{
}

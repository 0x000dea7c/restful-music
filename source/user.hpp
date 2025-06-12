#pragma once

#include "email.hpp"
#include "password.hpp"
#include "username.hpp"
#include "uuid.hpp"

class user
{
public:
  user(username const& username,
       password const& password,
       email const& email,
       uuid const& uuid);

  auto username_value() const { return _username; }

  auto password_value() const { return _password; }

  auto email_value() const { return _email; }

  auto uuid_value() const { return _uuid; }

private:
  username const _username;
  password const _password;
  email const _email;
  uuid const _uuid;
};

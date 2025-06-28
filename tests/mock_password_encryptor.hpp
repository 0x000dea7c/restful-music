#pragma once

#include "password_encryptor.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

class mock_password_encryptor : public password_encryptor {
public:
  MOCK_METHOD(std::string, encrypt, (std::string_view const &password),
              (const, override));

  MOCK_METHOD(bool, passwords_match,
              (std::string_view const &, std::string_view const &),
              (const, override));
};

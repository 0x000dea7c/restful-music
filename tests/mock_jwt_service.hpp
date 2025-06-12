#pragma once

#include "jwt_service.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class mock_jwt_service : public jwt_service {
public:
  MOCK_METHOD(std::string, create_token,
              (std::string_view const &username, std::string_view const &uuid,
               std::chrono::system_clock::time_point expires_at),
              (const, override));
};

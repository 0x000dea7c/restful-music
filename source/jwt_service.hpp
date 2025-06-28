#pragma once

#include <chrono>
#include <string>

class jwt_service {
public:
  virtual ~jwt_service() = default;

  virtual std::string
  create_token(std::string_view const &username, std::string_view const &uuid,
               std::chrono::system_clock::time_point expires_at) const = 0;
};

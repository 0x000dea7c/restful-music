#include "jwt_service.hpp"
#include <chrono>
#include <format>
#include <string>
#include <string_view>

class fake_jwt_service : public jwt_service {
public:
  std::string create_token(
      std::string_view const &username, std::string_view const &uuid,
      std::chrono::system_clock::time_point expires_at) const override {
    return std::format(
        "fake_token_{}_{}_{}", username, uuid,
        std::to_string(std::chrono::system_clock::to_time_t(expires_at)));
  }
};

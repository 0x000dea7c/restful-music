#include "jwt_service_impl.hpp"
#include <jwt-cpp/jwt.h>

jwt_service_impl::jwt_service_impl(config &config) : _config{config} {}

std::string jwt_service_impl::create_token(
    std::string_view const &username, std::string_view const &uuid,
    std::chrono::system_clock::time_point expires_at) const {

  return jwt::create()
      .set_issuer(_config.jwt_issuer())
      .set_subject(username.data())
      .set_payload_claim("uuid", jwt::claim(std::string(uuid)))
      .set_expires_at(expires_at)
      .sign(jwt::algorithm::hs256{_config.jwt_secret()});
}

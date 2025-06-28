#include "config.hpp"
#include "jwt_service.hpp"
#include <string>

class jwt_service_impl : public jwt_service {
public:
  explicit jwt_service_impl(config &config);

  std::string
  create_token(std::string_view const &username, std::string_view const &uuid,
               std::chrono::system_clock::time_point expires_at) const override;

private:
  config &_config;
};

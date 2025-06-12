#include "config.hpp"
#include "database_repository_sqlite.hpp"
#include "jwt_service_impl.hpp"
#include "password_encryptor_sodium.hpp"
#include "user_controller.hpp"
#include <crow/app.h>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main() {
  try {
    config config;
    crow::SimpleApp app;
    password_encryptor_sodium password_encryptor;
    database_repository_sqlite database_repository(config.database_name());
    jwt_service_impl jwt_service(config);
    user_controller user_controller(password_encryptor, database_repository, jwt_service);

    CROW_ROUTE(app, "/users/register")
        .methods(crow::HTTPMethod::POST)(
            [&user_controller](crow::request &request,
                               crow::response &response) {
              user_controller.user_register(request, response);
            });

    CROW_ROUTE(app, "/users/login")
        .methods(crow::HTTPMethod::POST)(
            [&user_controller](crow::request &request,
                               crow::response &response) {
              user_controller.user_login(request, response);
            });

    app.port(static_cast<std::uint16_t>(config.port())).multithreaded().run();
  } catch (password_encryptor_exception const &ex) {
    std::cerr << "Couldn't initialise libsodium" << '\n';
  } catch (config_exception const &ex) {
    std::cerr << ex.what() << '\n';
  } catch (std::runtime_error const &ex) {
    std::cerr << "Unknown error: " << ex.what() << '\n';
  }

  return EXIT_SUCCESS;
}

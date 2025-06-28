#include "user_controller.hpp"
#include "http_status_codes.hpp"
#include "password.hpp"
#include "password_encryptor.hpp"
#include "database_repository.hpp"
#include "jwt_service.hpp"
#include <crow/app.h>
#include "user_usecase_login.hpp"
#include "user_usecase_register.hpp"

// RAII to avoid calling response.end() every god damn time
class crow_response_scoped {
public:
  explicit crow_response_scoped(crow::response& response)
    : _response{response}
  {}

  ~crow_response_scoped() { _response.end(); }

private:
  crow::response& _response;
};

user_controller::user_controller(password_encryptor &password_encryptor,
                                 database_repository &database_repository,
                                 jwt_service &jwt_service)
    : _password_encryptor{password_encryptor},
      _database_repository{database_repository}, _jwt_service{jwt_service} {}

void user_controller::user_register(crow::request const& request, crow::response& response)
{
  crow::json::wvalue response_json;
  crow_response_scoped const scoped(response);
  auto request_json = crow::json::load(request.body);

  if (!request_json || request_json.keys().empty()) {
    response.code = static_cast<int>(http_status_codes::BAD_REQUEST);
    response_json["error"] = "Invalid JSON";
    response.body = response_json.dump();
    return;
  }

  if (!request_json.has("username")) {
    response.code = static_cast<int>(http_status_codes::BAD_REQUEST);
    response_json["error"] = get_error_message_username_empty();
    response.body = response_json.dump();
    return;
  }

  if (!request_json.has("password")) {
    response.code = static_cast<int>(http_status_codes::BAD_REQUEST);
    response_json["error"] = get_error_message_password_empty();
    response.body = response_json.dump();
    return;
  }

  if (!request_json.has("email")) {
    response.code = static_cast<int>(http_status_codes::BAD_REQUEST);
    response_json["error"] = get_error_message_email_empty();
    response.body = response_json.dump();
    return;
  }

  if (request_json["username"].t() != crow::json::type::String) {
    response.code = static_cast<int>(http_status_codes::BAD_REQUEST);
    response_json["error"] = get_error_message_username_malformed();
    response.body = response_json.dump();
    return;
  }

  if (request_json["password"].t() != crow::json::type::String) {
    response.code = static_cast<int>(http_status_codes::BAD_REQUEST);
    response_json["error"] = get_error_message_password_malformed();
    response.body = response_json.dump();
    return;
  }

  if (request_json["email"].t() != crow::json::type::String) {
    response.code = static_cast<int>(http_status_codes::BAD_REQUEST);
    response_json["error"] = get_error_message_email_malformed();
    response.body = response_json.dump();
    return;
  }

  std::string const string_username = request_json["username"].s();
  std::string const string_password = request_json["password"].s();
  std::string const string_email = request_json["email"].s();

  user_usecase_register const usecase(_password_encryptor, _database_repository);

  try {
    auto user_new_uuid = usecase.execute(string_username, string_password, string_email);
    response.code = static_cast<int>(http_status_codes::OK);
    response_json["id"] = user_new_uuid;
  } catch (user_usecase_register_exception const& ex) {
    response.code = static_cast<int>(http_status_codes::BAD_REQUEST);
    response_json["error"] = get_register_usecase_error_message(ex.error_code());
  } catch (password_exception const &ex) {
    response.code = static_cast<int>(http_status_codes::BAD_REQUEST);
    response_json["error"] = get_password_error_message(ex.error_code());
  } catch (username_exception const &ex) {
    response.code = static_cast<int>(http_status_codes::BAD_REQUEST);
    response_json["error"] = get_username_error_message(ex.error_code());
  } catch (email_exception const &ex) {
    response.code = static_cast<int>(http_status_codes::BAD_REQUEST);
    response_json["error"] = get_email_error_message(ex.error_code());
  } catch (password_encryptor_exception const &ex) {
    response.code = static_cast<int>(http_status_codes::INTERNAL_SERVER_ERROR);
    response_json["error"] = get_password_encryptor_error_message(ex.error_code());
  } catch (database_repository_exception const &ex) {
    response.code = static_cast<int>(http_status_codes::INTERNAL_SERVER_ERROR);
    response_json["error"] = get_database_repository_error_message(ex.error_code());
  }

  response.body = response_json.dump();
}

void user_controller::user_login(crow::request const &request,
                                 crow::response &response)
{
  crow::json::wvalue response_json;
  crow_response_scoped const scoped(response);
  auto request_json = crow::json::load(request.body);

  if (!request_json || request_json.keys().empty()) {
    response_json["error"] = get_error_message_invalid_json();
    response.code = static_cast<int>(http_status_codes::BAD_REQUEST);
    response.body = response_json.dump();
    return;
  }

  if (!request_json.has("username")) {
    response_json["error"] = get_error_message_username_empty();
    response.code = static_cast<int>(http_status_codes::BAD_REQUEST);
    response.body = response_json.dump();
    return;
  }

  if (!request_json.has("password")) {
    response_json["error"] = get_error_message_password_empty();
    response.code = static_cast<int>(http_status_codes::BAD_REQUEST);
    response.body = response_json.dump();
    return;
  }

  if (request_json["username"].t() != crow::json::type::String) {
    response.code = static_cast<int>(http_status_codes::BAD_REQUEST);
    response_json["error"] = get_error_message_username_malformed();
    response.body = response_json.dump();
    return;
  }

  if (request_json["password"].t() != crow::json::type::String) {
    response.code = static_cast<int>(http_status_codes::BAD_REQUEST);
    response_json["error"] = get_error_message_password_malformed();
    response.body = response_json.dump();
    return;
  }

  std::string const string_username = request_json["username"].s();
  std::string const string_password = request_json["password"].s();

  user_usecase_login const usecase(_password_encryptor, _database_repository, _jwt_service);

  try {
    auto const token = usecase.execute(string_username, string_password);
    response.code = static_cast<int>(http_status_codes::OK);
    response_json["message"] = get_message_login_successful();
    response_json["token"] = token;
  } catch (user_usecase_login_exception const& ex) {
    response.code = static_cast<int>(http_status_codes::BAD_REQUEST);
    response_json["error"] = get_login_usecase_error_message(ex.error_code());
  } catch (username_exception const &ex) {
    response.code = static_cast<int>(http_status_codes::BAD_REQUEST);
    response_json["error"] = get_username_error_message(ex.error_code());
  } catch (password_exception const&) {
    response.code = static_cast<int>(http_status_codes::BAD_REQUEST);
    response_json["error"] = get_login_usecase_error_message(user_usecase_login_error_codes::invalid_password);
  } catch (database_repository_exception const&) {
    response.code = static_cast<int>(http_status_codes::INTERNAL_SERVER_ERROR);
    response_json["error"] = get_error_message_validating_password();
  }

  response.body = response_json.dump();
}

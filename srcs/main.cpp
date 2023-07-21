#include <fstream>
#include <iostream>
#include <string>

#include "ApiRequests.hpp"
#include "Authorization.hpp"
#include "ContentType.hpp"
#include "crow.h"

int main() {
    crow::App<ContentType, Authorization> app;
    app.loglevel(crow::LogLevel::INFO);  // default

    CROW_ROUTE(app, "/").CROW_MIDDLEWARES(
        app, Authorization)([]() { return "Hello world\n"; });

    CROW_ROUTE(app, "/auth/sign-up")
    ([](const crow::request& req) {
        crow::json::rvalue json = crow::json::load(req.body);
        if (!json) return crow::response(crow::status::BAD_REQUEST);
        return signUp(json);
    });

    CROW_ROUTE(app, "/auth/sign-in")
    ([](const crow::request& req) {
        crow::json::rvalue json = crow::json::load(req.body);
        if (!json) return crow::response(crow::status::BAD_REQUEST);
        return signIn(json);
    });

    app.port(18080).multithreaded().run();
}

// sql::mysql::MySQL_Driver *driver;
// sql::Connection *conn;

// std::ifstream f;  // TODO : replace with getenv()
// f.open(".env");
// std::string user, pass;
// f >> user >> pass;
// f.close();

// try {
//     driver = sql::mysql::get_mysql_driver_instance();
//     conn = driver->connect("tcp://127.0.0.1:3306", user, pass);

//     sql::Statement *stmt = conn->createStatement();
//     std::string query = R"(
//         CREATE TABLE server.tab (
//             ID int NOT NULL AUTO_INCREMENT,
//             test VARCHAR(100),
//             PRIMARY KEY (ID)
//         );
//     )";
//     sql::ResultSet *res = stmt->executeQuery(std::move(query));
//     while (res->next()) {
//         std::string name = res->getString("_message");
//         std::cout << name << std::endl;
//     }

// } catch (const std::exception &e) {
//     std::cerr << e.what() << std::endl;
// }

// CROW_ROUTE(app, "/test/<int>/<int>")
//     .methods(crow::HTTPMethod::POST)(
//         [](int a, int b) { return std::to_string(a + b) + '\n'; });
#include "server.h"
#include "utils.h"
#include <iostream>
#include <sstream>



Server::Server(URLShortener& shortener, int port)
    : shortener_(shortener), port_(port)
{
}

void Server::start() {
    std::cout << "=== URL Shortener running on port " << port_ << " ===" << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  shorten <url>  - Create a short URL" << std::endl;
    std::cout << "  resolve <code> - Look up a short code" << std::endl;
    std::cout << "  quit           - Exit" << std::endl;
    std::cout << std::endl;

    std::string line;
    while (std::cout << "> " && std::getline(std::cin, line)) {
        if (line == "quit") break;
        if (line.empty()) continue;

        // Parse the command and argument
        std::istringstream iss(line);
        std::string command, argument;
        iss >> command >> argument;

        // Build a Request and route it
        Request request;
        if (command == "shorten") {
            request.method = "POST";
            request.path = "/shorten";
            request.body = argument;
        } else if (command == "resolve") {
            request.method = "GET";
            request.path = "/" + argument;
        } else {
            std::cout << "Unknown command: " << command << std::endl;
            continue;
        }

        // Handle the request and print the response
        Response response = handle_request(request);
        std::cout << "[" << response.status_code << "] " << response.body;
        if (!response.redirect_url.empty()) {
            std::cout << " -> " << response.redirect_url;
        }
        std::cout << std::endl;
    }

    std::cout << "Goodbye!" << std::endl;
}

Response Server::handle_request(const Request& request) {
    if (request.method == "POST" && request.path == "/shorten") {
        return handle_shorten(request);
    } else if (request.method == "GET") {
        std::string code = request.path.substr(1); // Remove leading "/"
        if (!code.empty()) {
            return handle_redirect(code);
        }
    }
    return handle_not_found();
}

Response Server::handle_shorten(const Request& request) {
    const std::string& url = request.body;

    if (url.empty()) {
        return handle_bad_request("No URL provided");
    }

    if (!Utils::is_valid_url(url)) {
        return handle_bad_request("Invalid URL: " + url);
    }

    std::string code = shortener_.shorten(url);
    return Response{201, "Created: " + code, ""};
}

Response Server::handle_redirect(const std::string& short_code) {
    auto url = shortener_.resolve(short_code);
    if (url.has_value()) {
        return Response{301, "Redirecting...", url.value()};
    }
    return handle_not_found();
}

Response Server::handle_not_found() {
    return Response{404, "Not Found", ""};
}

Response Server::handle_bad_request(const std::string& message) {
    return Response{400, "Bad Request: " + message, ""};
}

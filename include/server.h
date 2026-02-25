#pragma once



#include <string>
#include "url_shortener.h"

// A simple struct to represent an HTTP-like request
struct Request {
    std::string method;   // "GET", "POST", "DELETE"
    std::string path;     // "/shorten", "/abc123"
    std::string body;     // JSON body for POST requests
};

// A simple struct to represent an HTTP-like response
struct Response {
    int status_code;          // 200, 201, 301, 404, 400
    std::string body;         // Response content
    std::string redirect_url; // For 301 redirects
};

class Server {
public:
    explicit Server(URLShortener& shortener, int port = 8080);

    // ========================================================================
    // TODO: Implement start()
    // ========================================================================
    // Start the server's main loop.
    //
    // FOR NOW (console version):
    //   - Print a welcome message
    //   - Loop: read user input, parse it, handle it, print response
    //   - Exit when user types "quit"
    //
    // LATER (HTTP version):
    //   - Bind to the port
    //   - Listen for incoming connections
    //   - Route requests to handle_request()
    // ========================================================================
    void start();

    // ========================================================================
    // TODO: Implement handle_request()
    // ========================================================================
    // Route a request to the appropriate handler based on method + path.
    //
    // Routing table:
    //   POST /shorten       → create a short URL
    //   GET  /{short_code}  → redirect to original URL
    //   GET  /stats         → show statistics (optional)
    //
    // THINK ABOUT:
    //   - How do you extract the short code from "GET /abc123"?
    //   - What status code for success? For not found? For bad input?
    //   - How do you parse JSON from the POST body? (start with simple parsing)
    // ========================================================================
    Response handle_request(const Request& request);

private:
    URLShortener& shortener_;
    int port_;

    // ========================================================================
    // TODO: Implement these private helpers
    // ========================================================================
    // Breaking handle_request into smaller functions makes it cleaner.
    //
    // THINK ABOUT:
    //   - Each handler does ONE thing (Single Responsibility)
    //   - They all return a Response struct
    //   - Error handling: what if the body is empty? URL is invalid?
    // ========================================================================
    Response handle_shorten(const Request& request);
    Response handle_redirect(const std::string& short_code);
    Response handle_not_found();
    Response handle_bad_request(const std::string& message);
};

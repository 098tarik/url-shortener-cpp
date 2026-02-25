#include <iostream>
#include <cassert>

#include "utils.h"
#include "storage.h"
#include "url_shortener.h"
#include "server.h"



void test_utils() {
    std::cout << "--- Testing Utils ---" << std::endl;

    // === Base62 Encoding Tests ===

    // Boundary: zero
    assert(Utils::encode_base62(0) == "0");

    // Single-character outputs (0–61 should each be one character)
    assert(Utils::encode_base62(1) == "1");
    assert(Utils::encode_base62(9) == "9");
    assert(Utils::encode_base62(10) == "a");    // First lowercase letter
    assert(Utils::encode_base62(35) == "z");    // Last lowercase letter
    assert(Utils::encode_base62(36) == "A");    // First uppercase letter
    assert(Utils::encode_base62(61) == "Z");    // Last single-char value

    // Two-character outputs (rollover at 62)
    assert(Utils::encode_base62(62) == "10");   // Like decimal 10 = "10"
    assert(Utils::encode_base62(63) == "11");
    assert(Utils::encode_base62(123) == "1Z");

    // Multi-character: known values
    assert(Utils::encode_base62(1000) == "g8");
    assert(Utils::encode_base62(9999) == "2Bh");

    // Large values stay compact
    assert(Utils::encode_base62(1000000).length() <= 4);   // Should be 4 chars
    assert(Utils::encode_base62(1000000000).length() <= 6); // Should be 6 chars

    std::cout << "  encode_base62: PASSED" << std::endl;

    assert(Utils::decode_base62("0") == 0);
    assert(Utils::decode_base62("Z") == 61);
    assert(Utils::decode_base62("10") == 62);
    assert(Utils::decode_base62("g8") == 1000);
    
    // Round-trip: encode then decode should give back the original
    for (uint64_t i = 0; i < 10000; i++) {
        assert(Utils::decode_base62(Utils::encode_base62(i)) == i);
    }
    
    std::cout << "  decode_base62: PASSED" << std::endl;

    assert(Utils::is_valid_url("https://example.com") == true);
    assert(Utils::is_valid_url("http://example.com/path") == true);
    assert(Utils::is_valid_url("not-a-url") == false);
    assert(Utils::is_valid_url("") == false);
    
    std::cout << "  is_valid_url: PASSED" << std::endl;
    std::cout << std::endl;
}

void test_storage() {
    std::cout << "--- Testing Storage ---" << std::endl;

    Storage storage;

    // Test save and find
    assert(storage.save("abc", "https://example.com") == true);
    assert(storage.find_by_code("abc").value() == "https://example.com");
    assert(storage.find_by_url("https://example.com").value() == "abc");

    // Test not found
    assert(storage.find_by_code("xyz").has_value() == false);

    // Test count
    assert(storage.count() == 1);

    std::cout << "  Save & Find: PASSED" << std::endl;
    std::cout << std::endl;
}

void test_shortener() {
    std::cout << "--- Testing URLShortener ---" << std::endl;

    Storage storage;
    URLShortener shortener(storage);
    printf("works");
    // Shorten a URL
    std::string code = shortener.shorten("https://www.example.com/very/long/url");
        printf("works");
    assert(!code.empty());
    std::cout << "  Shortened to: " << code << std::endl;

    // Resolve it back
    auto resolved = shortener.resolve(code);
    assert(resolved.has_value());
    assert(resolved.value() == "https://www.example.com/very/long/url");
    std::cout << "  Resolved back to: " << resolved.value() << std::endl;

    // Duplicate should return same code
    std::string code2 = shortener.shorten("https://www.example.com/very/long/url");
    assert(code == code2);

    // Unknown code should return nullopt
    assert(shortener.resolve("nonexistent").has_value() == false);

    std::cout << "  Full pipeline: PASSED" << std::endl;
    std::cout << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   URL Shortener — Test & Run" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    // ========================================================================
    // Phase 1-3: Run tests
    // ========================================================================
    // Uncomment each test function as you implement the corresponding module.

    test_utils();
    test_storage();
    test_shortener();

    // ========================================================================
    // Phase 4: Start the interactive server
    // ========================================================================
    Storage storage2;
    URLShortener shortener2(storage2);
    Server server(shortener2, 8080);
    server.start();

    std::cout << "========================================" << std::endl;
    std::cout << "   All enabled tests passed!" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}

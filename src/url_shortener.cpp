#include "url_shortener.h"
#include "utils.h"



URLShortener::URLShortener(Storage& storage)
    : storage_(storage), next_id_(1)
{
}

std::string URLShortener::shorten(const std::string& long_url) {
    // Check if this URL was already shortened
    auto existing = storage_.find_by_url(long_url);
    if (existing.has_value())
        return existing.value();

    // Generate a new random short code, retry if collision
    std::string code;
    do {
        code = Utils::generate_random_code(6);
    } while (storage_.find_by_code(code).has_value());
    storage_.save(code, long_url);
    return code;
}

std::optional<std::string> URLShortener::resolve(const std::string& short_code) {
    return storage_.find_by_code(short_code);
}

#include "storage.h"
using namespace std;


bool Storage::save(const std::string& short_code, const std::string& long_url) {
    // Check for duplicate BEFORE inserting
    if (code_to_url_.contains(short_code))
        return false;

    code_to_url_[short_code] = long_url;
    url_to_code_[long_url] = short_code;
    return true;
}

std::optional<std::string> Storage::find_by_code(const std::string& short_code) {
    auto it = code_to_url_.find(short_code);
    if (it != code_to_url_.end()) {
        return it->second;   
    }
    return std::nullopt;
}

std::optional<std::string> Storage::find_by_url(const std::string& long_url) {
    auto it = url_to_code_.find(long_url);
    if (it != url_to_code_.end()) {
        return it->second;
    }
    return std::nullopt;
}

size_t Storage::count() const {
    return code_to_url_.size();
}

bool Storage::remove(const std::string& short_code) {
    auto it = code_to_url_.find(short_code);
    if (it == code_to_url_.end())
        return false;

    // Get the URL before erasing so we can remove the reverse mapping too
    std::string long_url = it->second;
    code_to_url_.erase(it);
    url_to_code_.erase(long_url);
    return true;
}

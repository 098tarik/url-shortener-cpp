#pragma once



#include <string>
#include <optional>
#include "storage.h"
#include <cstdint>

class URLShortener {
public:
    explicit URLShortener(Storage& storage);
    std::string shorten(const std::string& long_url);
    std::optional<std::string> resolve(const std::string& short_code);

private:
    Storage& storage_;

    uint64_t next_id_;
};

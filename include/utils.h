#pragma once

#pragma once
#include <string>
#include <cstdint>

namespace Utils {

std::string encode_base62(uint64_t id);
uint64_t decode_base62(const std::string& encoded);
bool is_valid_url(const std::string& url);
std::string generate_random_code(size_t length = 6);

} // namespace Utils

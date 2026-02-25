#include "utils.h"
#include <algorithm>
#include <random>
#include <stdexcept>
#include <numeric>
#include <ranges>
#include <iostream>




namespace Utils {

    static const std::string BASE62_ALPHABET =
        "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    std::string encode_base62(uint64_t id) {
        if (id == 0) return "0";
        std::string result;
        while (id > 0) {
            result += BASE62_ALPHABET[id % 62];
            id /= 62;
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

    uint64_t decode_base62(const std::string& encoded) {
        uint64_t result = 0;
        for (const auto &c : encoded) {
            size_t pos = BASE62_ALPHABET.find(c);
            if (pos == std::string::npos) return 0;
            result = result * 62 + pos;
        }
        return result;
    }

    bool is_valid_url(const std::string& url) {
        if (url.empty()) return false;
        if (url.substr(0, 7) == "http://" || url.substr(0, 8) == "https://") return true;
        return false;
    }

    std::string generate_random_code(size_t length) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 61);
        std::string result;

        for (const auto &l : std::views::iota(size_t{0},length))
        {
            int random_index = dis(gen);
            char random_char = BASE62_ALPHABET[random_index];
            result += random_char;
        }
        return result;
    }

} // namespace Utils

#pragma once



#include <string>
#include <optional>
#include <unordered_map>

class Storage {
public:
    Storage() = default;

    bool save(const std::string& short_code, const std::string& long_url);

    std::optional<std::string> find_by_code(const std::string& short_code);

    // ========================================================================
    // TODO: Implement find_by_url()
    // ========================================================================
    // Reverse lookup: given a long URL, find its short code (if it exists).
    // Useful for avoiding duplicate shortenings of the same URL.
    //
    // THINK ABOUT:
    //   - This requires a second map (url → code). Is that worth the memory?
    //   - Alternative: iterate through all entries (slower but less memory)
    // ========================================================================
    std::optional<std::string> find_by_url(const std::string& long_url);

    // ========================================================================
    // TODO: Implement count()
    // ========================================================================
    // Return the total number of stored URL mappings.
    // Useful for generating the next ID and for statistics.
    // ========================================================================
    size_t count() const;

    // ========================================================================
    // TODO (Stretch Goal): Implement remove()
    // ========================================================================
    // Delete a URL mapping by short code.
    //
    // THINK ABOUT:
    //   - Don't forget to remove from BOTH maps!
    //   - Return true if it existed, false if not found
    // ========================================================================
    bool remove(const std::string& short_code);

private:
    // ========================================================================
    // Data Storage
    // ========================================================================
    // Two hash maps give you O(1) lookup in both directions:
    //   short_code → long_url   (for resolving)
    //   long_url   → short_code (for deduplication)
    //
    // TRADE-OFF: Uses 2x memory, but lookups are instant in both directions.
    //
    // FUTURE IMPROVEMENT IDEAS:
    //   - Replace with SQLite for persistence across restarts
    //   - Replace with Redis for a distributed cache
    //   - Add a TTL (time-to-live) for auto-expiring URLs
    // ========================================================================
    std::unordered_map<std::string, std::string> code_to_url_;
    std::unordered_map<std::string, std::string> url_to_code_;
};

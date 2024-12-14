#include "base64.hpp"

#include <cstdint>

namespace base64 {
std::string encode(const std::string_view input) {
    const std::string alphabet =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    const char pad = '=';

    std::uint8_t reminder = 0;
    std::uint8_t chunk_len = 6;
    std::uint8_t mask = 0b11;
    std::string output = "";

    for (const auto ch : input) {
        if (chunk_len == 0) {
            output += alphabet[reminder];
            reminder = 0;
            chunk_len = 6;
            mask = 0b11;
        }

        output += alphabet[(reminder << chunk_len) | (ch >> (8 - chunk_len))];
        reminder = ch & mask;

        chunk_len -= 2;
        mask = (mask << 2) | 0b11;
    }

    if (chunk_len != 6) {
        output += alphabet[(reminder << chunk_len)];
    }

    for (size_t i = 0; i < output.length() % 4; i++) {
        output += pad;
    }

    return output;
}
} // namespace base64

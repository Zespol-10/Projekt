#include "base64.hpp"

#include <cstdint>

std::string _encode(const std::string_view input,
                    const std::string_view alphabet, const char pad) {
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

std::string _decode(const std::string_view input,
                    const std::string_view alphabet, const char pad) {
    std::uint8_t map[255] = {};
    for (size_t i = 0; i < alphabet.length(); i++) {
        map[(size_t)alphabet[i]] = i;
    }

    std::uint8_t buffer = 0;
    std::uint8_t chunk_len = 0;
    std::string output = "";

    for (const auto ch : input) {
        if (ch == pad) {
            break;
        }

        std::uint8_t val = map[(size_t)ch];

        if (chunk_len == 0) {
            chunk_len = 8;
        } else {
            buffer |= val >> (chunk_len - 2);
            output += buffer;
        }

        buffer = (val << (10 - chunk_len)) & 0b11111111;
        chunk_len -= 2;
    }

    return output;
}

namespace base64 {
std::string encode(const std::string_view input) {
    return _encode(
        input,
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",
        '=');
}

std::string decode(const std::string_view input) {
    return _decode(
        input,
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",
        '=');
}
} // namespace base64

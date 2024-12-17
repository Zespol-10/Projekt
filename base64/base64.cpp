#include "base64.hpp"

#include <cstdint>

std::string _encode(const std::string_view input,
                    const std::string_view alphabet, const char pad,
                    size_t line_len, const std::string_view line_sep) {
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
        if (line_len != 0 && output.length() % line_len == 0) {
            output += line_sep;
        }

        reminder = ch & mask;

        chunk_len -= 2;
        mask = (mask << 2) | 0b11;
    }

    if (chunk_len != 6) {
        output += alphabet[(reminder << chunk_len)];
        if (line_len != 0 && output.length() % line_len == 0) {
            output += line_sep;
        }
    }

    for (size_t i = 0; i < output.length() % 4; i++) {
        output += pad;
        if (line_len != 0 && output.length() % line_len == 0) {
            output += line_sep;
        }
    }

    return output;
}

std::string _decode(const std::string_view input,
                    const std::string_view alphabet, const char pad,
                    const std::string_view line_sep) {
    std::uint8_t map[255] = {};
    for (size_t i = 0; i < alphabet.length(); i++) {
        map[(size_t)alphabet[i]] = i;
    }

    std::uint8_t buffer = 0;
    std::uint8_t chunk_len = 0;
    std::string output = "";

    for (const auto ch : input) {
        if (line_sep.find(ch) != std::string_view::npos) {
            continue;
        } else if (ch == pad) {
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
std::string encode1421(const std::string_view input) {
    return _encode(
        input,
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",
        '=');
}

std::string decode1421(const std::string_view input) {
    return _decode(
        input,
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", '=',
        "\r\n");
}

std::string encode2045(const std::string_view input) {
    return _encode(
        input,
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", '=',
        76, "\r\n");
}

std::string decode2045(const std::string_view input) {
    return _decode(
        input,
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", '=',
        "\r\n");
}

std::string encode2152(const std::string_view input) {
    return _encode(
        input,
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", '\0',
        0, "");
}

std::string decode2152(const std::string_view input) {
    return _decode(
        input,
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", '\0',
        "");
}

std::string encode3501(const std::string_view input) {
    return _encode(
        input,
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+,", '\0',
        0, "");
}

std::string decode3501(const std::string_view input) {
    return _decode(
        input,
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+,", '\0',
        "");
}

std::string encode4648_4(const std::string_view input) {
    return _encode(
        input,
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", '=',
        0, "");
}

std::string decode4648_4(const std::string_view input) {
    return _decode(
        input,
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", '=',
        "");
}

std::string encode4648_5(const std::string_view input) {
    return _encode(
        input,
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+_", '=',
        0, "");
}

std::string decode4648_5(const std::string_view input) {
    return _decode(
        input,
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+_", '=',
        "");
}

std::string encode4880(const std::string_view input) {
    return _encode(
        input,
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", '=',
        76, "\r\n");
}

std::string decode4880(const std::string_view input) {
    return _decode(
        input,
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", '=',
        "\r\n");
}
} // namespace base64

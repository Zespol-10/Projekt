#include "base64.hpp"

#include <cstdint>

struct Specification {
    const std::string_view alphabet;
    const char padding;
    const size_t line_len;
    const std::string_view line_separator;
};

const Specification RFC1421 = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",
    '=',
    64,
    "\r\n",
};

const Specification RFC2045 = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",
    '=',
    76,
    "\r\n",
};

const Specification RFC2152 = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",
    '\0',
    0,
    "",
};

const Specification RFC3501 = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+,",
    '\0',
    0,
    "",
};

const Specification RFC4648_4 = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",
    '=',
    0,
    "",
};

const Specification RFC4648_5 = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+_",
    '=',
    0,
    "",
};

const Specification RFC4880 = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",
    '=',
    76,
    "\r\n",
};

std::string _encode(const std::string_view input, const Specification &spec) {
    std::uint8_t reminder = 0;
    std::uint8_t chunk_len = 6;
    std::uint8_t mask = 0b11;
    std::string output = "";

    for (const auto ch : input) {
        if (chunk_len == 0) {
            output += spec.alphabet[reminder];
            reminder = 0;
            chunk_len = 6;
            mask = 0b11;
        }

        output +=
            spec.alphabet[(reminder << chunk_len) | (ch >> (8 - chunk_len))];
        if (spec.line_len != 0 && output.length() % spec.line_len == 0) {
            output += spec.line_separator;
        }

        reminder = ch & mask;

        chunk_len -= 2;
        mask = (mask << 2) | 0b11;
    }

    if (chunk_len != 6) {
        output += spec.alphabet[(reminder << chunk_len)];
        if (spec.line_len != 0 && output.length() % spec.line_len == 0) {
            output += spec.line_separator;
        }
    }

    for (size_t i = 0; i < output.length() % 4; i++) {
        output += spec.padding;
        if (spec.line_len != 0 && output.length() % spec.line_len == 0) {
            output += spec.line_separator;
        }
    }

    return output;
}

std::string _decode(const std::string_view input, const Specification &spec) {
    std::uint8_t map[255] = {};
    for (size_t i = 0; i < spec.alphabet.length(); i++) {
        map[(size_t)spec.alphabet[i]] = i;
    }

    std::uint8_t buffer = 0;
    std::uint8_t chunk_len = 0;
    std::string output = "";

    for (const auto ch : input) {
        if (spec.line_separator.find(ch) != std::string_view::npos) {
            continue;
        } else if (ch == spec.padding) {
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
    return _encode(input, RFC1421);
}

std::string decode1421(const std::string_view input) {
    return _decode(input, RFC1421);
}

std::string encode2045(const std::string_view input) {
    return _encode(input, RFC2045);
}

std::string decode2045(const std::string_view input) {
    return _decode(input, RFC2045);
}

std::string encode2152(const std::string_view input) {
    return _encode(input, RFC2152);
}

std::string decode2152(const std::string_view input) {
    return _decode(input, RFC2152);
}

std::string encode3501(const std::string_view input) {
    return _encode(input, RFC3501);
}

std::string decode3501(const std::string_view input) {
    return _decode(input, RFC3501);
}

std::string encode4648_4(const std::string_view input) {
    return _encode(input, RFC4648_4);
}

std::string decode4648_4(const std::string_view input) {
    return _decode(input, RFC4648_4);
}

std::string encode4648_5(const std::string_view input) {
    return _encode(input, RFC4648_5);
}

std::string decode4648_5(const std::string_view input) {
    return _decode(input, RFC4648_5);
}

std::string encode4880(const std::string_view input) {
    return _encode(input, RFC4880);
}

std::string decode4880(const std::string_view input) {
    return _decode(input, RFC4880);
}
} // namespace base64

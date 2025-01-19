#include "arithmetic.hpp"

#include <array>
#include <cstdint>
#include <limits>

// The following implementation is based on:
//
// Mark Nelson's "Data Compression With Arithmetic Coding" article
// https://web.archive.org/web/20241217122540/https://marknelson.us/posts/2014/10/19/data-compression-with-arithmetic-coding.html
//
// and
//
// mathematicalmonk's "Information Theory" YouTube series
// https://www.youtube.com/watch?v=ouYV3rBtrTI&list=PLE125425EC837021F&index=41

namespace {
// Type used to store a single code
typedef std::uint64_t code_t;

// Number of bits available to represent numbers
const std::size_t PRECISION = std::numeric_limits<code_t>::digits;

// 256 possible char values and the EOF code
const std::size_t ALPHABET_LEN = 257;
// The code used to indicate EOF
const code_t CODE_EOF = ALPHABET_LEN - 1;

// Bits available for code value
const std::size_t CODE_VALUE_BITS = PRECISION / 2 + 1;
// Maximum code value
const code_t MAX_CODE = (code_t(1) << CODE_VALUE_BITS) - 1;

// Bits available for frequency
const std::size_t FREQUENCY_BITS = PRECISION - CODE_VALUE_BITS;
// Maximum frequency
const code_t MAX_FREQUENCY = (code_t(1) << FREQUENCY_BITS) - 1;

// The values representing: 0.25, 0.5, 0.75, 1.0
const code_t QUARTER1 = code_t(1) << (CODE_VALUE_BITS - 2);
const code_t QUARTER2 = 2 * QUARTER1;
const code_t QUARTER3 = 3 * QUARTER1;

struct Probability {
    code_t low;
    code_t high;
    code_t count;
};

struct Range {
    code_t left;
    code_t right;

    Range() : left(0), right(MAX_CODE) {}

    void update(Probability prob) {
        auto width = right - left + 1;
        right = left + (width * prob.high / prob.count) - 1;
        left = left + (width * prob.low / prob.count);
    }

    void decrease(code_t delta) {
        left -= delta;
        right -= delta;
    }
};

class Model {
    // Freez the model once the total frequency reaches MAX_FREQUENCY
    bool frozen;
    // The cumulative frequencies of each alphabet letter
    // One more space needed, because there is also a sum of all frequencies
    std::array<code_t, ALPHABET_LEN + 1> cumulative;

  public:
    Model() : frozen(false) {
        for (code_t i = 0; i < cumulative.size(); i++) {
            cumulative[i] = i;
        }
    }

    Probability get_probability(std::uint16_t ch) {
        Probability p = {cumulative[ch], cumulative[ch + 1], cumulative.back()};
        update(ch);
        return p;
    }

    void update(std::uint16_t ch) {
        if (frozen) {
            return;
        }

        for (code_t i = ch + 1; i < cumulative.size(); i++) {
            cumulative[i]++;
        }

        if (cumulative.back() == MAX_FREQUENCY) {
            frozen = true;
        }
    }
};

class Compressor {
    code_t pending;
    Range range;
    Model model;
    std::vector<bool> output;

  public:
    Compressor() : pending(0) {}

    void emit(bool bit) {
        output.push_back(bit);
        output.resize(output.size() + pending, !bit);
        pending = 0;
    }

    std::vector<bool> compress(const std::string_view &input) {
        auto iter = input.begin();
        std::uint16_t ch = 0;

        while (ch != CODE_EOF) {
            ch = iter == input.end() ? CODE_EOF : *(iter++);

            auto prob = model.get_probability(ch);
            range.update(prob);

            // The range width is less than 0.5 and both ends of the range have
            // the same most significant bit - emit the known bit and reduce the
            // range
            while (range.left >= QUARTER2 || range.right < QUARTER2) {
                emit(range.left >= QUARTER2);
                range.left = (range.left << 1) & MAX_CODE;
                range.right = ((range.right << 1) + 1) & MAX_CODE;
            }

            // The range width is less than 0.5, but the ends of the range have
            // different most significant bits - remeber to output a bit later
            // and reduce the range
            while (range.left >= QUARTER1 && range.right < QUARTER3) {
                pending++;
                range.decrease(QUARTER1);
                range.left <<= 1;
                range.right = (range.right << 1) + 1;
            }
        }

        // Emit the remaing bits
        pending++;
        emit(range.left >= QUARTER1);

        // Make sure to emit a multiple of 8 bits
        output.resize((output.size() + 7) & ~0b111, false);

        return output;
    }
};
} // namespace

namespace arithmetic {
std::vector<bool> compress(const std::string_view input) {
    return Compressor().compress(input);
}
} // namespace arithmetic

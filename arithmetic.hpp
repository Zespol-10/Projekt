#include <string>
#include <string_view>
#include <vector>

namespace arithmetic {
std::vector<bool> compress(const std::string_view input);
std::string decompress(const std::vector<bool> &input);
} // namespace arithmetic

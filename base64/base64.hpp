#pragma once

#include <string>
#include <string_view>

namespace base64 {

std::string encode(const std::string_view input);
std::string decode(const std::string_view input);

} // namespace base64

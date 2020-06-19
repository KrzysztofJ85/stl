#include "palindrom.hpp"

#include <algorithm>

bool is_palindrome(std::string data) {
    data.erase(std::remove_if(data.begin(), data.end(),
                              [](char str) { return !std::isalpha(str); }),
               data.end());
    std::transform(data.begin(), data.end(), data.begin(), tolower);

    return (std::equal(data.begin(), data.begin() + data.size() / 2, data.rbegin()));
}

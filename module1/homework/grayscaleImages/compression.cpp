#include "compression.hpp"

#include <algorithm>
#include <iostream>

constexpr uint8_t ASCIIspace = ' ';

VectorPair compressGrayscale(const ArrayArray& data) {
    VectorPair result;
    result.reserve(width * height);

    std::for_each(data.begin(), data.end(), [&result](auto entry) {
        uint8_t currValue = entry.front();
        auto it_first = entry.begin();
        while (it_first != entry.end()) {
            auto it_last = std::find_if(it_first, entry.end(), [&currValue](const auto value) {
                 return currValue != value;
            });
            result.push_back({currValue, std::count(it_first, it_last, currValue)});
            it_first = it_last;
            currValue = *it_last;
        }
    });

    result.shrink_to_fit();

    return result;
}

ArrayArray decompressGrayscale(const VectorPair& data) {
    ArrayArray result;

    auto it = result.front().begin();

    std::for_each(data.begin(), data.end(), [it](const auto& entry) mutable {
        it = std::fill_n(it, entry.second, entry.first);
    });

    return result;
}

void printMap(const ArrayArray& mapToPrint) {
    for (const auto& column : mapToPrint) {
        for (const auto& rowValue : column) {
            if (rowValue > ASCIIspace) {
                std::cout << rowValue;
            } else {
                std::cout << ASCIIspace;
            }
        }
        std::cout << '\n';
    }
}

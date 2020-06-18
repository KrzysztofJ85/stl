#include "compression.hpp"

#include <algorithm>
#include <iostream>

std::vector<std::pair<uint8_t, uint8_t>> compressGrayscale(const std::array<std::array<uint8_t, width>, height>& dataToCompress) {
    std::vector<std::pair<uint8_t, uint8_t>> vecCompressed;
    vecCompressed.reserve(height * width);
    for (const auto& arr : dataToCompress) {
        for (auto itArr = arr.begin(); itArr != arr.end();) {
            auto it = std::adjacent_find(itArr, arr.end(), std::not_equal_to<int>{});
            if (it != arr.end()) {
                it++;
            }
            vecCompressed.emplace_back(*itArr, std::distance(itArr, it));
            itArr = it;
        }
    }
    vecCompressed.shrink_to_fit();

    return vecCompressed;
}

std::array<std::array<uint8_t, width>, height> decompressGrayscale(const std::vector<std::pair<uint8_t, uint8_t>>& dataTodecompress) {
    std::array<std::array<uint8_t, width>, height> arrayDecompressed;
    auto it = arrayDecompressed.front().begin();
    std::for_each(dataTodecompress.begin(), dataTodecompress.end(), [it](const auto& pair) mutable {
        it = std::fill_n(it, pair.second, pair.first);
    });
    return arrayDecompressed;
}

void printMap(const std::array<std::array<uint8_t, height>, width>& mapToPrint) {
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

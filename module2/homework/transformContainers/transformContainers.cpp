#include "transformContainers.hpp"

#include <algorithm>

std::map<int, std::string> removeDuplicateAndTranformToMap(std::list<std::string>& lst,
                                                           std::deque<int>& deq) {
    std::map<int, std::string> result;
    std::sort(deq.begin(), deq.end());
    deq.erase(std::unique(deq.begin(), deq.end()), deq.end());
    lst.sort();
    lst.erase(std::unique(lst.begin(), lst.end()), lst.end());
    std::transform(deq.begin(), deq.end(), lst.begin(), std::inserter(result, result.end()),
                   [](const auto& elementOfDeq, const auto& elementOfLst) {
                       return std::make_pair(elementOfDeq, elementOfLst);
                   });

    return result;
}

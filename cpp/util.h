#ifndef __UTIL_H__
#define __UTIL_H__

#include <map>
#include <cassert>
#include <utility>
#include <common.h>

template <typename T>
class PriorityQueue {
    public:
        bool update(T element, float priority);
        std::pair<T, float> findMin();

    private:
        constexpr static float INF = 10000;
        std::map<T, float> _elementPriority;
        std::multimap<float, T> _priorityElements;
};

template <typename T>
bool PriorityQueue<T>::update(T element, float priority) {
    if(_elementPriority.count(element)) {

        auto previousPriority = _elementPriority[element];

        if(priority < previousPriority) {
            _elementPriority[element] = priority;
            auto range = _priorityElements.equal_range(previousPriority);
            for(auto it = range.first; it != range.second; ++it) {
                if(it->second == element) {
                    _priorityElements.erase(it);
                    _priorityElements.insert(std::pair<float, T>(priority, element));
                    return true;
                }
            }
            assert(0);
        }

        return false;

    } else {
        _elementPriority[element] = priority;
        _priorityElements.insert(std::pair<float, T>(priority, element));
        return true;
    }
}

template <typename T>
std::pair<T, float> PriorityQueue<T>::findMin() {
    if(_priorityElements.size() == 0)
        return std::pair<T, float>(T(), -INF);

    auto minprioitr = _priorityElements.begin();
    std::pair<float, T> retval = *minprioitr;

    _priorityElements.erase(minprioitr);
    _elementPriority[retval.second] = -INF;

    return std::pair<T, float>(retval.second, retval.first);
}

static Cell addDelta(const Cell &x, const Cell &y) {
    return Cell(x.first+y.first, x.second+y.second);
}

static Cell subDelta(const Cell &x, const Cell &y) {
    return Cell(x.first-y.first, x.second-y.second);
}

static bool isValid(const Cell &x, const Size &size) {
    if(x.first < 0 || x.second < 0)
        return false;

    if(x.first >= size.first || x.second >= size.second)
        return false;

    return true;
}

#endif

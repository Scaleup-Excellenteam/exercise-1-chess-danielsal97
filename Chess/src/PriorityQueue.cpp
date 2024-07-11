#include "PriorityQueue.h"
#include <stdexcept>

template<typename T, typename Comparator>
PriorityQueue<T, Comparator>::PriorityQueue() : queue(), comp() {}

template<typename T, typename Comparator>
void PriorityQueue<T, Comparator>::push(const T& item) {
    auto it = queue.begin();
    for (; it != queue.end(); ++it) {
        if (comp(item, *it)) {
            break;
        }
    }
    queue.insert(it, item);
}

template<typename T, typename Comparator>
T PriorityQueue<T, Comparator>::poll() {
    if (queue.empty()) {
        throw std::out_of_range("PriorityQueue is empty");
    }
    T top = queue.front();
    queue.pop_front();
    return top;
}

// Explicitly instantiate the template classes you are going to use
template class PriorityQueue<int, std::less<int>>;
template class PriorityQueue<int, MyComparator>;

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <list>
#include <iostream>
struct MyComparator {
    bool operator()(int a, int b) const {
        return a > b; // Return true if a has higher priority than b
    }
};
template<typename T, typename Comparator = std::less<T>>
class PriorityQueue {
public:
    PriorityQueue();
    void push(const T& item);
    T poll();
    friend std::ostream& operator<<(std::ostream& os, const PriorityQueue& pq) {
        for (const auto& item : pq.queue) {
            os << item << " ";
        }
        return os;
    }

private:
    std::list<T> queue;
    Comparator comp;
};

#endif // PRIORITYQUEUE_H

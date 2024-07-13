#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <list>
#include <iostream>
#include "Move.h"

struct MyComparator {
    bool operator()(const Move& a, const Move& b) const {
        return a.score > b.score; // Return true if a has higher priority (higher score) than b
    }
};

template<typename T, typename Comparator = std::less<T>>
class PriorityQueue {
public:
    PriorityQueue();
    void push(const T& item);
    T poll();
    size_t size() const;
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

template<typename T, typename Comparator>
size_t PriorityQueue<T, Comparator>::size() const {
    return queue.size();
}

#endif // PRIORITYQUEUE_H

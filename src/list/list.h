// list.h
#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../common/aliases.h"

namespace dstr {

    template <typename T>
    class List {
    private:
        struct Node {
            T     data;
            Node* forward[17]; // fixed array: indices 0..MAX_LEVEL (16)
            i32   level;       // highest lane index this node participates in

            Node(const T& value, i32 lvl);
        };

        static constexpr i32   MAX_LEVEL = 16;
        static constexpr float PROB = 0.5f;

        up<Node> head_;        // sentinel, never holds real data
        i32      currentLevel_;
        i32      size_;

        i32  randomLevel();

        // Fills update[0..currentLevel_] with the rightmost node at each level
        // whose next pointer has not yet passed value. Caller provides the array.
        void findUpdate(const T& value, Node* update[]) const;

    public:
        List();
        ~List();

        List(const List& other);
        List& operator=(const List& other);
        List(List&& other) noexcept;
        List& operator=(List&& other) noexcept;

        void insert(const T& value);
        void display()  const;
        void search(const T& value) const;
        bool remove(const T& value);
        void sort();        // no-op: always sorted on insert
        bool empty() const;
        i32  size()  const;

        // Calls fn(element) for every node in sorted order
        template <typename Visitor>
        void for_each(Visitor fn) const;

        // O(log n) lookup, returns pointer to data or nullptr if not found
        const T* find(const T& value) const;
    };

} // namespace dstr

#include "list.inl"

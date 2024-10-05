#ifndef _SYSTEM_UTIL_H_
#define _SYSTEM_UTIL_H_

#include "Arduino.h"

namespace system_util {
    /**
     * @brief generates unique name if filename already exists -- file.csv -> file(1).csv
    */
    String uniquifyFilename(String filename);

    /**
     * @struct Item in a stack. Each node has a reference to the previous and next node in the stack.
     * Data of any type can be associated with each node.
    */
    template <typename T>
    struct Node {
        T data;
        Node<T>* next = nullptr;
        Node<T>* prev = nullptr;
    };

    /**
     * @class Class representing a fixed stack of nodes. Follows the fixed stack design pattern.
    */
    template <typename T, int maxsize>
    class FixedStack {
        public:
            FixedStack() {
                static_assert(maxsize > 2);
            }

            /**  @brief Add node to the top of stack. */
            void push(T& data) {
                Node<T>* temp = new Node<T>();
                if (first == nullptr) {
                    first = temp;
                    last = temp;
                } else {
                    last->next = temp;
                    temp->prev = last;
                    last = last->next;
                }
                last->data = data;

                // delete node if stack exceeds capacity
                if (++count > maxsize) {
                    Node<T>* temp = first->next;
                    delete first;
                    first = temp;
                    count = maxsize;
                }
            }

            /** @brief Returns top node in stack */
            T& top() {
                return last->data;
            }

            /** @brief Remove top-most node in stack */
            inline void pop() {
                if (!first) {
                    return;
                } else if (count == 1) {
                    delete first;
                    first = nullptr;
                    last = nullptr;
                } else {
                    Node<T>* temp = last;
                    last = last->prev;
                    delete temp;
                }
                --count;
            }

            /** @brief Returns true if there are no nodes in the stack, false otherwise. */
            inline bool empty() {
                return !first;
            }
            
            /** @brief Returns number of nodes in the stack. */
            inline uint16_t size() {
                return count;
            }

        private:
            Node<T>* first = nullptr; // first node in stack
            Node<T>* last = nullptr; // last / top-most node in stack
            uint16_t count = 0; // number of nodes in stack
    };
}

#endif
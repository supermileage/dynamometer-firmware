#ifndef _SYSTEM_UTIL_H_
#define _SYSTEM_UTIL_H_

#include "Arduino.h"

namespace system_util {
    /**
     * @brief generates unique name if filename already exists -- file.csv -> file(1).csv
    */
    String uniquifyFilename(String filename);

    template <typename T>
    struct Node {
        T data;
        Node<T>* next = nullptr;
        Node<T>* prev = nullptr;
    };

    template <typename T, int maxsize>
    class FixedStack {
        public:
            FixedStack() {
                static_assert(maxsize > 2);
            }

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

            T& top() {
                return last->data;
            }

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

            inline bool empty() {
                return !first;
            }

            inline uint16_t size() {
                return count;
            }

        private:
            Node<T>* first = nullptr;
            Node<T>* last = nullptr;
            uint16_t count = 0;
    };
}

#endif
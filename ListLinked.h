#include <ostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {

    private:
        Node<T>* first;
        int n;


    public:
        ListLinked(): first(nullptr), n(0){}
        ~ListLinked(){ 
            while (first != nullptr) {
            Node<T> *aux = first->next;
            delete first;
            first = aux; 
            }
        }
        T operator[](int pos) {
            if (pos < 0 || pos >= n) {
            throw std::out_of_range("Index out of range");
            }
            Node<T>* current = first;
            for (int i = 0; i < pos; ++i) {
            current = current->next;
            }
            return current->data;
        }
        friend std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list) {
            Node<T>* current = list.first;
            while (current != nullptr) {
            out << current->data << " ";
            current = current->next;
            }
            return out;
        }
        void insert(int pos, T e)  {
            if (pos > n || pos < 0) {
            throw std::out_of_range("Index out of range");
            }

            Node<T>* newNode = new Node<T>(e);

            if (pos == 0) {
            newNode->next = first;
            first = newNode;
            } else {
            Node<T>* current = first;
            for (int i = 0; i < pos - 1; ++i) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
            }

            ++n;
        }
        void append(T e)  {
            insert(n, e);
        }
        void prepend(T e) {
            insert(0, e);
        }
        T remove(int pos) {
            if (pos >= n || pos < 0) {
                throw std::out_of_range("Index out of range");
            }

            Node<T>* current = first;
            Node<T>* aux = nullptr;

            // Special case: removing the first element
            if (pos == 0) {
                first = first->next;
                T data = current->data;
                delete current;
                --n;
                return data;
            }

            // Traverse to the node just before the one to be removed
            for (int i = 0; i < pos - 1; ++i) {
                current = current->next;
            }

            aux = current->next;
            if (aux == nullptr) {
                throw std::runtime_error("Unexpected null pointer");
            }

            current->next = aux->next;
            T data = aux->data;
            delete aux;
            --n;
            return data;
        }
        T get(int pos) {
            if (pos >= n || pos < 0) {
            throw std::out_of_range("Index out of range");
            }
            Node<T>* current = first;
            for (int i = 0; i < pos; ++i) {
                current = current->next;
            }
            return current->data;
        }
        int search(T e) {
            Node<T>* current = first;
            int pos = 0;
            while (current != nullptr) {
            if (current->data == e) {
                return pos;
            }
            current = current->next;
            ++pos;
            }
            return -1;
        }
        bool empty() {
            return first == nullptr;
        }
        int size() {
            return n;
        } 


};
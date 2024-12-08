#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T> 
class BSNode {
    public:
        // miembros públicos
        T elem;
        BSNode<T>* left;
        BSNode<T>* right;

        	
        //Constructor
        BSNode(T elem, BSNode<T>* left=nullptr, BSNode<T>* right=nullptr) : elem(elem), left(left), right(right) {}

        friend std::ostream& operator<<(std::ostream &out, const BSNode<T> &bsn) {
            out << "Node(" << bsn.elem;
            if (bsn.left != nullptr) {
                out << ", left: " << *bsn.left;
            } else {
                out << ", left: null";
            }
            if (bsn.right) {
                out << ", right: " << *bsn.right;
            } else {
                out << ", right: null";
            }
            out << ")";
            return out;
        }
    
};
#endif
#ifndef BSTREE_H
#define BSTREE_H

#include "BSNode.h"
#include <ostream>
#include <stdexcept>

template <typename T>
class BSTree{

    private:
        //Private Attributes
        BSNode<T>* root=nullptr;
        int nelem; //N of elements

        //Private Methods
        BSNode<T>* search(BSNode<T>* n, T e) const{
            if(n == nullptr){
                throw std::runtime_error("Element not found");
            } else if (n->elem < e){ 
                return BSNode<T>* search(n->right, T e);
            } else if(n->elem > e) {
                return BSNode<T>* search(n->left, T e);
            } else  {
                return n;
                }
        };

        BSNode<T> *insert(BSNode<T> *n, T e) {
            if (n == nullptr) {
                nelem++;
                return new BSNode(e); 
                }
            else if (n->elem == e) {
                throw std::runtime_error("Duplicate element");
                }
            else if (n->elem < e) {
                n->right = insert(n->right, e);
            } else {
                n->left = insert(n->left, e);
            }
            return n;
	    };

        void print_inorder(std::ostream &out, BSNode<T> *n) const {
		    if (n != nullptr) {
                print_inorder(out, n->left);
                out << n->elem << " ";
                print_inorder(out, n->right);
            }
	    ;}

        BSNode<T> *remove(BSNode<T> *n, T e) {
            if (n == nullptr) {
                throw std::runtime_error("Elementt not found");
            }
            else if (n->elem < e) {
                n->right = remove(n->right, e);
            }
            else if (n->elem > e) {
                n->left = remove(n->left, e);
            }
            else {
                if (n->left != nullptr && n->right != nullptr) {
                    nelem--;
                    n->elem = max(n->left);
                    n->left = remove_max(n->left);
                }
                else {
                    nelem--;
                    n = (n->left != nullptr) ? n->left : n->right;
                }
            }
            return n;
        };

        T max(BSNode<T> *n) const {
            if (n == nullptr) {
                throw std::runtime_error("Element not found");
            }
            else if (n->right != NULL) {
                return max(n->right);
            }
            else {
                return n->elem;
            }
	    };

        BSNode<T> *remove_max(BSNode<T> *n) {
            if (n->right == nullptr) {
                return n->left;
            }
            else {
                n->right = remove_max(n->right);
                return n;
            }
	    };

        void delete_cascade(BSNode<T> *n) {
            if (n != nullptr) {
                delete_cascade(n->left);
                delete_cascade(n->right);
                delete n;
            }
	}


    public:
        //Public Attributes
        BSTree() : root(nullptr), nelem(0) {};
        int size() const {return nelem;};
        

        //Public Methods 
        T search(T elem) const{
            return search(this->root, elem);
        };

        T operator[](T e) const{ return search(e);}

        void insert(T e){ root = insert(root, e); }

        friend std::ostream &operator<<(std::ostream &out, const BSTree<T> &tree){
            tree.print_inorder(out, tree.root);
		    return out; 
        };

        void remove(T e) { root = remove(root, e); };

        ~BSTree() { delete_cascade(root); };

};

#endif
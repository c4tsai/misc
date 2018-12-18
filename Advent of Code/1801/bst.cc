#include <memory>
#include <utility>
#include <iostream>

#include "bst.h"
using namespace std;

int BST::get_node() const {return node;}

BST::BST(int init): node{init}, left{nullptr}, right{nullptr} {}

BST::BST(int init, const BST &lf, const BST &rt): node{init}, 
    left{unique_ptr<BST>(new BST(lf))}, right{unique_ptr<BST>(new BST(rt))} {}

BST& BST::left_tree() const {
    return *left;
}

BST& BST::right_tree() const {
    return *right;
}

BST::BST(const BST &other): node{other.get_node()}, 
    left{unique_ptr<BST>(new BST(other.left_tree()))},
    right{unique_ptr<BST>(new BST(other.right_tree()))} {}

BST &BST::operator=(const BST &other) {
    node = other.get_node();
    left = unique_ptr<BST>(new BST(other.left_tree()));
    right = unique_ptr<BST>(new BST(other.right_tree()));
    return *this;
}

BST::~BST() {}

bool BST::in_tree(const int n) {
    if (n == node) {return true;}
    else {if (n < node) {
            if (left) {
                return left->in_tree(n);
            } else {return false;}
        } else {
            if (right) {
                return right->in_tree(n);
            }else {return false;}
        }
    }
}

void BST::add_to_tree(const int n) {
    if (n == node) {} 
    else {if (n < node) {
        if (left) {left->add_to_tree(n);}
        else {
            left = unique_ptr<BST>(new BST(n));
            cout << "Added " << n << " to the left of " << node << endl;
        }
    } else {
        if (right) {right->add_to_tree(n);}
        else {
            right = unique_ptr<BST>(new BST(n));
            cout << "Added " << n << " to the right of " << node << endl;
        }
    }}
}

#ifndef __BST_H__
#define __BST_H__

#include <memory>

class BST { // Binary Search Tree
    int node;
    std::unique_ptr<BST> left;
    std::unique_ptr<BST> right;
    
  public: 
    explicit BST(int init);
    BST(int init, const BST &lf, const BST &rt);
    
    // Accessors
    int get_node() const;
    BST& left_tree() const;
    BST& right_tree() const;
    
    // Big 5
    BST(const BST &other);
    BST &operator=(const BST &other);
    ~BST();
    
    bool in_tree(const int n);
    void add_to_tree(const int n);
};

#endif
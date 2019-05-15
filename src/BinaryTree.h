//
// Created by olga on 26.03.19.
//

#ifndef TREE_MOSKANOVA_BINARYTREE_H
#define TREE_MOSKANOVA_BINARYTREE_H

#include<iostream>
#include<cstring>
#include<string.h>
#include<typeinfo>
#include"Tree.h"


template<typename nodeType>
class BinaryTreeNode:public TreeNode<nodeType> {
private:
    nodeType data;
    BinaryTreeNode *parent;
    BinaryTreeNode *right;
    BinaryTreeNode *left;
    static unsigned depth;
    unsigned recursive_get_depth(unsigned cur);
public:
    explicit BinaryTreeNode(nodeType node_data);
    BinaryTreeNode();
    BinaryTreeNode(const BinaryTreeNode<nodeType> &node);
    ~BinaryTreeNode();

    // Children ops
    void add_right_child(const BinaryTreeNode<nodeType> &child);
    void add_left_child(const BinaryTreeNode<nodeType> &child);
    void add_right_child(BinaryTreeNode<nodeType> *child);
    void add_left_child(BinaryTreeNode<nodeType> *child);

    nodeType *get_children_data();
    unsigned get_depth();                      // how many nodes are under this node
    unsigned get_tree_depth();                 // depth of the whole tree

    void output();                      //alisa func

    BinaryTreeNode<nodeType> *copy();        //alisa func
    BinaryTreeNode<nodeType> *copy_subtree(); //alisa func
};

template<typename nodeType>
unsigned BinaryTreeNode<nodeType>::depth = 0;
//====================== NODE CONSTRUCTORS ======================
template<typename nodeType>
BinaryTreeNode<nodeType>::BinaryTreeNode(nodeType node_data)
{
    data = node_data;
    parent = nullptr;
    right = nullptr;
    left = nullptr;
}

template <typename nodeType>
BinaryTreeNode<nodeType>::BinaryTreeNode()
{
    if (typeid(nodeType).name() == typeid(std::string).name())
    {
        data = '\0';
    }
    else
    {
        data = (nodeType) 0;
    }
    parent = nullptr;
    right = nullptr;
    left = nullptr;
}

//========================= NODE COPY =====================
template<typename nodeType>
BinaryTreeNode<nodeType>::BinaryTreeNode(const BinaryTreeNode<nodeType> &node)
{
    data = node.data;
    parent = node.parent;
    left = nullptr;
    right = nullptr;
}

//========================== NODE DESTRUCTOR =====================
template<typename nodeType>
BinaryTreeNode<nodeType>::~BinaryTreeNode<nodeType>()
{
    
}



//======================= CHILDREN OPS ===========================
template<typename nodeType>
void BinaryTreeNode<nodeType>::add_right_child(const BinaryTreeNode<nodeType> &child)
{
    if (!(is_in_tree(child)))
    {
        if (!(is_in_tree(child)))
        {
            if (right!=nullptr) {right->parent = nullptr;}
            right = child;
        }
    }

}
template<typename nodeType>
void BinaryTreeNode<nodeType>::add_left_child(const BinaryTreeNode<nodeType> &child)
{
    if (left!= nullptr) {left->parent = nullptr;}
    left = child;
}
template<typename nodeType>
void BinaryTreeNode<nodeType>::add_right_child(BinaryTreeNode<nodeType> *child)
{
    if (!(this->is_in_tree(child))) {
        if (right != nullptr) { right->parent = nullptr; }
        right = child;
    }
}

template<typename nodeType>
void BinaryTreeNode<nodeType>::add_left_child(BinaryTreeNode<nodeType> *child)
{
    if (!(is_in_tree(child)))
    {
        if (left!= nullptr) {left->parent = nullptr;}
        left = child;
    }
}

template<typename nodeType>
nodeType *BinaryTreeNode<nodeType>::get_children_data()
{

    nodeType *children_data = new nodeType[2];
    children_data[0] = right->data;
    children_data[1] = left->data;
    return children_data;
}

//========================= PARENT OPS ===========================

template<typename nodeType>
unsigned BinaryTreeNode<nodeType>::get_depth()
{
    depth=0;
    unsigned cur_depth_l=0, cur_depth_r = 0;
    if (left==nullptr && right==nullptr)
    {
        return depth;
    }
    else
    {
        if (left!=nullptr)
        {
            cur_depth_l++;
            return left->recursive_get_depth(cur_depth_l);
        }
        if (right!=nullptr)
        {
            cur_depth_r++;
            return right->recursive_get_depth(cur_depth_r);
        }
        if (cur_depth_l>cur_depth_r) {return cur_depth_l;}
        else {return cur_depth_r;}
    }
}

template<typename nodeType>
unsigned BinaryTreeNode<nodeType>::recursive_get_depth(unsigned cur)
{
    if (left==nullptr && right==nullptr){return cur;}
    else
    {
        unsigned cur_l = cur, cur_r=cur;
        if (left!=nullptr)
        {
            cur_l =  left->recursive_get_depth(cur+1);
        }
        if (right!=nullptr)
        {
            cur_r = right->recursive_get_depth(cur+1);
        }
        if (cur_l>cur_r){return cur_l;}
        else {return cur_r;}
    }
}

template<typename nodeType>
unsigned BinaryTreeNode<nodeType>::get_tree_depth()
{
    return (this->get_root()->get_depth());
}
//========================= OUTPUT =================================
template<typename nodeType>
void BinaryTreeNode<nodeType>::output()                      //alisa func
{

    
}

//=========================== COPY ==============================
template<typename nodeType>
BinaryTreeNode<nodeType> *BinaryTreeNode<nodeType>::copy()        //alisa func
{
    
}

template<typename nodeType>
BinaryTreeNode<nodeType> *BinaryTreeNode<nodeType>::copy_subtree() //alisa func
{
    
}

#endif //TREE_MOSKANOVA_BINARYTREE_H
//
// Created by olga on 26.03.19.
//

#ifndef TREE_MOSKANOVA_BINARYTREE_H
#define TREE_MOSKANOVA_BINARYTREE_H

#include<iostream>
#include<cstring>
#include<string.h>
#include<typeinfo>

#define BINARY_NUMBER 10


template<typename nodeType>
class BinaryTreeNode{
private:
    nodeType data;
    BinaryTreeNode *parent;
    BinaryTreeNode *right;
    BinaryTreeNode *left;
    unsigned recursive_get_depth(unsigned cur);
    bool is_in_tree(BinaryTreeNode<nodeType> *other);
    bool is_the_same(BinaryTreeNode<nodeType> *other);
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

    void set_data(nodeType new_data);
    nodeType get_data();

    nodeType *get_children_data();

    //parents
    void set_parent(BinaryTreeNode<nodeType> &new_parent);
    BinaryTreeNode<nodeType>* get_root();

    //depth
    unsigned get_depth();                      // how many nodes are under this node
    unsigned get_tree_depth();                 // depth of the whole tree

    void output();

    BinaryTreeNode<nodeType> *copy();
    BinaryTreeNode<nodeType> *copy_subtree();
};

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
    if (!(this->is_in_tree(child)))
    {
        if (right!=nullptr) {right->parent = nullptr;}
        right = child;
        child.parent = this;
    }
    else
    {
        std::cout<<"Cannot add child, sorry)"<<std::endl;
    }
}

template<typename nodeType>
void BinaryTreeNode<nodeType>::add_left_child(const BinaryTreeNode<nodeType> &child)
{
    if (!(this->is_in_tree(child)))
    {
        if (left!= nullptr) {left->parent = nullptr;}
        left = child;
        child.parent = this;
    }
    else
    {
        std::cout<<"Cannot add child, sorry"<<std::endl;
    }
}

template<typename nodeType>
void BinaryTreeNode<nodeType>::add_right_child(BinaryTreeNode<nodeType> *child)
{
    if (!(this->is_in_tree(child))) {
        if (right != nullptr) { right->parent = nullptr; }
        right = child;
        child->parent = this;
    }
    else
    {
        std::cout<<"Cannot add child, sorry)"<<std::endl;
    }
}

template<typename nodeType>
void BinaryTreeNode<nodeType>::add_left_child(BinaryTreeNode<nodeType> *child)
{
    if (!(this->is_in_tree(child)))
    {
        if (left!= nullptr) {left->parent = nullptr;}
        left = child;
        child->parent = this;
    }
    else
    {
        std::cout<<"Cannot add child, sorry)"<<std::endl;
    }
}

template<typename nodeType>
nodeType *BinaryTreeNode<nodeType>::get_children_data()
{
    unsigned i=0;
    if (right!=nullptr)
    {
        i++;
    }
    if (left!=nullptr)
    {i++;}

    auto *children_data = new nodeType[2];
    if (i==0)
    {
        if (typeid(nodeType).name() == typeid(std::string).name())
        {
            children_data[0] = '\0';
            children_data[1] = '\0';
        }
        else
        {
            children_data[0] = (nodeType)0;
            children_data[1] = (nodeType)0;
        }

    }
    else if (i==2)
    {
        children_data[0] = right->data;
        children_data[1] = left->data;
    }
    else
    {
        if (right!=nullptr)
        {
            children_data[1] = right->data;
            if (typeid(nodeType).name() == typeid(std::string).name())
            {children_data[0] = '\0';}
            else
            {children_data[0] = (nodeType)0;}
        }
        else
        {
            children_data[0] = left->data;
            if (typeid(nodeType).name() == typeid(std::string).name())
            {children_data[1] = '\0';}
            else
            {children_data[1] = (nodeType)0;}
        }
    }
    return children_data;
}

//========================= PARENT OPS ===========================
template<typename nodeType>
void BinaryTreeNode<nodeType>::set_parent(BinaryTreeNode<nodeType> &new_parent)
{
    if (parent!=nullptr)
    {
        if (parent->left==this) {parent->left = nullptr;}
        else {parent->right = nullptr;}
    }
    parent = new_parent;
}
// ======================= DATA OPS ==============================
template<typename nodeType>
nodeType BinaryTreeNode<nodeType>::get_data()
{
    return data;
}

template<typename nodeType>
void BinaryTreeNode<nodeType>::set_data(nodeType new_data)
{
    data = new_data;
}

// ======================== DEPTH ==================================
template<typename nodeType>
unsigned BinaryTreeNode<nodeType>::get_depth()
{
    unsigned depth=0;
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
void BinaryTreeNode<nodeType>::output() {
}

//=========================== COPY ==============================
template<typename nodeType>
BinaryTreeNode<nodeType> *BinaryTreeNode<nodeType>::copy()
{
    
}

template<typename nodeType>
BinaryTreeNode<nodeType> *BinaryTreeNode<nodeType>::copy_subtree()
{
    
}

// ===========================  ===============================
template<typename nodeType>
BinaryTreeNode<nodeType>* BinaryTreeNode<nodeType>::get_root()
{
    if (this->parent==nullptr) {return this;}
    else
    {
        return (this->parent->get_root());
    }
}

template<typename nodeType>
bool BinaryTreeNode<nodeType>::is_the_same(BinaryTreeNode<nodeType> *other)
{
    std::string rez;
    if (this==other) {rez="YES";}
    else {rez="NO";}

    std::cout<<"is_the_same: "<<rez<<"  "<<this<<"  "<<other<<std::endl;
    return this==other;
}

template<typename nodeType>
bool BinaryTreeNode<nodeType>::is_in_tree(BinaryTreeNode<nodeType> *other)
{

    return (this->get_root()->is_the_same(other->get_root()));
}



#endif //TREE_MOSKANOVA_BINARYTREE_H
//
// Created by olga on 26.03.19.
//

#ifndef TREE_MOSKANOVA_PREFIXTREE_H
#define TREE_MOSKANOVA_PREFIXTREE_H

#include"Tree.h"

template<typename nodeType>
class PrefixTreeNode{
private:
    nodeType data;
    PrefixTreeNode **children;
    float weight;
    PrefixTreeNode *parent;
    unsigned number_of_children;
public:
    explicit PrefixTreeNode(nodeType node_data);
    PrefixTreeNode();
    ~PrefixTreeNode();
    PrefixTreeNode(const PrefixTreeNode<nodeType> &node);

    float get_weight();
    void set_weight(float new_weight);

    void add_child(const PrefixTreeNode<nodeType> &child);
    void add_child(PrefixTreeNode<nodeType> *child);
    unsigned get_number_of_children();
    nodeType* get_children_data();


};

// ======================PREFIX_TREE_NODE CONSTRUCTOR ====================
template<typename nodeType>
PrefixTreeNode<nodeType>::PrefixTreeNode()
{
    if (typeid(nodeType).name() == typeid(std::string).name())
    {
        data = '\0';
    }
    else
    {
        data = (nodeType) 0;
    }
    children = nullptr;
    weight = 0;
    parent = nullptr;
    number_of_children = 0;
}

template<typename nodeType>
PrefixTreeNode<nodeType>::PrefixTreeNode(nodeType node_data)
{
    data = node_data;
    children = nullptr;
    weight = 0;
    parent = nullptr;
    number_of_children = 0;
}

// ======================== DESTRUCTOR ======================
template<typename nodeType>
PrefixTreeNode<nodeType>::~PrefixTreeNode()
{
    if (number_of_children > 0)
    {
        for (int i = 0; i < number_of_children; ++i) {
            delete children[i];
        }
        delete [] children;
        number_of_children = 0;
    }
    parent = nullptr;
}

// ======================== COPY ============================
template<typename nodeType>
PrefixTreeNode<nodeType>::PrefixTreeNode(const PrefixTreeNode<nodeType> &node)
{
    data = node.data;
    number_of_children = 0;
    parent = node.parent;
    this->parent->add_child(this);
    children = nullptr;
    weight = node.weight;
}

// ====================== WEIGHT OPS =========================
template<typename nodeType>
float PrefixTreeNode<nodeType>::get_weight()
{
    return weight;
}

template<typename nodeType>
void PrefixTreeNode<nodeType>::set_weight(float new_weight)
{
    weight = new_weight;
}

// ==================== CHILDREN OPS ============================
template <typename nodeType>
void PrefixTreeNode<nodeType>::add_child(const PrefixTreeNode<nodeType> &child) {
    if (!(is_in_tree(child)))
    {
        if (child->parent!=nullptr)
        {
            child->parent->remove_child(child);
        }
        if (number_of_children > 0) {
            auto new_children = new PrefixTreeNode<nodeType> *[number_of_children + 1];
            for (int i = 0; i < number_of_children; ++i) {
                new_children[i] = children[i];
            }
            new_children[number_of_children] = *child;//&child
            number_of_children++;
        } else {
            number_of_children++;
            children = new PrefixTreeNode [number_of_children];
            children[0] = *child;
        }
        child.parent = this;
    }
    else
    {
        std::cout<<"cannot add child_node: this node is already in this tree"<<std::endl;
    }
}

template<typename nodeType>
void PrefixTreeNode<nodeType>::add_child(PrefixTreeNode<nodeType> *child){
    if (!(this->is_in_tree(child)))
    {
        if (child->parent!=nullptr)
        {
            child->parent->remove_child(child);
        }
        if (number_of_children>0)
        {
            auto new_children = new PrefixTreeNode<nodeType>*[number_of_children+1];
            for (int i=0; i<number_of_children; ++i){
                new_children[i] = children[i];
            }
            new_children[number_of_children] = child;
            number_of_children++;
            delete[] children;
            children = new_children;
        } else{
            number_of_children++;
            children = new PrefixTreeNode*[number_of_children];
            children[0] = child;
        }
        child->parent = this;
    }
    else
    {
        std::cout<<"cannot add child_node: this node is already in this tree"<<std::endl;
    }
}

template <typename nodeType>
unsigned PrefixTreeNode<nodeType>::get_number_of_children() {
    return number_of_children;
}

template <typename nodeType>
nodeType* PrefixTreeNode<nodeType>::get_children_data() {
    if (children==nullptr) {return nullptr;}
    auto children_data = new nodeType[number_of_children]; // a pointer :)
    for (int i = 0; i < number_of_children; i++) {
        children_data[i] = children[i]->data;
    }
    return children_data;
}



#endif //TREE_MOSKANOVA_PREFIXTREE_H
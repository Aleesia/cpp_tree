//
// Created by olga on 26.03.19.
//

#ifndef TREE_MOSKANOVA_PREFIXTREE_H
#define TREE_MOSKANOVA_PREFIXTREE_H

#include<string>
#include<typeinfo>
#include<iostream>
#include<cstring>
#include<string.h>
#define STR_LEN 50
#define OUTPUT_STR "           "

template<typename nodeType>
class PrefixTreeNode{
private:
    nodeType data;
    PrefixTreeNode **children;
    float weight;
    PrefixTreeNode *parent;
    unsigned number_of_children;
    unsigned recursive_get_depth(unsigned cur);
    PrefixTreeNode<nodeType>* recursive_copy_subtree(PrefixTreeNode<nodeType> *copy_of_parent_node);
    static char output_str[STR_LEN];
public:
    explicit PrefixTreeNode(nodeType node_data);
    PrefixTreeNode();
    PrefixTreeNode(nodeType node_data, float weight);
    ~PrefixTreeNode();
    PrefixTreeNode(const PrefixTreeNode<nodeType> &node);

    float get_weight();
    void set_weight(float new_weight);

    void add_child(const PrefixTreeNode<nodeType> &child);
    void add_child(PrefixTreeNode<nodeType> *child);
    unsigned get_number_of_children();
    nodeType* get_children_data();
    void remove_child(PrefixTreeNode<nodeType> *child);

    unsigned get_depth();
    unsigned get_tree_depth();

    PrefixTreeNode<nodeType>* get_root();

    bool is_the_same(PrefixTreeNode<nodeType> *other);
    bool is_in_tree(PrefixTreeNode<nodeType> *other);

    void output();
    void show_adjacency_matrix();

    PrefixTreeNode<nodeType>* copy_subtree();


};


template<typename nodeType>
char PrefixTreeNode<nodeType>::output_str[STR_LEN]="";

// ======================PREFIX_TREE_NODE CONSTRUCTORS ====================
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

template<typename nodeType>
PrefixTreeNode<nodeType>::PrefixTreeNode(nodeType node_data, float node_weight)
{
    data=node_data;
    children=nullptr;
    weight=node_weight;
    parent=nullptr;
    number_of_children=0;
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
template<typename nodeType> //TODO: change!!!
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

template<typename nodeType>
void PrefixTreeNode<nodeType>::remove_child(PrefixTreeNode<nodeType> *child)
{
    if (number_of_children>=2)
    {
        auto new_children = new PrefixTreeNode<nodeType>*[number_of_children-1];
        unsigned j=0, num = number_of_children;
        for (unsigned i=0; i<number_of_children; i++)
        {
            if (!(children[i]->is_the_same(child)))
            {
                if (j!=number_of_children-1)
                {
                    new_children[j] = children[i];
                    j++;
                }
                else
                {
                    delete [] new_children;
                    new_children = nullptr;
                }
            }
        }
        if (new_children!=nullptr)
        {
            delete [] children;
            children = new_children;
            number_of_children--;
        }
    }
    else if (number_of_children==1)
    {
        if (children[0]->is_the_same(child))
        {
            child->parent = nullptr;
            children = nullptr;
            number_of_children--;
        }
    }
}


// ========================= DEPTH ==========================
template<typename nodeType>
unsigned PrefixTreeNode<nodeType>::get_depth()
{
    unsigned cur=0;
    return recursive_get_depth(cur);
}

unsigned my_max(unsigned* ar, unsigned len)
{
    unsigned maxi=0;
    for (int i=0; i<len; i++)
    {
        if (ar[i]>maxi)
        {maxi = ar[i];}
    }
    return maxi;
}

template<typename nodeType>
unsigned PrefixTreeNode<nodeType>::recursive_get_depth(unsigned cur)
{
    if (number_of_children)
    {
        auto *depths = new unsigned[number_of_children];
        for (unsigned i=0; i<number_of_children; i++)
        {
            depths[i] = children[i]->recursive_get_depth(cur+1);
        }
        return my_max(depths, number_of_children);
    }
    else
    {
        return cur;
    }
}

template<typename nodeType>
unsigned PrefixTreeNode<nodeType>::get_tree_depth()
{
    return this->get_root()->get_depth();
}

// =======================OTHER FUNCS =======================

template<typename nodeType>
PrefixTreeNode<nodeType>* PrefixTreeNode<nodeType>::get_root()
{
    if (this->parent==nullptr) {return this;}
    else {return this->parent->get_root();}
}


template<typename nodeType>
void PrefixTreeNode<nodeType>::output()
{
    if (this->parent==nullptr) {output_str[0]='\0';}
    if (output_str[strlen(output_str)-1]=='|')
    {
        unsigned l = strlen(output_str);
        if (output_str[l-2]=='|'){output_str[l-1]='\0';}
        std::cout<<this->output_str << "---("<<this->weight<<")---<" << this->data << '>' << std::endl;
    }
    else {std::cout<<this->output_str << "|---("<<this->weight<<")---<" << this->data << '>' << std::endl;}
    if (output_str[strlen(output_str)-1]==' '){strcat(output_str, "|");}
    if (number_of_children) {
        strcat(output_str, OUTPUT_STR);
        children[0]->output();
        strcat(output_str, "|");
        for (unsigned i = 1; i < number_of_children; ++i) {
            children[i]->output();
        }
        unsigned l = strlen(output_str);
        output_str[l - 13] = '\0';
    }
}

template<typename nodeType>
void PrefixTreeNode<nodeType>::show_adjacency_matrix()
{

}

template<typename nodeType>
bool PrefixTreeNode<nodeType>::is_the_same(PrefixTreeNode<nodeType> *other)
{
    return (this==other);
}

template<typename nodeType>
bool PrefixTreeNode<nodeType>::is_in_tree(PrefixTreeNode<nodeType> *other)
{
    return (this->get_root()->is_the_same(other->get_root()));
}

template<typename nodeType>
PrefixTreeNode<nodeType>* PrefixTreeNode<nodeType>::recursive_copy_subtree(PrefixTreeNode<nodeType> *copy_of_parent_node)
{
    auto *node_copy = new PrefixTreeNode<nodeType>;
    node_copy->data = this->data;
    node_copy->weight = this->weight;
    node_copy->parent = copy_of_parent_node;
    node_copy->number_of_children = this->number_of_children;
    if (number_of_children)
    {
        node_copy->children = new PrefixTreeNode<nodeType>* [number_of_children];
        for (unsigned i=0; i<number_of_children; i++)
        {
            node_copy->children[i] = this->children[i]->recursive_copy_subtree(node_copy);
        }
    }
    return node_copy;
}


template<typename nodeType>
PrefixTreeNode<nodeType>* PrefixTreeNode<nodeType>::copy_subtree()
{
    auto *new_node = new PrefixTreeNode<nodeType>;
    new_node->data = data;
    new_node->parent = NULL;
    new_node->weight=0;
    new_node->number_of_children = number_of_children;
    if (number_of_children>0)
    {
        new_node->children = new PrefixTreeNode<nodeType>* [number_of_children];
        for (int i=0; i<number_of_children; ++i)
        {
            new_node->children[i] = children[i]->recursive_copy_subtree(new_node);
        }
    }
    else
    {
        new_node->children = nullptr;
    }
    return new_node;
}

#endif //TREE_MOSKANOVA_PREFIXTREE_H
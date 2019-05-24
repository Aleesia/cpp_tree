#ifndef TREE_MOSKANOVA_TREE_H
#define TREE_MOSKANOVA_TREE_H

#include<iostream>
#include<cstring>
#include<string.h>
#include<typeinfo>
#define MAX_TREE_DEPTH 50
#define STR_LEN 50
#define OUTPUT_STR "        "

template<typename nodeType>
class TreeNode{
private:
    unsigned number_of_children;
    static char output_str[STR_LEN];
    TreeNode** children;
    TreeNode<nodeType>* recursive_copy_subtree(TreeNode<nodeType> *copy_of_parent_node); //alisa func
    unsigned recursive_get_depth(unsigned cur);

protected:
    nodeType data;
    TreeNode *parent;
    bool is_in_tree(TreeNode<nodeType> *other);
    bool is_the_same(TreeNode<nodeType> *other);
public:
    explicit TreeNode(nodeType node_data);
    TreeNode();
    TreeNode(const TreeNode<nodeType> &node);
    ~TreeNode();

    // Node data ops
    virtual nodeType get_data();
    virtual void set_data(nodeType new_data);

    // Parent ops
    TreeNode* get_parent();
    void set_parent(const TreeNode<nodeType> &new_parent);
    TreeNode** get_parents(); // full list of parents
    nodeType get_parent_data();
    nodeType* get_parents_data();

    virtual unsigned get_depth();
    virtual unsigned get_tree_depth();

    TreeNode* get_root();

    // Children ops
    void add_child(const TreeNode<nodeType> &child);
    void add_child(TreeNode<nodeType> *child);
    virtual nodeType *get_children_data();
    unsigned get_number_of_children();

    virtual void output();
    void remove_child(TreeNode<nodeType> *child);            //doesn't delete the child

    virtual TreeNode<nodeType> *copy();
    virtual TreeNode<nodeType> *copy_subtree();

    // Show section

    //    void show(); // shows node data & stuff

};

template<typename nodeType>
char TreeNode<nodeType>::output_str[STR_LEN]="";
//============== NODE CONSTRUCTORS ===============

template <typename nodeType>
TreeNode<nodeType>::TreeNode(nodeType node_data) {
    data = node_data;
    parent = nullptr;
    children = nullptr;
    number_of_children = 0;
}

template <typename nodeType>
TreeNode<nodeType>::TreeNode() {
    if (typeid(nodeType).name() == typeid(std::string).name())
    {
        data = '\0';
    }
    else
    {
        data = (nodeType) 0;
    }
    children = nullptr;
    parent = nullptr;
    number_of_children = 0;
}

//============== NODE DESTRUCTOR ===============

template <typename nodeType>
TreeNode<nodeType>::~TreeNode()
{
    if (number_of_children > 0)
    {
        for (int i = 0; i < number_of_children; ++i) {
            delete children[i];
        }
        delete [] children;
        number_of_children = 0; //without this i had segmentation fault
    }
    parent = nullptr;
}

//================== NODE COPY =================
template<typename nodeType>
TreeNode<nodeType>::TreeNode(const TreeNode<nodeType> &node)
{
    this->data = node.data;
    this->number_of_children = 0;
    this->parent = node.parent;
    this->parent->add_child(this);
    this->children = nullptr;
    this->number_of_children = 0;
}
//================== DATA OPS ==================

template <typename nodeType>
nodeType TreeNode<nodeType>::get_data() {
    return data;
}

template <typename nodeType>
void TreeNode<nodeType>::set_data(nodeType new_data) {
    data = new_data;
}

//================= PARENT OPS =================

template <typename nodeType>
TreeNode<nodeType>* TreeNode<nodeType>::get_parent() {
    return parent;
}

template <typename nodeType>
void TreeNode<nodeType>::set_parent(const TreeNode<nodeType> &new_parent) {
    if (parent!=NULL){
        parent->remove_child(*this);
    }
    parent = *new_parent;
}

template <typename nodeType>
TreeNode<nodeType>** TreeNode<nodeType>::get_parents() {
    if (this->parent == nullptr) {
        return nullptr;
    }

    TreeNode<nodeType>** parents;
    parents = new TreeNode<nodeType>*[MAX_TREE_DEPTH];

    unsigned parents_len = 0;
    TreeNode<nodeType>* currentNode = this;
    while (currentNode->parent != nullptr) {
        parents_len++;
        currentNode = this->parent;

        parents[parents_len - 1] = currentNode;
    }

    TreeNode<nodeType> **parents1 = new TreeNode<nodeType>[parents_len];
    for (int i = 0; i < parents_len; ++i) {
        parents1[i] = parents[i]; //todo hope this works
    }
    delete[] parents;

    return parents1;
}

template <typename nodeType>
nodeType TreeNode<nodeType>::get_parent_data() {
    if (parent==nullptr)
    {
        if (typeid(nodeType).name() == typeid(std::string).name()) {return '\0';}
        else {return (nodeType)0;}
    }
    else {return parent->data;}
}

template <typename nodeType>
nodeType* TreeNode<nodeType>::get_parents_data() {
    if (this->parent == nullptr) {
        return nullptr;
    }

    nodeType* parents_data;
    parents_data = new nodeType[MAX_TREE_DEPTH];

    unsigned parents_len = 0;
    TreeNode<nodeType>* currentNode = this;
    while (currentNode->parent != nullptr) {
        parents_len++;
        currentNode = this->parent;

        parents_data[parents_len - 1] = currentNode->data;
    }

    auto parents_data1 = new nodeType[parents_len];
    for (int i = 0; i < parents_len; ++i) {
        parents_data1[i] = parents_data[i]; //todo hope this works
    }
    delete[] parents_data;

    return parents_data1;
}

//================ CHILDREN OPS ================

template <typename nodeType>
void TreeNode<nodeType>::add_child(const TreeNode<nodeType> &child) {
    if (!(is_in_tree(child)))
    {
        if (child->parent!=nullptr)
        {
            child->parent->remove_child(child);
        }
        if (number_of_children > 0) {
            auto new_children = new TreeNode<nodeType> *[number_of_children + 1];
            for (int i = 0; i < number_of_children; ++i) {
                new_children[i] = children[i];
            }
            new_children[number_of_children] = *child;//&child
            number_of_children++;
        } else {
            number_of_children++;
            children = new TreeNode [number_of_children];
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
void TreeNode<nodeType>::add_child(TreeNode<nodeType>*child){
    if (!(this->is_in_tree(child)))
    {
        if (child->parent!=nullptr)
        {
            child->parent->remove_child(child);
        }
        if (number_of_children>0)
        {
            auto new_children = new TreeNode<nodeType>*[number_of_children+1];
            for (int i=0; i<number_of_children; ++i){
                new_children[i] = children[i];
            }
            new_children[number_of_children] = child;
            number_of_children++;
            delete[] children;
            children = new_children;
        } else{
            number_of_children++;
            children = new TreeNode*[number_of_children];
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
unsigned TreeNode<nodeType>::get_number_of_children() {
    return number_of_children;
}

template <typename nodeType>
nodeType* TreeNode<nodeType>::get_children_data() {
    if (children==nullptr) {return nullptr;}
    auto children_data = new nodeType[number_of_children]; // a pointer :)
    for (int i = 0; i < number_of_children; i++) {
        children_data[i] = children[i]->data;
    }
    return children_data;
}


//========== ==============


template<typename nodeType>
bool TreeNode<nodeType>::is_the_same(TreeNode<nodeType> *other)
{
    std::string rez;
    if (this==other) {rez="YES";}
    else {rez="NO";}

    std::cout<<"is_the_same: "<<rez<<"  "<<this<<"  "<<other<<std::endl;
    return (this == other);
}

template<typename nodeType>
void TreeNode<nodeType>::remove_child(TreeNode<nodeType> *child)
{
    if (number_of_children>=2)
    {
        auto new_children = new TreeNode<nodeType>*[number_of_children-1];
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

template<typename nodeType>
TreeNode<nodeType>* TreeNode<nodeType>::get_root()
{
    if (parent==nullptr)
    {
        return this;
    }
    else
    {
        return parent->get_root();
    }
}

template<typename nodeType>
bool TreeNode<nodeType>::is_in_tree(TreeNode<nodeType> *other)
{
    return (this->get_root()->is_the_same(other->get_root()));
}

template<typename nodeType>
void TreeNode<nodeType>::output()
{
    if (this->parent==nullptr) {output_str[0]='\0';}
    if (output_str[strlen(output_str)-1]=='|')
    {
        unsigned l = strlen(output_str);
        if (output_str[l-2]=='|'){output_str[l-1]='\0';}
        std::cout<<this->output_str << "---<" << this->data << '>' << std::endl;
    }
    else {std::cout<<this->output_str << "|---<" << this->data << '>' << std::endl;}
    if (output_str[strlen(output_str)-1]==' '){strcat(output_str, "|");}
    if (number_of_children) {
        strcat(output_str, OUTPUT_STR);
        children[0]->output();
        strcat(output_str, "|");
        for (unsigned i = 1; i < number_of_children; ++i) {
            children[i]->output();
        }
        unsigned l = strlen(output_str);
        output_str[l - 10] = '\0';
    }
}


template<typename nodeType>
TreeNode<nodeType> *TreeNode<nodeType>::copy()
{
    auto* new_node = new TreeNode<nodeType>;
    new_node->data = data;
    if (parent==nullptr) {new_node->parent = nullptr;}
    else
        {new_node->parent = parent;
        parent->add_child(new_node);
        };
    new_node->number_of_children = 0;
    new_node->children = nullptr;
    return new_node;
}

template<typename nodeType>
TreeNode<nodeType>* TreeNode<nodeType>::recursive_copy_subtree(TreeNode<nodeType> *copy_of_parent_node)
{
    auto *node_copy = new TreeNode<nodeType>;
    node_copy->data = this->data;
    node_copy->parent = copy_of_parent_node;
    node_copy->number_of_children = this->number_of_children;
    if (number_of_children)
    {
        node_copy->children = new TreeNode<nodeType>* [number_of_children];
        for (unsigned i=0; i<number_of_children; i++)
        {
            node_copy->children[i] = this->children[i]->recursive_copy_subtree(node_copy);
        }
    }
    return node_copy;
}

template<typename nodeType>
TreeNode<nodeType> *TreeNode<nodeType>::copy_subtree()
{
    auto *new_node = new TreeNode<nodeType>;
    new_node->data = data;
    new_node->parent = NULL;
    new_node->number_of_children = number_of_children;
    if (number_of_children>0)
    {
        new_node->children = new TreeNode<nodeType>* [number_of_children];
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

template<typename nodeType>
unsigned TreeNode<nodeType>::get_depth()
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
unsigned TreeNode<nodeType>::recursive_get_depth(unsigned cur)
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
unsigned TreeNode<nodeType>::get_tree_depth()
{
    return (this->get_root()->get_depth());
}

#endif //TREE_MOSKANOVA_TREE_H
//
// Created by olga on 26.03.19.
// nullptr, auto, foreach are not forbidden
// C++11 is ok
//

#ifndef TREE_MOSKANOVA_TREE_H
#define TREE_MOSKANOVA_TREE_H

#include "TreeError.h"
#include <iostream>
#include <fstream>

template<typename nodeType>
class TreeNode{
    nodeType data;
    TreeNode *parent;
    TreeNode** children;
    unsigned number_of_children;
    unsigned number_of_parents;
    unsigned depth;

public:
    explicit TreeNode(nodeType node_data);

    //copy constructor can copy just node data or including whole subtree.
    // you can also copy parent pointer
    // todo swap params by default to the implementation
    // oh well, i can't do that.
    explicit TreeNode(TreeNode<nodeType> *node, bool child_free = false, bool save_parent = false);

    TreeNode();
    ~TreeNode();

    // Node data ops
    nodeType get_data();
    void set_data(nodeType new_data);
    // Parent ops
    TreeNode* get_parent();

    void set_parent(const TreeNode<nodeType> &new_parent);
    void remove_parent();
    TreeNode** get_parents(); // full list of parents
    nodeType get_parent_data();
    nodeType* get_parents_data();
    unsigned get_number_of_parents();
    // Children ops
    void add_child(const TreeNode<nodeType> &child);

    void add_child(TreeNode<nodeType> *child);
    nodeType *get_children_data();
    unsigned get_number_of_children();
    void remove_child(TreeNode<nodeType> *child);


    // Output section
    unsigned get_depth();

    // for (sub)tree
    void show_adjacency_matrix(); // console
    void show_adjacency_matrix(char *filename);
    void show_adjacency_list(); // console
    void show_adjacency_list(const char *filename);
    // for node only
    template <typename NodeType>
    friend std::ostream &operator<<(std::ostream &cout, TreeNode<NodeType> *node);

protected:
    // this function is used when we operate with children/parents
    // Then we need to update information about all parents' depth
    void update_depth();
    // this is hidden recursion
    void show_adjacency_list(bool root);
    void show_adjacency_list(bool root, const char* filename);
};


//============== NODE CONSTRUCTORS ===============

template <typename nodeType>
TreeNode<nodeType>::TreeNode(nodeType node_data) {
    data = node_data;
    parent = nullptr;
    children = nullptr;
    number_of_children = 0;
    number_of_parents = 0;
    depth = 1;
}

template <typename nodeType>
TreeNode<nodeType>::TreeNode() {
    data = (nodeType) 0;
    children = nullptr;
    parent = nullptr;
    number_of_children = 0;
    number_of_parents = 0;
    depth = 1;
}

template <typename nodeType>
TreeNode<nodeType>::TreeNode(TreeNode<nodeType> *node, bool child_free, bool save_parent) {

    data = node->data;

    if (save_parent) {
        parent = node->parent;
        number_of_parents = node->number_of_parents;
    } else {
        parent = nullptr;
        number_of_parents = 0;
    }

    if (child_free or node->number_of_children == 0) {
        number_of_children = 0;
        children = nullptr;
        depth = 1;
    } else {
        number_of_children = node->number_of_children;
        children = new TreeNode<nodeType> *[number_of_children];
        for (int i = 0; i < number_of_children; i++) {
            children[i] = new TreeNode<nodeType>(node->children[i]);
        }
        depth = node->depth;
    }
}

//============== NODE DESTRUCTOR ===============

template <typename nodeType>
TreeNode<nodeType>::~TreeNode() {
    if (number_of_children > 0) {
        for (int i = 0; i < number_of_children; i++) {
            delete children[i];
        }
        delete []children;
    }

    parent = nullptr;
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

template <typename nodeType>
unsigned TreeNode<nodeType>::get_depth() {
    return depth;
}

//================= PARENT OPS =================

template <typename nodeType>
unsigned TreeNode<nodeType>::get_number_of_parents() {
    return number_of_parents;
}

template <typename nodeType>
TreeNode<nodeType>* TreeNode<nodeType>::get_parent() {
    return parent;
}

template <typename nodeType>
void TreeNode<nodeType>::set_parent(const TreeNode<nodeType> &new_parent) {
    parent = *new_parent;
    number_of_parents = new_parent.number_of_parents + 1;
    parent->update_depth();
}

template <typename nodeType>
void TreeNode<nodeType>::remove_parent() {
    // remove this child from parent's children list
    auto new_children = new TreeNode<nodeType> *[parent->number_of_children - 1];
    int j = 0;
    for (int i = 0; i < parent->number_of_children; ++i) {
        if (parent->children[i]==this) {
            continue;
        } else {
            new_children[j] = parent->children[i];
            j++;
        }
    }
    delete[] parent->children;
    parent->children = new_children;
    parent->number_of_children--;

    parent->update_depth();

    parent = nullptr;
    number_of_parents = 0;
}

template <typename nodeType>
TreeNode<nodeType>** TreeNode<nodeType>::get_parents() {
    if (this->parent == nullptr) {
        return nullptr;
    }

    TreeNode<nodeType>** parents;
    parents = new TreeNode<nodeType>*[number_of_parents];

    TreeNode<nodeType>* currentNode = this;
    for (int i = 0; i < number_of_parents; ++i) {
        currentNode = this->parent;
        parents[i] = currentNode;
    }

    return parents;
}

template <typename nodeType>
nodeType TreeNode<nodeType>::get_parent_data() {
    return parent->data;
}

template <typename nodeType>
nodeType* TreeNode<nodeType>::get_parents_data() {
    if (this->parent == nullptr) {
        return nullptr;
    }

    nodeType* parents_data;
    parents_data = new nodeType[number_of_parents];

    TreeNode<nodeType>* currentNode = this;
    for (int i = 0; i < number_of_parents; ++i) {
        currentNode = this->parent;
        parents_data[i] = currentNode->data;
    }

    return parents_data;
}

//================ CHILDREN OPS ================

template <typename nodeType>
void TreeNode<nodeType>::add_child(const TreeNode<nodeType> &child) {
    if (number_of_children > 0) {
        auto new_children = new TreeNode<nodeType>*[number_of_children + 1];
        for (int i = 0; i < number_of_children; ++i) {
            new_children[i] = children[i];
        }
        new_children[number_of_children] = *child;
        number_of_children++;

        delete[] children;
        children = new_children;
    } else {
        number_of_children++;
        children = new TreeNode[number_of_children];
        children[0] = *child;
    }

    update_depth();

    child.parent = this;
    child.number_of_parents = number_of_parents + 1;
}

template <typename nodeType>
void TreeNode<nodeType>::add_child(TreeNode<nodeType> *child) {
    if (number_of_children > 0) {
        auto new_children = new TreeNode<nodeType> *[number_of_children + 1];
        for (int i = 0; i < number_of_children; ++i) {
            new_children[i] = children[i];
        }
        new_children[number_of_children] = child;
        number_of_children++;

        delete[] children;
        children = new_children;
    } else {
        number_of_children++;
        children = new TreeNode *[number_of_children];
        children[0] = child;
    }

    update_depth();

    child->parent = this;
    child->number_of_parents = number_of_parents + 1;
}

template <typename nodeType>
unsigned TreeNode<nodeType>::get_number_of_children() {
    return number_of_children;
}

template <typename nodeType>
nodeType* TreeNode<nodeType>::get_children_data() {
    auto children_data = new nodeType[number_of_children]; // a pointer :)
    for (int i = 0; i < number_of_children; i++) {
        children_data[i] = children[i]->data;
    }
    return children_data;
}

template <typename nodeType>
void TreeNode<nodeType>::remove_child(TreeNode<nodeType> *child) {
    // check if this is a child
    // if it's not we do nothing.
    // todo: throw an error
    for (int i = 0; i < number_of_children; ++i) {
        if (children[i] == child) {
            child->remove_parent(); // genius ;]
        }
    }
}

//================ OUTPUT SECTION ================

template <typename nodeType>
void TreeNode<nodeType>::show_adjacency_list() {
    show_adjacency_list(true);
}

template <typename nodeType>
void TreeNode<nodeType>::show_adjacency_list(bool root) {
    // for this node
    if (root) {
        std::cout << data << ": (";
    } else {
        std::cout << data << ": ("
                  << parent->data << ", ";
    }
    for (int i = 0; i < number_of_children; ++i) {
        std::cout << children[i]->data << ", ";
    }
    std::cout << ")" << std::endl;

    // for children
    for (int i = 0; i < number_of_children; ++i) {
        children[i]->show_adjacency_list(false);
    }
}

template <typename nodeType>
void TreeNode<nodeType>::show_adjacency_list(const char *filename) {
    show_adjacency_list(true, filename);
}

template <typename nodeType>
void TreeNode<nodeType>::show_adjacency_list(bool root, const char *filename) {
    try {
        std::fstream fstream(filename, std::ios::out | std::ios::app);

        if (!fstream) throw TreeError(1);

        // for this node
        if (root) {
//            std::fstream fstream(filename, std::ios::out);

//            if (!fstream) throw TreeError(1);

            fstream << data << ": (";
            fstream.seekg(std::ios_base::beg);
        } else {
//            std::fstream fstream(filename, std::ios::app);

//            if (!fstream) throw TreeError(1);

            fstream.seekg(std::ios_base::end);
            fstream << data << ": ("
                    << parent->data << ", ";
        }
        for (int i = 0; i < number_of_children; ++i) {
            fstream << children[i]->data << ", ";
        }
        fstream << ")" << std::endl;
        fstream.close();

        // for children
        for (int i = 0; i < number_of_children; ++i) {
            children[i]->show_adjacency_list(false, filename);
        }
    } catch (TreeError &treeError) {
//        treeError.Message();
        std::cout << "oops";
    }

}

template <typename NodeType>
std::ostream &operator<<(std::ostream &cout, TreeNode<NodeType> *node) {
    cout << "node " << node->data << "\n"
         << "parent node ";
    if (node->parent == nullptr){
        cout << "does not exist";
    } else  {
        cout << node->parent->data;
    }
    cout << "\n" << "children nodes: ";
    if (node->number_of_children == 0) {
        cout << "do not exist";
    } else {
        cout << "\n";
        for (int i = 0; i < node->number_of_children; ++i) {
            cout << node->children[i]->data << ", ";
        }
    }
}

template <typename nodeType>
void TreeNode<nodeType>::show_adjacency_matrix() {

}

template <typename nodeType>
void TreeNode<nodeType>::show_adjacency_matrix(char *filename) {

}

//=============== OTHER STUFF ==================

template <typename nodeType>
void TreeNode<nodeType>::update_depth() {
    if (number_of_children == 0) {
        depth = 1;
    } else {
        depth = children[0]->depth + 1;
        for (int i = 1; i < number_of_children; ++i) {
            depth = depth > children[i]->depth + 1 ?
                    depth : children[i]->depth + 1;
        }
    }

    if (parent != nullptr) {
        parent->update_depth();
    }
}

#endif //TREE_MOSKANOVA_TREE_H

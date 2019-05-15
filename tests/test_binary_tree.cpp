#include"Tree.h"
#include"BinaryTree.h"
#include<iostream>

int main()
{
    BinaryTreeNode<int> my_node;
    BinaryTreeNode<int> *new_node = new BinaryTreeNode<int>(9);
    //new_node->get_data();
    my_node.add_right_child(new_node);


    std::cout<<"depth: "<<my_node.get_depth()<<std::endl;
}
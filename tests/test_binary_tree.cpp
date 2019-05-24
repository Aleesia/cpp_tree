
#include"BinaryTree.h"
#include<iostream>

int main()
{
    BinaryTreeNode<int> my_node(88);
    auto *new_node = new BinaryTreeNode<int>(9);
    std::cout<<"data:"<<new_node->get_data()<<std::endl;
    std::cout<<"data:"<<my_node.get_data()<<std::endl;
    my_node.add_right_child(new_node);
    my_node.add_left_child(new_node);


    std::cout<<"depth: "<<my_node.get_depth()<<std::endl;
}
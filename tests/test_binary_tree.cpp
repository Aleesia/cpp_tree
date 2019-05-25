#include"BinaryTree.h"
#include<iostream>

void create_tree()
{
    BinaryTreeNode<std::string> str_root("project");
    BinaryTreeNode<std::string> str_child_11("project_C");
    BinaryTreeNode<std::string> str_child_12("project_C++");

    BinaryTreeNode<std::string> str_child_21("GeomND");
    BinaryTreeNode<std::string> str_child_22("Spline");
    //BinaryTreeNode<std::string> str_child_23("BigNumber");
    //BinaryTreeNode<std::string> str_child_24("Interpolation");

    BinaryTreeNode<std::string> str_child_31("Tenzor");
    BinaryTreeNode<std::string> str_child_32("Tree");
    //BinaryTreeNode<std::string> str_child_33("Graph");
    //BinaryTreeNode<std::string> str_child_34("Bank");

    //BinaryTreeNode<std::string> str_child_41("Moskanova");
    BinaryTreeNode<std::string> str_child_42("Melekestseva");
    BinaryTreeNode<std::string> str_child_43("Horbunov");
    BinaryTreeNode<std::string> str_child_44("Kovaltchuk");
    BinaryTreeNode<std::string> str_child_45("Stoychik");
    BinaryTreeNode<std::string> str_child_46("Prygodiuk");

    str_child_21.add_left_child(&str_child_45);
    str_child_21.add_right_child(&str_child_42);
    str_child_22.add_left_child(&str_child_43);
    str_child_22.add_right_child(&str_child_44);
    str_child_31.add_right_child(&str_child_46);

    str_root.add_left_child(&str_child_11);
    str_root.add_right_child(&str_child_12);
    str_child_11.add_left_child(&str_child_21);
    str_child_11.add_right_child(&str_child_22);
    str_child_12.add_left_child(&str_child_31);
    str_child_12.add_right_child(&str_child_32);

    str_root.output();
}

int main()
{
    BinaryTreeNode<long long int> my_node(2020202020), node2(1020205060), node3(4040404040), node4(3030303030), node7(7070707070), node8(8080808080), node9(9090909090), node10(9998341734);
    auto *new_node = new BinaryTreeNode<long long int>(293482457);
    BinaryTreeNode<long long int> node100(1000000000), node11(1234567890), node12(1234567890);


    my_node.add_right_child(new_node);
    my_node.add_left_child(&node2);
    node2.add_right_child(&node3);
    node2.add_left_child(&node4);

    node4.add_left_child(&node7);
    node4.add_right_child(&node8);
    node3.add_left_child(&node9);
    new_node->add_right_child(&node10);
    node10.add_right_child(&node100);
    node10.add_right_child(&node11);
    new_node->add_left_child(&node12);

    std::cout<<"depth: "<<my_node.get_depth()<<std::endl;
    std::cout<<"\n\n";

    my_node.output();


    BinaryTreeNode<float> root(0.987);
    BinaryTreeNode<float> n1(4.23);
    BinaryTreeNode<float> n2(34.1);
    BinaryTreeNode<float> n3(6786876);


    root.add_right_child(&n1);
    n1.add_right_child(&n2);
    n1.add_left_child(&n3);

    std::cout<<std::endl;

    root.output();
    std::cout<<"\n=================================================================================\n";

    create_tree();
}
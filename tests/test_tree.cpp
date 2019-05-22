//
// Created by olga on 26.03.19.
//

#include <iostream>
#include "Tree.h"

using namespace std;

int main(){
//    TreeNode<int> root;
    auto *root = new TreeNode<int >(17);
//    root.set_data(17);

    cout << root->get_data() << endl;


    auto *first_child = new TreeNode<int>(13);
    auto *second_child = new TreeNode<int>(15);

    root->add_child(first_child);
    root->add_child(second_child);

    int *children_data = root->get_children_data();
    int n_children = root->get_number_of_children();
    for (int i = 0; i < n_children; i++) {
        cout << children_data[i] << " ";
    }

    delete[] children_data;

    delete root;

    return 0;
}
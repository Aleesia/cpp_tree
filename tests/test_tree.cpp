//
// Created by olga on 26.03.19.
//

#include <iostream>
#include "Tree.h"

using namespace std;

int main(){
    auto *root = new TreeNode<int >(27);

    //test get_data
    cout << root->get_data() << endl;

    //test constructor
    auto *first_child = new TreeNode<int>(13);
    auto *second_child = new TreeNode<int>(15);

    //test add_child
    root->add_child(first_child);
    root->add_child(second_child);

    // children_data test
    int *children_data = root->get_children_data();
    int n_children = root->get_number_of_children();
    for (int i = 0; i < n_children; i++) {
        cout << children_data[i] << " ";
    }

    delete[] children_data;

    auto *third_child = new TreeNode<int>(1);
    second_child->add_child(third_child);

    //test get_number_of_parents
    cout << endl << third_child->get_number_of_parents() << endl;

    delete root;

    return 0;
}
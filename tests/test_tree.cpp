//
// Created by olga on 26.03.19.
//

#include <iostream>
#include "Tree.h"

using namespace std;

int main(){
    TreeNode<int> root;
    root.set_data(17);

    cout << root.get_data();


    TreeNode<int> first_child(13), second_child(15);

    root.add_child(&first_child);
    root.add_child(&second_child);

    int *children_data = root.get_children_data();
    for (int i = 0; i < root.get_number_of_children(); i++) {
        cout << children_data[i];
    }

    delete[] children_data;

    delete &root;

    return 0;
}
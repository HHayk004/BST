#include <iostream>
#include "BST.h"

int main()
{
    BST<int> tree = {10, 5, 18, 12, 13, 22, 21, 24, 20};

    BST<int> tree1 = tree;

    tree.print_tree();

    std::cout << "\n\n";

    tree1.print_tree();

    return 0;
}

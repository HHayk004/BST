#include <iostream>
#include "BST.h"

int main()
{
    BST<int> tree = {10, 5, 19, 12, 13, 21, 20};

    BST<int> tree1 = tree; 
    BST<int> tree2 = std::move(tree);
	
    tree1.print_tree();
    tree2.print_tree();

    return 0;
}

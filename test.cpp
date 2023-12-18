#include <iostream>
#include "BST.h"

int main()
{
    BST<int> tree = {10, 5, 18, 12, 22, 21, 24, 20};

    tree.remove(10);
    tree.inOrder();
    std::cout << "\n";

    return 0;
}

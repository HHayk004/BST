#include <iostream>
#include "BST.h"

int main()
{
    BST<int> tree = {10, 5, 18, 12, 13, 22, 21, 24, 20};

    tree.level_order();
    std::cout << std::endl;

    return 0;
}

#include <iostream>
#include "BST.h"

int main()
{
    BST<int> tree = {10, 5, 100, 12, 13, 21, 20};

    int size = tree.size();
    for (int i = 1; i <= size; ++i)
    {
        std::cout << tree.kth_smallest(i) << ' ';
    }
    std::cout << std::endl;

    for (int i = 1; i <= size; ++i)
    {
        std::cout << tree.kth_largest(i) << ' ';
    }
    std::cout << std::endl;

	return 0;
}

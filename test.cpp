#include <iostream>
#include "BST.h"

int main()
{
    BST<int> tree = {10, 5, 100, 12, 13, 21, 20};

	std::cout << tree.kth_largest(1); 
	return 0;
}

#ifndef BST_HPP
    #define BST_HPP

    template <typename T>
    BST<T>::BST() : m_root(nullptr) {} 

    template <typename T>
    BST<T>::BST(std::initializer_list<T> list)
    {
        m_root = nullptr;
        for (auto& elem : list)
        {
            insert(elem); // using insert for initializer list
        }
    }

    template <typename T>
    BST<T>::BST(const BST<T>& tree) // copy constructor
    {
        if (tree.m_root)
        {
            m_root = new Node(tree.m_root->val);
            copyImpl(m_root, tree.m_root);
        }    
    }

    template <typename T>
    void BST<T>::copy(const BST<T>& tree) // copy public function
    {
        if (this != &tree)
        {
            if (m_root)
            {
                drop(m_root); // clearing before copying
            }

            if (tree.m_root)
            {
                m_root = new Node(tree.m_root->val); // initializing the m_root
                copyImpl(m_root, tree.m_root);
            }
        }
    }

    template <typename T>
    void BST<T>::copyImpl(Node* root1, Node* root2) // copy impl function
    {
        // recursive compying of tree
        if (root2->left)
        {
            root1->left = new Node(root2->left->val);
            copyImpl(root1->left, root2->left);
        }

        if (root2->right)
        {
            root1->right = new Node(root2->right->val);
            copyImpl(root1->right, root2->right);
        }
    }

    template <typename T>
    void BST<T>::drop(Node* root) // destructor helper function
    {
        // recursive deleting of tree
        if (root->left)
        {
            drop(root->left);
        }
 
        if (root->right)
        {
            drop(root->right);
        }

        delete root;
        root = nullptr;
    }

    template <typename T>
    BST<T>::~BST()
    {
        if (m_root) // if there are dynamic memory, call drop function
        {
            drop(m_root);
        }
    }

    template <typename T>
    BST<T>::Node::Node(T& value) // parameter constructor for node
    {
        if (value >= 0)
        {
            val = value;
            left = nullptr;
            right = nullptr;
        }

        else
        {
            std::cerr << "Invalid value for root:\n";
            exit(-1);
        }
    }

    template <typename T>
    BST<T>::Node::~Node() // it isn't nessesary
    {
        val = 0;
        left = nullptr;
        right = nullptr;
    }

    template <typename T>
    void BST<T>::insert(T value) // element insert function
    {
        // inserting value by rules of BST with iterative method
        if (value < 0) // value can't be negative
        {
            std::cerr << "Invalid value for insert:\n";
            exit(-1);
        }

        if (!m_root) // if it's empty tree 
        {
            m_root = new Node(value);
            return;
        }

        Node* root = m_root;
        while (root->val != value) // find and put our value in tree
        {
            if (value < root->val) // for left node
            {
                if (!root->left)
                {
                    root->left = new Node(value); // using parameter constructor
                    break; // end of cycle
                }
                root = root->left;
            }

            else if (value > root->val) // the same but for right node
            {
                if (!root->right) 
                {
                    root->right = new Node(value);
                    break;
                }
                root = root->right;
            }
        }
    }
 
    template <typename T>
    void BST<T>::remove(T value) // element remove function
    {
        if (value < 0) // if it's invalid value, return error message
        {
            std::cerr << "Invalid value for remove:\n";
            exit(-1);
        }

        Node* prev = nullptr; // our removing node's previous node
        Node* root = m_root;

        while (root && root->val != value) // finding our removing node
        {
            prev = root;
            if (value < root->val)
            {
                root = root->left;
            }

            else
            {
                root = root->right;
            }
        }

        if (!root) // if it doesn't find, return error message
        {
            std::cerr << "Invalid input for remove:\n";
            exit(-1);
        }

        Node* prev1 = root; // replaced node's previous node
        Node* root1 = root->right; // replaced node

        if (!root1) // if it's leafe node
        {
            if (root == m_root)
            {
                m_root = m_root->left;
            }

            else
            {
                prev->right = root->left;
            }
        }

        else
        {
            while (root1->left) // find replaced node 
            {
                prev1 = root1;
                root1 = root1->left;
            }

            prev1->left = nullptr; //replacing the nodes

            root1->left = root->left;
            root1->right = root->right;

            if (root == m_root)
            {
                prev->right = root1;
                m_root = root1;
            }
        }

        delete root; //removing the node
    }

    template <typename T>
    void BST<T>::clear() // same logic as for destructor
    {
        if (m_root)
        {
            drop(m_root);
            m_root = nullptr;
        }
    }

    template <typename T>
    void BST<T>::update(const T& value, const T& new_value) // simple update function
    {
        remove(value);
        insert(new_value);
    }
        
    template <typename T>
    bool BST<T>::search(const T& value) const // searching using the rules of bst and with iterative
    {
        if (value < 0) // checking validity of our value
        {
            return false;
        }

        Node* root = m_root;
        while (root && root->val != value) // searching the node
        {
            if (value < root->val)
            {
                root = root->left;
            }

            else
            {
                root = root->right;
            }
        }

        return root; // if root is nullptr - false, else it's true
    }

    template <typename T>
    bool BST<T>::contains(const T& value) const
    {
        return search(value); // using previous function
    }

    template <typename T>
    void BST<T>::inOrder() const // inOrder printing public function
    {
        inOrderImpl(m_root); // calling the impl function
        std::cout << std::endl;
    }

    template <typename T>
    void BST<T>::inOrderImpl(BST<T>::Node* root) const // inOrder printing implementation
    {
        if (root) // root validity checking
        {
            inOrderImpl(root->left);
            std::cout << root->val << ' ';
            inOrderImpl(root->right);
        }
    }

    template <typename T>
    void BST<T>::preOrder() const // preOrder printing public function
    {
        preOrderImpl(m_root); // calling the impl funciton
        std::cout << std::endl;
    }

    template <typename T>
    void BST<T>::preOrderImpl(BST<T>::Node* root) const // preOrder printing implementation
    {
        if (root) // root validity checking
        {
            std::cout << root->val << ' ';
            preOrderImpl(root->left);
            preOrderImpl(root->right);
        }
    }

    template <typename T>
    void BST<T>::postOrder() const
    {
        postOrderImpl(m_root); // calling the impl function
        std::cout << std::endl;
    }

    template <typename T>
    void BST<T>::postOrderImpl(BST<T>::Node* root) const // postOrder private function implementation
    {
        if (root)
        {
            postOrderImpl(root->left);
            postOrderImpl(root->right);
            std::cout << root->val << ' ';
        }
    }

    template <typename T>
    void BST<T>::level_order() const // level order function with my queue
    {
        Hayk::Queue<Node*> roots;
        roots.push(m_root);

        while (!roots.isEmpty()) 
        {
            Node* root = roots.front();
            if (root->left)
            {
                roots.push(root->left);
            }

            if (root->right)
            {
                roots.push(root->right);
            }

            std::cout << root->val << ' ';
            roots.pop();
        }
        std::cout << std::endl;
    }

	template <typename T>
	void BST<T>::print_tree() const // printing tree levelOrder + endl + nullptr nodes
	{
		int count = 0; // current count of nodes
		int n = 1; // level nodes count
		bool check = false; // check for not nullptr nodes
		Hayk::Queue<Node*> roots;
		if (m_root)
		{
            std::cout << ":";
			roots.push(m_root);
			count = 1;
		}

		while (count)
		{
			Node* root = roots.front();
			if (root) // if root printing it's value
			{
				check |= (root->left || root->right);
				roots.push(root->left);
				roots.push(root->right);
				std::cout << root->val << ':';
			}

			else // printing ' '
			{
				roots.push(nullptr);
				roots.push(nullptr);
				std::cout << " :";
			}

			--count;
			if (!count)
			{
				if (!check)
				{
					break;
				}
				
				check = false;

				std::cout << std::endl << ':';
				
				count = 2 * n; // nodes count in current level
				n *= 2;
			}

			roots.pop();
		}
        std::cout << std::endl;
	}

    template <typename T>
    typename BST<T>::Node* BST<T>::find_min() const
    {
        if (!m_root) // checking m_root validity
        {
            return nullptr;
        }

        Node* root = m_root;
        while (root->left) // min node is the leftest node
        {
            root = root->left;
        }

        return root;
    }
    
    template <typename T>
    typename BST<T>::Node* BST<T>::find_max() const
    {
        if (!m_root) // checking m_root validity
        {
            return nullptr;
        }

        Node* root = m_root;
        while (root->right) // max node is the rightest node
        {
            root = root->right;
        }

        return root;
    }

    template <typename T>
    typename BST<T>::Node* BST<T>::successor(T value) const
    {
        Node* root = m_root;
		Node* result = nullptr; // if root doesn't have right node, result will contain the answer
        while (root && root->val != value) // finding the value node and saving bigger nodes
        {
            if (value < root->val)
            {
				if (!result || result->val > root->val)
				{
					result = root;
				}
                root = root->left;
            }

            else
            {
                root = root->right;
            }
        }

        if (!root) // if there isn't node with this value
        {
            return nullptr;
        }

        if (root->right) // if there is root->right, forget about result node
        {
			root = root->right;
			while (root->left)
			{
				root = root->left;
			}
            
			return root;
        }

        return result;
    }

    template <typename T>
    typename BST<T>::Node* BST<T>::predecessor(T value) const // same lagic as in successor but in opposite
    {
		Node* root = m_root;
		Node* result = nullptr;
    	while (root && root->val != value)
        {
            if (value < root->val)
            {
                root = root->left;
            }

            else
            {
				if (!result || result->val < root->val)
				{
					result = root;
				}
                root = root->right;
            }
        }

        if (!root)
        {
            return nullptr;
        }

        if (root->left)
        {
			root = root->left;
			while (root->right)
			{
				root = root->right;
			}
            
			return root;
        }

        return result;

	}

    template <typename T>
    size_t BST<T>::size() const
    {
        return sizeImpl(m_root); // calling impl fucntion
    }

    template <typename T>
    size_t BST<T>::sizeImpl(Node* root) const // simple using of recursion
    {
        if (!root)
        {
            return 0;
        }

        return 1 + sizeImpl(root->left) + sizeImpl(root->right);
    }

    template <typename T>
    size_t BST<T>::height() const // public funrtoin
    {
        return heightImpl(m_root); // calling impl function
    }

    template <typename T>
    size_t BST<T>::heightImpl(Node* root) const // height function implementation with simple using of recursion
    {
        if (!root)
        {
            return 0;
        }

        size_t h1 = heightImpl(root->left) + 1; // max height of left side
        size_t h2 = heightImpl(root->right) + 1; // max height of right side

        return (h1 > h2) ? h1 : h2; // returning max of h1 and h2
    }

    template <typename T>
    bool BST<T>::is_valid_bst() const // checking if we do all right with insert and remove
    {
        if (!m_root) // if it's empty tree, it's true
        {
            return true;
        }

        return is_valid_bstImpl(m_root); // calling impl funcion
    }

    template <typename T>
    bool BST<T>::is_valid_bstImpl(BST<T>::Node* root) const // is_valid_bst function implementation using of simple recursion
    {
        return !(root->left && root->val <= root->left->val && !is_valid_bstImpl(root->left)) && 
               !(root->right && root->val <= root->right->val && !is_valid_bstImpl(root->right));  
    }

    template <typename T>
    MyVector<T> BST<T>::serialize() const // same logic as in level order, but we bush in vector and return it
    {
        Hayk::Queue<Node*> roots;
        MyVector<T> result;
        roots.push(m_root);

        while (!roots.isEmpty())
        {
            Node* root = roots.front();
            if (root->left)
            {
                roots.push(root->left);
            }

            if (root->right)
            {
                roots.push(root->right);
            }

            result.push_back(root->val);
            roots.pop();
        }
    
        return result;
    }

	template <typename T>
	MyVector<T> BST<T>::range_query(const T& start, const T& end) const // public
	{
		MyVector<T> result;

		range_queryImpl(m_root, start, end, result); // calling impl function

		return result;
	}

	template <typename T>
	void BST<T>::range_queryImpl(BST<T>::Node* root, const T& start, const T& end, MyVector<T>& vec) const // range_query function implementation
	{
		if (root) // if it isn't nullptr
		{
			if (root->val > end) // if it's big than the end of range
			{
				range_queryImpl(root->left, start, end, vec); // call for left
			}
			
			else if (root->val < start) // if it is's small than the start of range
			{
				range_queryImpl(root->right, start, end, vec);
			}	
			
			else// if it's in range
			{			
				if (root->val != start) // if it's meaningful to call for left node
				{
					range_queryImpl(root->left, start, end, vec);
				}
			
				vec.push_back(root->val); // pushing in inorder logic
				
				if (root->val != end) // if it's meaningful to call for right node
				{
					range_queryImpl(root->right, start, end, vec);
				}
			}
		}
	}

	template <typename T>
	T BST<T>::kth_smallest(int k) const // kth_smallest public function
	{
        if (m_root) // checking m_root validity
        {	
            int index = 0;
			return kth_smallestImpl(m_root, k, index); // calling impl function
        }

		return -1;
	}

	template <typename T>
	T BST<T>::kth_smallestImpl(Node* root, int k, int& index) const // kth_smallest function implementation
	{
        // using inOrder logic and counting with index
        if (root->left) 
        {
            int tmp = kth_smallestImpl(root->left, k, index);
            if (tmp != -1) // if tmp != -1, we find the value
            {
                return tmp;
            }
        }

        ++index;
    
        if (index == k) // it's base case
        {
            return root->val;
        }

        if (root->right)
        {
            int tmp = kth_smallestImpl(root->right, k, index);
            if (tmp != -1) // same as in top
            {
                return tmp;
            }
        }

        return -1;
    }

	template <typename T>
	T BST<T>::kth_largest(int k) const // kth_largest public function
	{
		if (m_root) // checking m_root validity
        {	
            int index = 0;
			return kth_largestImpl(m_root, k, index); // calling impl function
        }

        return -1;
	}

	template <typename T>
	T BST<T>::kth_largestImpl(Node* root, int k, int& index) const // kth_largest function implementation
	{
        // inOrder logic as in kth_smallest but opposite
		if (root->right)
        {
            int tmp = kth_largestImpl(root->right, k, index);
            if (tmp != -1)
            {
                return tmp;
            }
        }

        ++index;
    
        if (index == k)
        {
            return root->val;
        }

        if (root->left)
        {
            int tmp = kth_largestImpl(root->left, k, index);
            if (tmp != -1)
            {
                return tmp;
            }
        } 

        return -1;
	}

	template <typename T>
	void BST<T>::print_node_val(Node* root) const // simple function to get print node's value
	{
		if (root)
		{
			std::cout << root->val << std::endl;
		}

		else
		{
			std::cout << "nullptr\n";
		}
	}
#endif

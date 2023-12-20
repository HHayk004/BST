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
            insert(elem);
        }
    }

    template <typename T>
    BST<T>::BST(const BST<T>& tree)
    {
        if (tree.m_root)
        {
            m_root = new Node(tree.m_root->val);
            copyImpl(m_root, tree.m_root);
        }    
    }

    template <typename T>
    void BST<T>::copy(const BST<T>& tree)
    {
        if (this != &tree)
        {
            if (m_root)
            {
                drop(m_root);
            }

            if (tree.m_root)
            {
                m_root = new Node(tree.m_root->val);
                copyImpl(m_root, tree.m_root);
            }
        }
    }

    template <typename T>
    void BST<T>::copyImpl(Node* root1, Node* root2)
    {
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
    void BST<T>::drop(Node* root)
    {
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
        if (m_root)
        {
            drop(m_root);
            m_root = nullptr;    
        }
    }

    template <typename T>
    BST<T>::Node::Node(T& value)
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
    BST<T>::Node::~Node()
    {
        val = 0;
        left = nullptr;
        right = nullptr;
    }

    template <typename T>
    void BST<T>::insert(T value)
    {
        if (value < 0)
        {
            std::cerr << "Invalid value for insert:\n";
            exit(-1);
        }

        if (!m_root)
        {
            m_root = new Node(value);
            return;
        }

        Node* root = m_root;
        while (root->val != value)
        {
            if (value < root->val)
            {
                if (!root->left)
                {
                    root->left = new Node(value);
                    break;
                }
                root = root->left;
            }

            else if (value > root->val)
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
    void BST<T>::remove(T value)
    {
        if (value < 0)
        {
            std::cerr << "Invalid value for remove:\n";
            exit(-1);
        }

        Node* prev = nullptr;
        Node* root = m_root;

        while (root && root->val != value)
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

        if (!root)
        {
            std::cerr << "Invalid input for remove:\n";
            exit(-1);
        }

        Node* prev1 = root;
        Node* root1 = root->right;

        if (!root1)
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
            while (root1->left)
            {
                prev1 = root1;
                root1 = root1->left;
            }

            prev1->left = nullptr;

            if (prev)
            {
                prev->right = root1;
            }
            root1->left = root->left;
            root1->right = root->right;

            if (root == m_root)
            {
                m_root = root1;
            }
        }

        delete root;
    }

    template <typename T>
    void BST<T>::clear()
    {
        if (m_root)
        {
            drop(m_root);
            m_root = nullptr;
        }
    }

    template <typename T>
    bool BST<T>::search(T value) const
    {
        if (value < 0)
        {
            return false;
        }

        Node* root = m_root;
        while (root && root->val != value)
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

        return root;
    }


    template <typename T>
    void BST<T>::inOrder() const
    {
        inOrderImpl(m_root);
    }

    template <typename T>
    void BST<T>::inOrderImpl(BST<T>::Node* root) const
    {
        if (root)
        {
            inOrderImpl(root->left);
            std::cout << root->val << ' ';
            inOrderImpl(root->right);
        }
    }

    template <typename T>
    void BST<T>::preOrder() const
    {
        preOrderImpl(m_root);
    }

    template <typename T>
    void BST<T>::preOrderImpl(BST<T>::Node* root) const
    {
        if (root)
        {
            std::cout << root->val << ' ';
            preOrderImpl(root->left);
            preOrderImpl(root->right);
        }
    }

    template <typename T>
    void BST<T>::postOrder() const
    {
        postOrderImpl(m_root);
    }

    template <typename T>
    void BST<T>::postOrderImpl(BST<T>::Node* root) const
    {
        if (root)
        {
            postOrderImpl(root->left);
            postOrderImpl(root->right);
            std::cout << root->val << ' ';
        }
    }

    template <typename T>
    void BST<T>::level_order() const
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
    }

	template <typename T>
	void BST<T>::print_tree() const
	{
		int count = 0;
		int n = 1;
		bool check = false;
		Hayk::Queue<Node*> roots;
		if (m_root)
		{
			roots.push(m_root);
			count = 1;
		}

		while (count)
		{
			Node* root = roots.front();
			if (root)
			{
				check |= (root->left || root->right);
				roots.push(root->left);
				roots.push(root->right);
				std::cout << '_' << root->val;
			}

			else
			{
				roots.push(nullptr);
				roots.push(nullptr);
				std::cout << "_ ";
			}

			--count;
			if (!count)
			{
				if (!check)
				{
					break;
				}
				
				check = false;

				std::cout << std::endl;
				
				count = 2 * n;
				n *= 2;
			}

			roots.pop();
		}
	}

    template <typename T>
    typename BST<T>::Node* BST<T>::find_min() const
    {
        if (!m_root)
        {
            return nullptr;
        }

        Node* root = m_root;
        while (root->left)
        {
            root = root->left;
        }

        return root;
    }
    
    template <typename T>
    typename BST<T>::Node* BST<T>::find_max() const
    {
        if (!m_root)
        {
            return nullptr;
        }

        Node* root = m_root;
        while (root->right)
        {
            root = root->right;
        }

        return root;
    }

    template <typename T>
    typename BST<T>::Node* BST<T>::successor(T value) const
    {
        if (!m_root)
        {
            return nullptr;
        }

        Node* root = m_root;
        while (root && root->val != value)
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

        if (!root)
        {
            return root;
        }

        if (root->left)
        {
            return root->left;
        }

        return root->right;
    }

    template <typename T>
    typename BST<T>::Node* BST<T>::predecessor(T value) const
    {
        if (!m_root || m_root->val == value)
        {
            return nullptr;
        }

        Node* root = m_root;
        while (root)
        {
            if (value < root->val)
            {
                if (root->left && root->left->val == value)
                {
                    return root;
                }

                root = root->left;
            }

            else
            {
                if (root->right && root->right->val == value)
                {
                    return root;
                }

                root = root->right;
            }
        }

        return root;
    }

    template <typename T>
    size_t BST<T>::size() const
    {
        return sizeImpl(m_root);
    }

    template <typename T>
    size_t BST<T>::sizeImpl(Node* root) const
    {
        if (!root)
        {
            return 0;
        }

        return 1 + sizeImpl(root->left) + sizeImpl(root->right);
    }

    template <typename T>
    size_t BST<T>::height() const
    {
        return heightImpl(m_root);
    }

    template <typename T>
    size_t BST<T>::heightImpl(Node* root) const
    {
        if (!root)
        {
            return 0;
        }

        size_t h1 = heightImpl(root->left);
        size_t h2 = heightImpl(root->right);

        return (h1 > h2) ? h1 + 1 : h2 + 1; 
    }

    template <typename T>
    bool BST<T>::is_valid_bst() const
    {
        if (!m_root)
        {
            return true;
        }

        return is_valid_bstImpl(m_root);
    }

    template <typename T>
    bool BST<T>::is_valid_bstImpl(BST<T>::Node* root) const
    {
        return !(root->left && root->val <= root->left->val && !is_valid_bstImpl(root->left)) && 
               !(root->right && root->val <= root->right->val && !is_valid_bstImpl(root->right));  
    }

    template <typename T>
    MyVector<T> BST<T>::serialize() const
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
#endif

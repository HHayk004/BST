#ifndef BST_HPP
    #define BST_HPP
    
    #include "Queue/queue.h"

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
    }

    template <typename T>
    BST<T>::~BST()
    {
        if (m_root)
        {
            drop(m_root);    
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
            std::cerr << "Invalid value for node:\n";
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
    void BST<T>::preOrder() const
    {
        Hayk::Queue<Node*> nodes;
        nodes.push(m_root);

        while (!nodes.isEmpty())
        {
            Node* node = nodes.front();
            if (node->left)
            {
                nodes.push(node->left);
            }

            if (node->right)
            {
                nodes.push(node->right);
            }

            std::cout << node->val << ' ';
            nodes.pop();
        }
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

#endif

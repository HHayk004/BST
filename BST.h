#ifndef BST_H
    #define BST_H

    #include <iostream>
    #include <initializer_list>

    template <typename T>
    class BST {
        private:
            struct Node {
                public:
                    T val;
                    Node* left;
                    Node* right;

                    Node(T& val = 0);
                    ~Node();
            };

        private:
            Node* m_root;
            
            void drop(Node* root);
            
            void inOrderImpl(Node* root) const;
            void preOrderImpl(Node* root) const;
            void postOrderImpl(Node* root) const;

            size_t sizeImpl(Node* root) const;
            size_t heightImpl(Node* root) const;
            
            bool is_valid_bstImpl(Node* root) const;

        public:
            BST();
            BST(std::initializer_list<T> list);
            ~BST();
            
            void insert(T value);
            void remove(T value);

            void clear();

            bool search(T value) const;

            void inOrder() const;
            void preOrder() const;
            void postOrder() const;
            void level_order() const;

            Node* find_min() const;
            Node* find_max() const;

            Node* successor(T value) const;
            Node* predecessor(T value) const;

            size_t size() const;
            size_t height() const;

            bool is_valid_bst() const;
    };

    #include "BST.hpp"
#endif

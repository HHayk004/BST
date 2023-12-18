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
            void postOrderImpl(Node* root) const;

            size_t sizeImpl(Node* root) const;
            size_t heightImpl(Node* root) const;

        public:
            BST();
            BST(std::initializer_list<T> list);
            ~BST();
            
            void insert(T value);
            void remove(T value);

            bool search(T value) const;

            void inOrder() const;
            void postOrder() const;
            void preOrder() const;

            size_t size() const;
            size_t height() const;
    };

    #include "BST.hpp"
#endif

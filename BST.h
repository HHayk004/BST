#ifndef BST_H
    #define BST_H

    #include <iostream>
    #include <initializer_list>
    #include "../Queue/queue.h"
    #include "../Vector/vector.h"

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

            void copyImpl(Node* root1, Node* root2);

            void inOrderImpl(Node* root) const;
            void preOrderImpl(Node* root) const;
            void postOrderImpl(Node* root) const;	

            size_t sizeImpl(Node* root) const;
            size_t heightImpl(Node* root) const;
            
            bool is_valid_bstImpl(Node* root) const;

			void range_queryImpl(Node* root, const T& start, const T& end, MyVector<T>& vec) const;	

			T kth_smallestImpl(Node* root, int k) const;
			T kth_largestImpl(Node* root, int k) const;
        public:
            BST();
            BST(std::initializer_list<T> list);
            
            BST(const BST<T>& tree);
            void copy(const BST<T>& tree);

            ~BST();
            
            void insert(T value);
            void remove(T value);

            void clear();

            bool search(T value) const;

            void inOrder() const;
            void preOrder() const;
            void postOrder() const;
            void level_order() const;
			void print_tree() const;

            Node* find_min() const;
            Node* find_max() const;

            Node* successor(T value) const;
            Node* predecessor(T value) const;

            size_t size() const;
            size_t height() const;

            bool is_valid_bst() const;
    
            MyVector<T> serialize() const;

			MyVector<T> range_query(const T& start, const T& end) const;

			T kth_smallest(int k) const;
			T kth_largest(int k) const;

			void print_node_val(Node* root) const;
    };

    #include "BST.hpp"
#endif

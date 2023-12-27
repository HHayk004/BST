#ifndef BST_H
    #define BST_H

    #include <iostream>
    #include <initializer_list>
    #include "../Queue/queue.h"
    #include "../Vector/vector.h"

    template <typename T>
    class BST {
        private:
            struct Node { // our node class
                public:
                    T val;
                    Node* left;
                    Node* right;

                    Node(T& val = 0);
                    ~Node();
            };

        private:
            Node* m_root; // beginning of our root
            
            void drop(Node* root); // tree deleter

            void copyImpl(Node* root1, Node* root2);

            void inOrderImpl(Node* root) const;
            void preOrderImpl(Node* root) const;
            void postOrderImpl(Node* root) const;	

            size_t sizeImpl(Node* root) const;
            size_t heightImpl(Node* root) const;
            
            bool is_valid_bstImpl(Node* root) const;

			void range_queryImpl(Node* root, const T& start, const T& end, MyVector<T>& vec) const;	

			T kth_smallestImpl(Node* root, int k, int& index) const;
			T kth_largestImpl(Node* root, int k, int& index) const;

        public:
            BST();
            BST(std::initializer_list<T> list);
            
            BST(const BST<T>& tree);
            void copy(const BST<T>& tree);

            ~BST();
            
            void insert(T value);
            void remove(T value);

            void clear();

            void update(const T& value, const T& new_value);

            bool search(const T& value) const;
            bool contains(const T& value) const;

            void inOrder() const; // left, root, right
            void preOrder() const;// root, left, right
            void postOrder() const; // left, right, root
            void level_order() const;
			void print_tree() const;

            Node* find_min() const;
            Node* find_max() const;

            Node* successor(T value) const; // the smallest bigger node
            Node* predecessor(T value) const; // the biggest smaller node

            size_t size() const;
            size_t height() const;

            bool is_valid_bst() const;
    
            MyVector<T> serialize() const; // inorder vector

			MyVector<T> range_query(const T& start, const T& end) const;

			T kth_smallest(int k) const;
			T kth_largest(int k) const;

			void print_node_val(Node* root) const; // my function for tests
    };

    #include "BST.hpp"
#endif

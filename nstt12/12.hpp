#include <stdio.h>

using namespace std;
template<typename T>
class AVL {
    template<typename U>
    struct TreeNode {
        U val;
        int h;
        TreeNode<U> * left;
        TreeNode<U> * right;
        TreeNode<U> * parent;
        int children;
        
        TreeNode(U x): val(x), left(nullptr), right(nullptr), parent(nullptr), children(0), h(0) {}

        TreeNode(const TreeNode<U>& other) = default;

        TreeNode(int x, TreeNode<U>* left, TreeNode<U>* right, TreeNode<U>* parent, int children, int height): val(x), left(left), 
                                                                                    right(right), children(children), parent(parent), h(height){}
        int height(TreeNode<U> * node) {
            if (node) {
                return node -> h;
            } else {
                return 0;
            }
        }

        int balanceFactor(TreeNode<U> * node) {
            return height(node -> right) - height(node -> left);
        }

        void fixHeight(TreeNode<U> * node) {
            int hl = height(node -> left);
            int hr = height(node -> right);
            if (hl > hr) {
                node -> h = hl + 1;

            } else {
                node -> h = hr + 1;
            }
        }

        TreeNode<U> * rotate_right(TreeNode<U> * node) {
            TreeNode<U> * newRoot = node -> left;
            node -> left = newRoot -> right;
            if (node -> left) {
                node -> left -> children = newRoot -> children;
                node->left->parent = node;

            }
            newRoot -> right = node;
            newRoot->parent = node->parent;
            node->parent = newRoot;

            if (newRoot -> right) {
                newRoot -> right -> children = node -> children;
                newRoot->right->parent = newRoot;

            }
            fixHeight(node);
            fixHeight(newRoot);
            return newRoot;
        }

        TreeNode<U> * rotateLeft(TreeNode<U> * node) {
            TreeNode<U> * newRoot = node -> left;
            if (node -> right) {
                node -> right -> children = newRoot -> children;
                node->right->parent = node;

            }
            newRoot->parent = node->parent;
            node->parent = newRoot;
            newRoot -> left = node;
            if (newRoot -> left) {
                newRoot -> left -> children = node -> children;
                newRoot->left->parent = newRoot;

            }
            fixHeight(node);
            fixHeight(newRoot);
            return newRoot;
        }

        TreeNode<U> * balance(TreeNode<U> * node) {
            fixHeight(node);
            if (balanceFactor(node) == 2) {
                if (balanceFactor(node -> right) < 0) {
                    node -> right = rotate_right(node -> right);
                }
                return rotateLeft(node);
            }
            if (balanceFactor(node) == -2) {
                if (balanceFactor(node -> left)) {
                    node -> left = rotateLeft(node -> left);
                }
                return rotate_right(node);
            }
            return node;
        }
        TreeNode<U> * _insert(TreeNode<U> * node, U value) {
            if (!node) {
                return new TreeNode(value);
            }
            if (value < node -> val) {
                node -> left = _insert(node -> left, value);
                node -> left -> children++;
            } else {
                node -> right = _insert(node -> right, value);
                node -> right -> children++;
            }
            return balance(node);
        }
        TreeNode<U> * findMin(TreeNode<U> * node) {
            if (node -> left) {
                return findMin(node -> left);
            } else {
                return node;
            }
        }
        TreeNode<U> * removeMin(TreeNode<U> * node) {
            if (!node -> left) {
                return node -> right;
            }
            node -> left = removeMin(node -> left);
            return balance(node);
        }

        TreeNode<U> * _remove(TreeNode<U> * node, U value) {
            if (!node) {
                return 0;
            }
            if (value < node -> val) {
                node -> left = _remove(node -> left, value);
                if (node -> left) {
                    node -> left -> children--;
                }
            } else if (value > node -> val) {
                node -> right = _remove(node -> right, value);
                if (node -> right) {
                    node -> right -> children--;
                }
            } else {
                TreeNode<U> * left = node -> left;
                TreeNode<U> * right = node -> right;
                delete node;
                if (!right) {
                    return left;
                }
                TreeNode<U> * min = findMin(right);
                min -> right = removeMin(right);
                min -> left = left;
                return balance(min);
            }
            return balance(node);
        }

        void _updateVal(TreeNode<U>* node, U newValue, U oldValue) {
            if (!node) {
                return;
            }
            if (oldValue < node->val) {
                _updateVal(node->left, newValue, oldValue);
            } else if (oldValue > node->val) {
                _updateVal(node->right, newValue, oldValue);
            } else {
                node->val = newValue;
            }
        }
    };
    template<typename V>
    struct iterator{
        TreeNode<V> * node;
        iterator(TreeNode<V>* node) : node(node) {};
        bool operator==(const iterator<V>& other) {
            return node == other.node;
        }
        bool operator!=(const iterator<V>& other) {
            return !(*this == other);
        }
        V operator*() {
            return node->val;
        }
        iterator<V>& operator++() {
            if (node->left) {
                node = node->left;
                while (node->right) {
                    node = node->right;
                }
            } else if (node->right) {
                node = node->right;
            } else {
                while (node->parent && node == node->parent->right) {
                    node = node->parent;
                }
                node = node->parent;
            }
            return *this;
        }
        iterator operator++(int) noexcept {
                iterator it = *this;
                ++*this;
                return it;
        } 


    };

    void destroy_recursive(TreeNode<T>* node) {
        if (node) {
            destroy_recursive(node->left);
            destroy_recursive(node->right);
            delete node;
        }
    }

    TreeNode<T>* copy_nodes(TreeNode<T>* t) {
        if (t) {
            TreeNode<T>* left = copy_nodes(t->left);
            TreeNode<T>* right = copy_nodes(t->right);
            TreeNode<T>* parent = t->parent;
            return new TreeNode<T>(t->val, left, right, parent, t->children, t->h);
        } else {
            return nullptr;
        }
    }
    void insert_nodes(TreeNode<T>* other) {
        if (other) {
            insert_nodes(other->left);
            insert_nodes(other->right);
            this->insert(other->val);
        }
    }
    TreeNode<T> * root;
    public:
    AVL() {
        AVL<T>(0);
    }
    AVL(T val): root(new TreeNode<T>(val)) {}
    AVL(const AVL<T>& other) {
        root = copy_nodes(other.root);

    }
    AVL(AVL<T>&& other) {
        root = other.root;
        other.root = nullptr;
    }
    iterator<T> begin() {
        return iterator<T>(root);
    }
    
    iterator<T> end() {
        return iterator<T>(nullptr);
    }

    const AVL<T>& operator=(const AVL& other) {
        if (this != &other) {
            destroy_recursive(this->root);
            this->root = copy_nodes(other.root);
        }
        
        return *this;
    }
    AVL<T>& operator=(AVL&& other) {
        if (this != &other) {
            // delete root;

            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }
    AVL<T> operator+(const AVL& other) {
        AVL<T> result = *this;
        result.insert_nodes(other.root);
        return result;
    }
    void insert(T val) {
        if ((!root)) {
            this -> root = new TreeNode<T>(val);
        } else {
            TreeNode<T> * newRoot = root->_insert(root, val);
            this -> root = newRoot;
        }
    }
    void remove(T val) {
        TreeNode<T>* newRoot = root->_remove(root, val);
    }
    void updateVal(T newVal, T OldVal) {
        root->_updateVal(root, newVal, OldVal);
    }

    TreeNode<T>* get_root() {
        return this->root;
    }


    ~AVL() {
        destroy_recursive(this->root);
    }
    
};
        

#include <iostream>
#include <utility>

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
        int height(TreeNode<U> *node) {
            return node ? node->h : 0;
        }

        int balanceFactor(TreeNode<U> *node) {
            return height(node->right) - height(node->left);
        }

        void fixHeight(TreeNode<U> *node) {
            int hl = height(node->left);
            int hr = height(node->right);
            node->h = (hl > hr ? hl : hr) + 1;
        }

        TreeNode<U> *rotateRight(TreeNode<U> *node) {
            TreeNode<U> *newRoot = node->left;
            node->left = newRoot->right;
            if (newRoot->right) {
                newRoot->right->parent = node;
            }

            newRoot->right = node;
            newRoot->parent = node->parent;
            node->parent = newRoot;
            fixHeight(node);
            fixHeight(newRoot);
            return newRoot;
        }

        TreeNode<U> *rotateLeft(TreeNode<U> *node) {
            TreeNode<U> *newRoot = node->right;
            node->right = newRoot->left;
            if (newRoot->left) {
                newRoot->left->parent = node;
            }

            newRoot->left = node;
            newRoot->parent = node->parent;
            node->parent = newRoot;
            fixHeight(node);
            fixHeight(newRoot);
            return newRoot;
        }

        TreeNode<U> *balance(TreeNode<U> *node) {
            fixHeight(node);
            if (balanceFactor(node) == 2) {
                if (balanceFactor(node->right) < 0) {
                    node->right = rotateRight(node->right);
                }
                return rotateLeft(node);
            }
            if (balanceFactor(node) == -2) {
                if (balanceFactor(node->left) > 0) {
                    node->left = rotateLeft(node->left);
                }
                return rotateRight(node);
            }
            return node;
        }

        TreeNode<U> *_insert(TreeNode<U> *node, U value) {
            if (!node) {
                return new TreeNode(value);
            }
            if (value < node->val) {
                node->left = _insert(node->left, value);
                node->left->parent = node;
            } else {
                node->right = _insert(node->right, value);
                node->right->parent = node;
            }
            return balance(node);
        }

        TreeNode<U> *findMin(TreeNode<U> *node) {
            return node->left ? findMin(node->left) : node;
        }

        TreeNode<U> *removeMin(TreeNode<U> *node) {
            if (!node->left) {
                return node->right;
            }
            node->left = removeMin(node->left);
            return balance(node);
        }

        TreeNode<U> *_remove(TreeNode<U> *node, U value) {
            if (!node) {
                return nullptr;
            }
            if (value < node->val) {
                node->left = _remove(node->left, value);
            } else if (value > node->val) {
                node->right = _remove(node->right, value);
            } else {
                TreeNode<U> *left = node->left;
                TreeNode<U> *right = node->right;
                delete node;
                if (!right) {
                    return left;
                }
                TreeNode<U> *min = findMin(right);
                min->right = removeMin(right);
                min->left = left;
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
    struct iterator {
        TreeNode<V> *node;

        iterator(TreeNode<V>* node) : node(node) {}

        bool operator==(const iterator<V>& other) const {
            return node == other.node;
        }

        bool operator!=(const iterator<V>& other) const {
            return !(*this == other);
        }

        V& operator*() const {
            return node->val;
        }

        iterator<V>& operator++() {
            if (node->right) {
                node = node->right;
                while (node->left) {
                    node = node->left;
                }
            } else {
                TreeNode<V>* p = node->parent;
                while (p && node == p->right) {
                    node = p;
                    p = p->parent;
                }
                node = p;
            }
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
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
            TreeNode<T>* new_node = new TreeNode<T>(t->val, left, right, nullptr, t->children, t->h);
            if (left) left->parent = new_node;
            if (right) right->parent = new_node;
            return new_node;
        }
        return nullptr;
    }

    void insert_nodes(TreeNode<T>* other) {
        if (other) {
            insert_nodes(other->left);
            insert_nodes(other->right);
            insert(other->val);
        }
    }

    TreeNode<T>* root;

public:
    AVL() : root(nullptr) {}

    AVL(T val) : root(new TreeNode<T>(val)) {}

    AVL(const AVL<T>& other) : root(copy_nodes(other.root)) {}

    AVL(AVL<T>&& other) : root(other.root) {
        other.root = nullptr;
    }

    iterator<T> begin() {
        TreeNode<T>* min_node = root;
        if (min_node) {
            while (min_node->left) {
                min_node = min_node->left;
            }
        }
        return iterator<T>(min_node);
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
            destroy_recursive(this->root);
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
        if (!root) {
            root = new TreeNode<T>(val);
        } else {
            root = root->_insert(root, val);
        }
    }

    void remove(T val) {
        if (root) {
            root = root->_remove(root, val);
        }
    }

    void updateVal(T newVal, T oldVal) {
        root->_updateVal(root, newVal, oldVal);
    }

    TreeNode<T>* get_root() const {
        return root;
    }

    ~AVL() {
        destroy_recursive(root);
    }
};

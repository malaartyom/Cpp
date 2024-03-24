#include <stdio.h>
// Write TreeNode in AVL

using namespace std;
class AVL {
    struct TreeNode {
        int val;
        int h;
        TreeNode * left;
        TreeNode * right;
        int children;
        
        TreeNode(int x): val(x), left(nullptr), right(nullptr), children(0), h(0) {}

        TreeNode(const TreeNode& other) = default;

        TreeNode(int x, TreeNode* left, TreeNode* right, int children, int height): val(x), left(left), 
                                                                                    right(right), children(children), h(height){}
        int height(TreeNode * node) {
            if (node) {
                return node -> h;
            } else {
                return 0;
            }
        }

        int balanceFactor(TreeNode * node) {
            return height(node -> right) - height(node -> left);
        }

        void fixHeight(TreeNode * node) {
            int hl = height(node -> left);
            int hr = height(node -> right);
            if (hl > hr) {
                node -> h = hl + 1;

            } else {
                node -> h = hr + 1;
            }
        }

        TreeNode * rotate_right(TreeNode * node) {
            TreeNode * newRoot = node -> left;
            node -> left = newRoot -> right;
            if (node -> left) {
                node -> left -> children = newRoot -> children;
            }
            newRoot -> right = node;
            if (newRoot -> right) {
                newRoot -> right -> children = node -> children;
            }
            fixHeight(node);
            fixHeight(newRoot);
            return newRoot;
        }

        TreeNode * rotateLeft(TreeNode * node) {
            TreeNode * newRoot = node -> left;
            if (node -> right) {
                node -> right -> children = newRoot -> children;
            }
            newRoot -> left = node;
            if (newRoot -> left) {
                newRoot -> left -> children = node -> children;
            }
            fixHeight(node);
            fixHeight(newRoot);
            return newRoot;
        }

        TreeNode * balance(TreeNode * node) {
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
        TreeNode * _insert(TreeNode * node, int value) {
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
        TreeNode * findMin(TreeNode * node) {
            if (node -> left) {
                return findMin(node -> left);
            } else {
                return node;
            }
        }
        TreeNode * removeMin(TreeNode * node) {
            if (!node -> left) {
                return node -> right;
            }
            node -> left = removeMin(node -> left);
            return balance(node);
        }

        TreeNode * _remove(TreeNode * node, int value) {
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
                TreeNode * left = node -> left;
                TreeNode * right = node -> right;
                delete node;
                if (!right) {
                    return left;
                }
                TreeNode * min = findMin(right);
                min -> right = removeMin(right);
                min -> left = left;
                return balance(min);
            }
            return balance(node);
        }

        void _updateVal(TreeNode* node, int newValue, int oldValue) {
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

    void destroy_recursive(TreeNode* node) {
        if (node) {
            destroy_recursive(node->left);
            destroy_recursive(node->right);
            delete node;
        }
    }

    TreeNode* copy_nodes(TreeNode* t) {
        if (t) {
            TreeNode* left = copy_nodes(t->left);
            TreeNode* right = copy_nodes(t->right);
            return new TreeNode(t->val, left, right, t->children, t->h);
        } else {
            return nullptr;
        }
    }
    void insert_nodes(TreeNode* other) {
        if (other) {
            insert_nodes(other->left);
            insert_nodes(other->right);
            this->insert(other->val);
        }
    }
    TreeNode * root;
    public:
    AVL() {
        AVL(0);
    }
    AVL(int val): root(new TreeNode(val)) {}
    AVL(const AVL& other) {
        root = copy_nodes(other.root);

    }
    AVL(AVL&& other) {
        root = other.root;
        other.root = nullptr;
    }
    const AVL& operator=(const AVL& other) {
        if (this != &other) {
            destroy_recursive(this->root);
            this->root = copy_nodes(other.root);
        }
        
        return *this;
    }
    AVL& operator=(AVL&& other) {
        if (this != &other) {
            delete root;

            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }
    AVL operator+(const AVL& other) {
        AVL result = *this;
        result.insert_nodes(other.root);
        return result;
    }
    void insert(int val) {
        if ((!root) || (!root -> val)) {
            this -> root = new TreeNode(val);
        } else {
            TreeNode * newRoot = root->_insert(root, val);
            this -> root = newRoot;
        }
    }
    void remove(int val) {
        TreeNode* newRoot = root->_remove(root, val);
    }
    void updateVal(int newVal, int OldVal) {
        root->_updateVal(root, newVal, OldVal);
    }

    TreeNode* get_root() {
        return this->root;
    }


    ~AVL() {
        destroy_recursive(this->root);
    }
    
};
        

#include <stdio.h>

using namespace std;
struct TreeNode {
    int val;
    int h;
    TreeNode * left;
    TreeNode * right;
    int children;
    
    TreeNode(int x) {
        this -> val = x;
        this -> left = NULL;
        this -> right = NULL;
    }
};

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
TreeNode * insert(TreeNode * node, int value) {
    if (!node) {
        return new TreeNode(value);
    }
    if (value < node -> val) {
        node -> left = insert(node -> left, value);
        node -> left -> children++;
    } else {
        node -> right = insert(node -> right, value);
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

TreeNode * remove(TreeNode * node, int value) {
    if (!node) {
        return 0;
    }
    if (value < node -> val) {
        node -> left = remove(node -> left, value);
        if (node -> left) {
            node -> left -> children--;
        }
    } else if (value > node -> val) {
        node -> right = remove(node -> right, value);
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

void updateVal(TreeNode* node, int newValue, int oldValue) {
    if (!node) {
        return;
    }
    if (oldValue < node->val) {
        updateVal(node->left, newValue, oldValue);
    } else if (oldValue > node->val) {
        updateVal(node->right, newValue, oldValue);
    } else {
        node->val = newValue;
    }
}

class AVL {
    TreeNode * root;

    public:
        AVL(int val) {
            this -> root = new TreeNode(val);
        }
    void _insert(int val) {
        if ((!root) || (!root -> val)) {
            this -> root = new TreeNode(val);
        } else {
            TreeNode * newRoot = insert(root, val);
            this -> root = newRoot;
        }
    }
    void _remove(int val) {
        TreeNode* newRoot = remove(root, val);
    }
    void _updateVal(int newVal, int OldVal) {
        updateVal(root, newVal, OldVal);
    }
};
        
int main(){
    return 0;
}

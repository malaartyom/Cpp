#include "1.h"
#include <iostream>
#include <cassert>

class Tests {
public:
    void testInsertion() {
        AVL avl(5);
        avl._insert(2);
        avl._insert(8);
        
        assert(avl.get_root()->val == 5);
        assert(avl.get_root()->left->val == 2);
        assert(avl.get_root()->right->val == 8);
    }
    void testRemoval() {
        AVL avl(5);
        avl._insert(2);
        avl._insert(8);
        avl._remove(2);

        assert(avl.get_root()->left == nullptr);
    }

    void testUpdateVal() {
        AVL avl(5);
        avl._insert(2);
        avl._insert(8);
        avl._updateVal(7, 8);

        assert(avl.get_root()->right->val == 7);
    }

    void runTests() {
        testInsertion();
        testRemoval();
        testUpdateVal();

        std::cout << "All AVL tests passed successfully!" << std::endl;
    }

};

int main() {
    Tests tests;
    tests.runTests();

    return 0;
}
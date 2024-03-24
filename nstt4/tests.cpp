#include "4.hpp"
#include <iostream>
#include <cassert>
void foo(AVL avl) {
    avl.get_root()->val = 159;
}

class Tests {
public:
    void testInsertion() {
        AVL avl(5);
        avl.insert(2);
        avl.insert(8);
        
        assert(avl.get_root()->val == 5);
        assert(avl.get_root()->left->val == 2);
        assert(avl.get_root()->right->val == 8);

        std::cout << "testInsertion passed successfully!" << std::endl;
    }
    void testRemoval() {
        AVL avl(5);
        avl.insert(2);
        avl.insert(8);
        avl.remove(2);

        assert(avl.get_root()->left == nullptr);
        std::cout << "testRemoval passed successfully!" << std::endl;
    }

    void testUpdateVal() {
        AVL avl(5);
        avl.insert(2);
        avl.insert(8);
        avl.updateVal(7, 8);

        assert(avl.get_root()->right->val == 7);
        std::cout << "testUpdateVal passed successfully!" << std::endl;
    }

    void testCopyConstructor_1() {
        AVL avl(5);
        avl.insert(2);
        avl.insert(8);
        avl.updateVal(7, 8);
        // add tests like in a presentation with foo FIXED

        AVL new_avl(avl);
        assert(new_avl.get_root()->right->val == 7);
        std::cout << "testCopyConstructor_1 passed successfully!" << std::endl;
        
    }
    void testCopyConstructor_2() {
        AVL avl(5);
        avl.insert(2);
        avl.insert(8);

        foo(avl);
        assert(avl.get_root()->val == 5);
        std::cout << "testCopyConstructor_2 passed successfully!" << std::endl;

    }
    void testCopyOperator() {
        AVL avl(5);
        avl.insert(2);
        avl.insert(8);
        avl.updateVal(7, 8);

        AVL new_avl;
        new_avl = avl;
        assert(new_avl.get_root()->right->val == 7);
        std::cout << "testCopyOperator passed successfully!" << std::endl;
    }

    void testMoveConstructor() {
        AVL avl1(5);
        avl1.insert(8);

        AVL avl2(2);

        AVL avl3 = avl1 + avl2;
        assert(avl3.get_root()->left->val == 2);
        

    }

    void testMoveOperator() {
        AVL avl1(5);
        avl1.insert(8);

        AVL avl2(2);

        AVL avl3; 
        avl3 = avl1 + avl2;
        assert(avl3.get_root()->left->val == 2);
    }

    void runTests() {
        testInsertion();
        testRemoval();
        testUpdateVal();
        testCopyConstructor_1();
        testCopyConstructor_2();
        testMoveConstructor();
        testMoveOperator();

        std::cout << "All AVL tests passed successfully!" << std::endl;
    }

};

int main() {
    Tests tests;
    tests.runTests();

    return 0;
}

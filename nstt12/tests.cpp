#include "12.hpp"
#include <iostream>
#include <cassert>
#include <vector>
void foo(AVL<int> avl) {
    avl.get_root()->val = 159;
}

class Tests {
public:
    void testInsertion() {
        AVL<int> avl(5);
        avl.insert(2);
        avl.insert(8);
        
        assert(avl.get_root()->val == 5);
        assert(avl.get_root()->left->val == 2);
        assert(avl.get_root()->right->val == 8);

        std::cout << "testInsertion passed successfully!" << std::endl;
    }
    void testRemoval() {
        AVL<int> avl(5);
        avl.insert(2);
        avl.insert(8);
        avl.remove(2);

        assert(avl.get_root()->left == nullptr);
        std::cout << "testRemoval passed successfully!" << std::endl;
    }

    void testUpdateVal() {
        AVL<int> avl(5);
        avl.insert(2);
        avl.insert(8);
        avl.updateVal(7, 8);

        assert(avl.get_root()->right->val == 7);
        std::cout << "testUpdateVal passed successfully!" << std::endl;
    }

    void testCopyConstructor_1() {
        AVL<int> avl(5);
        avl.insert(2);
        avl.insert(8);
        avl.updateVal(7, 8);
        // add tests like in a presentation with foo FIXED

        AVL new_avl(avl);
        assert(new_avl.get_root()->right->val == 7);
        std::cout << "testCopyConstructor_1 passed successfully!" << std::endl;
        
    }
    void testCopyConstructor_2() {
        AVL<int> avl(5);
        avl.insert(2);
        avl.insert(8);

        foo(avl);
        assert(avl.get_root()->val == 5);
        std::cout << "testCopyConstructor_2 passed successfully!" << std::endl;

    }
    void testCopyOperator() {
        AVL<int> avl(5);
        avl.insert(2);
        avl.insert(8);
        avl.updateVal(7, 8);

        AVL<int> new_avl;
        new_avl = avl;
        assert(new_avl.get_root()->right->val == 7);
        std::cout << "testCopyOperator passed successfully!" << std::endl;
    }

    void testMoveConstructor() {
        AVL<int> avl1(5);
        avl1.insert(8);

        AVL<int> avl2(2);

        AVL<int> avl3 = avl1 + avl2;
        assert(avl3.get_root()->left->val == 2);
        std::cout << "testMoveConstructor passed successfully!" << std::endl;
        

    }

    void testMoveOperator() {
        AVL avl1(5);
        avl1.insert(8);

        AVL avl2(2);

        AVL<int> avl3; 
        avl3 = avl1 + avl2;
        assert(avl3.get_root()->left->val == 2);
        std::cout << "testMoveOperator passed successfully!" << std::endl;
    }

    void testAVLWithString() {
        AVL avl1(std::string("abc"));
        avl1.insert(std::string("bda"));
        avl1.insert(std::string("ddd"));

        // std::cout << avl1.get_root() -> val << std::endl;
        // bool f = std::string("bda") < std::string("ddd");
        // bool f1= std::string("abc") < std::string("bda");
        // std::cout << f << std::endl;
        // std::cout << f1 << std::endl;


        assert(avl1.get_root()->val == "abc");
        assert(avl1.get_root()->right->val == "bda");
        assert(avl1.get_root()->right->right->val == "ddd");
        std::cout << "testAVLWithString passed successfully!" << std::endl;
    }
    
    void testIterator() {
        AVL tree(5);
        tree.insert(3);
        tree.insert(8);
        
        for (const auto& val : tree) {
            std::cout << val << " " << std::endl;
        }

    }

    void runTests() {
        testInsertion();
        testRemoval();
        testUpdateVal();
        testCopyConstructor_1();
        testCopyConstructor_2();
        testMoveConstructor();
        testMoveOperator();
        testAVLWithString();
        testIterator();

        std::cout << "All AVL tests passed successfully!" << std::endl;
    }

};

int main() {
    Tests tests;
    tests.runTests();

    return 0;
}
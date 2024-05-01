#include <iostream>

class Expression {
public:
    virtual Expression* diff(std::string var) = 0;
    virtual ~Expression() {};
    virtual void print() = 0;
    virtual Expression* copy() = 0;
};

class Unary :public Expression {
protected:
    Expression* expr;
public:
    Unary(Expression* expr) :expr(expr) {}
    virtual Expression* diff(std::string var) = 0;
    
    ~Unary() {
        delete expr;
    }
};

class Binary :public Expression {
protected:
    Expression* left;
    Expression* right;
public:
    Binary(Expression* left, Expression* right) {
        this->left = left;
        this->right = right;
    }
    ~Binary() {
        delete left;
        delete right;
    }

    void print() {
        std::cout << "(";
        left->print();
        std::cout << this->get_sign();
        right->print();
        std::cout << ")";
    }

    virtual char get_sign() = 0;


    virtual Expression* diff(std::string var) = 0;
};

// Implement get sign DONE
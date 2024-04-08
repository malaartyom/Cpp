#include <iostream>

class Expression {
public:
    virtual Expression* diff(std::string var) = 0;
    virtual ~Expression() {};
    virtual void print() = 0;
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
    virtual Expression* diff(std::string var) = 0;
};

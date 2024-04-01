#include <iostream>

class Expression {
public:
    virtual Expression* diff(std::string var) = 0;
    virtual ~Expression() = default;
};

class Unary : Expression {
    Expression* expr;
public:
    // Unary(Expression* expr) {
    //     this->expr = expr;
    // }
    ~Unary() {
        delete expr;
    }
};

class Binary : Expression {
    Expression* left;
    Expression* right;
public:
    ~Binary() {
        delete left;
        delete right;
    }
};
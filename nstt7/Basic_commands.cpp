#include "Expressions.hpp"

class Add : public Binary {
    public:
    Add(Expression* left, Expression* right): Binary(left, right) {}
    Expression* diff(std::string var) {
        Expression* new_left= left->diff(var);
        Expression* new_right = right->diff(var);
        return new Add(new_left, new_right);
   }
    void print() {
        left->print();
        std::cout << "+";
        right->print();
    }
};

class Sub : public Binary {
    public:
    Sub(Expression* left, Expression* right): Binary(left, right) {}
    Expression* diff(std::string var) {
        Expression* left= this->left->diff(var);
        Expression* right = this->right->diff(var);
        return new Sub(left, right);
   }
    void print() {
        left->print();
        std::cout << "-";
        right->print();
    }
};

class Mult : public Binary {
    public:
    Mult(Expression* left, Expression* right): Binary(left, right) {}
    Expression* diff(std::string var) {
        Expression* left= this->left->diff(var);
        Expression* right = this->right->diff(var);
        return new Add(new Mult(left, this->right),new Mult(this->left, right));
   }
    void print() {
        left->print();
        std::cout << "*";
        right->print();
    }
};

class Div : public Binary {
    public:
    Div(Expression* left, Expression* right): Binary(left, right) {}
    Expression* diff(std::string var) {
        Expression* left= this->left->diff(var);
        Expression* right = this->right->diff(var);
        return new Div(new Sub(new Mult(left, this->right), new Mult(this->left, right)), new Mult(this->right, this->right));
   }
    void print() {
        left->print();
        std::cout << "/";
        right->print();
    }
};
class Val : public Expression {
    int num;
    public:
    Val(int value): num(value) {}
    Expression* diff(std::string var) {
        return new Val(0);
    }
    void print() {
        std::cout << num;
    }

    ~Val() {}
};
class Var : public Expression {
    std::string name;
    public:
    Var(std::string name): name(name) {}
    Expression* diff(std::string var) {
        if (name == var) {
            return new Val(1);
        }
        return this;
    }
    void print() {
        std::cout << name;
    }

    ~Var() {}
};

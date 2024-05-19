#include "Expressions.hpp"

class Add : public Binary {
    public:
    Add(Expression* left, Expression* right): Binary(left, right) {}
    Expression* diff(std::string var) {
        Expression* new_left= left->diff(var);
        Expression* new_right = right->diff(var);
        return new Add(new_left, new_right);
   }
    Expression* copy() {
        return new Add(left->copy(), right->copy());
    }
    char get_sign() {
        return '+';
    }
};

class Sub : public Binary {
    public:
    Sub(Expression* left, Expression* right): Binary(left, right) {}
    Expression* diff(std::string var) {
        Expression* new_left= left->diff(var);
        Expression* new_right = right->diff(var);
        return new Sub(new_left, new_right);
   }
    Expression* copy() {
        return new Sub(left->copy(), right->copy());
    }
    char get_sign() {
        return '-';
    }
};

class Mult : public Binary {
    public:
    Mult(Expression* left, Expression* right): Binary(left, right) {}
    Expression* diff(std::string var) {
        Expression* new_left= left->diff(var);
        Expression* new_right = right->diff(var);
        return new Add(new Mult(new_left, right->copy()),new Mult(left->copy(), new_right));
   }

    Expression* copy() {
        return new Mult(left->copy(), right->copy());
    }

    char get_sign() {
        return '*';
    }
};

class Div : public Binary {
    public:
    Div(Expression* left, Expression* right): Binary(left, right) {}
    Expression* diff(std::string var) {
        Expression* new_left= this->left->diff(var);
        Expression* new_right = this->right->diff(var);
        return new Div(new Sub(new Mult(new_left, right->copy()), new Mult(left->copy(), new_right)), new Mult(right->copy(), right->copy()));
   }
    Expression* copy() {
        return new Div(left->copy(), right->copy());
    }

    char get_sign() {
        return '/';
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
    Expression* copy() {
        return new Val(num);
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
        return new Val(0);
    }
    void print() {
        std::cout << name;
    }
    Expression* copy() {
        return new Var(name);
    }
    ~Var() {}
};

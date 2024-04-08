#include <iostream>
#include "Basic_commands.cpp"
#include <cassert>

int main() {
    Expression* var1 = new Var("x");
    Expression* var2 = new Var("y");
    Expression* val5 = new Val(5);
    Expression* val3 = new Val(3);

    Expression* diffVarX = var1->diff("x");
    Expression* diffVarY = var2->diff("y");

    Expression* diffVal5X = val5->diff("x");

    Expression* addExpr = new Add(new Var("x"), new Val(5));
    Expression* diffAddExpr = addExpr->diff("x");

    Expression* multExpr = new Mult(new Var("x"), new Val(3));
    Expression* diffMultExpr = multExpr->diff("x");

    Expression* subExpr = new Sub(new Var("x"), new Val(3));
    Expression* diffSubExpr = subExpr->diff("x");

    Expression* divExpr = new Div(new Var("x"), new Val(3));
    Expression* diffDivExpr = divExpr->diff("x");
    Expression* diffDivExprY = divExpr->diff("y");

    // Output the results
    std::cout << "Differentiation of Var 'x': ";
    diffVarX->print();
    std::cout << std::endl;

    std::cout << "Differentiation of Var 'y': ";
    diffVarY->print();
    std::cout << std::endl;

    std::cout << "Differentiation of Val 5: ";
    diffVal5X->print();
    std::cout << std::endl;

    std::cout << "Differentiation of 'x + 5': ";
    diffAddExpr->print();
    std::cout << std::endl;

    std::cout << "Differentiation of '3x': ";
    diffMultExpr->print();
    std::cout << std::endl;

    std::cout << "Differentiation of 'x - 3': ";
    diffSubExpr->print();
    std::cout << std::endl;

    std::cout << "Differentiation of 'x / 3': ";
    diffDivExpr->print();
    std::cout << std::endl;

    std::cout << "Differentiation of 'x / 3' by y: ";
    diffDivExprY->print();
    std::cout << std::endl;

    delete var1;
    delete var2;
    delete val5;
    delete val3;
    delete diffVarX;
    delete diffVarY;
    delete diffVal5X;
    delete addExpr;
    delete diffAddExpr;
    delete multExpr;
    delete diffMultExpr;
    delete subExpr;
    delete diffSubExpr;
    delete divExpr;
    delete diffDivExpr;
    delete diffDivExprY;

    return 0;
}

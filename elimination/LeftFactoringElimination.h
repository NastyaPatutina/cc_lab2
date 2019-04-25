//
// Created by Nastya Patutina on 2019-04-17.
//

#ifndef LAB2_LEFTFACTORINGELIMINATION_H
#define LAB2_LEFTFACTORINGELIMINATION_H


#include "../gram/Equation.h"
#include <iterator>

class LeftFactoringElimination {
public:
    LeftFactoringElimination(std::list<Equation*> rules);
    std::list<Equation*> get_left_factor_rules();

private:
    std::list <Equation*> rules;

    std::list<Equation*> non_recursive_grammar;

    void perform_left_recursion_elimination();

    void left_recursion_elimination(Equation* grammar_rule);
};


#endif //LAB2_LEFTFACTORINGELIMINATION_H

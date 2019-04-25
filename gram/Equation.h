//
// Created by patutinaam on 11.03.19.
//

#ifndef LAB1_EQUATION_H
#define LAB1_EQUATION_H


#include <stack>
#include <string>
#include <list>
#include "GramSymbol.h"
#include "NotTerminal.h"
#include "../regexp/RegExpression.h"

class Equation {
private:
    NotTerminal* resNotTerm;
    RegExpression* rule;
public:
    NotTerminal* getResNotTerm();

    void setResNotTerm(NotTerminal* resNotTerm);

    RegExpression* getRule() ;

    void setRule(RegExpression* rule);

    std::string toString();

    void fromString(std::string equation);
};


#endif //LAB1_EQUATION_H

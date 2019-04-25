//
// Created by patutinaam on 11.03.19.
//

#include "Equation.h"
#include "../regexp/RegExpression.h"

std::string Equation::toString() {
    return resNotTerm->getName() + " -> " + rule->toString();
}

void Equation::fromString(std::string equation) {
    unsigned long posNotTerm = equation.find_first_of("->");
    std::string notTermName = equation.erase(0, posNotTerm);
    resNotTerm->setName(notTermName);
}

NotTerminal* Equation::getResNotTerm() {
    return resNotTerm;
}

void Equation::setResNotTerm(NotTerminal *resNotTerm) {
    Equation::resNotTerm = resNotTerm;
}

RegExpression* Equation::getRule() {
    return rule;
}

void Equation::setRule(RegExpression* rule) {
    this->rule = rule;
}

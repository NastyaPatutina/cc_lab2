//
// Created by Nastya Patutina on 2019-04-17.
//

#include <vector>
#include "LeftFactoringElimination.h"

LeftFactoringElimination::LeftFactoringElimination(std::list <Equation*> rules) {
    this->rules=rules;
    perform_left_recursion_elimination();
}

void LeftFactoringElimination::perform_left_recursion_elimination() {
    std::list<Equation*>::iterator i;
    for (i = rules.begin(); i != rules.end(); ++i) {
        left_recursion_elimination(*i);
    }
}

void LeftFactoringElimination::left_recursion_elimination(Equation* grammar_rule) {
    NotTerminal* equal_tokens = grammar_rule->getResNotTerm();
    std::list<RegExpression*> or_tokens = grammar_rule->getRule()->getOrNodes();

    NotTerminal* current_non_terminal = new NotTerminal(*equal_tokens);
    std::list<RegExpression*> alpha, beta;
    std::list<RegExpression*>::iterator j;
    for (j = or_tokens.begin(); j != or_tokens.end(); ++j) {
        std::list<RegExpression*> tokens = (*j)->getNodes();
        if(tokens.front()->toString() == current_non_terminal->getName()) {
            (*j)->removeNode(tokens.front());
            alpha.push_back(*j);
        } else {
            beta.push_back(*j);
        }
    }

    if(alpha.size() != 0) {
        Equation* first_rule = new Equation();
        Equation* second_rule = new Equation();
        NotTerminal* temp_non_terminal = new NotTerminal(current_non_terminal->getName() + "\'");
        first_rule->setResNotTerm(current_non_terminal);
        std::list<RegExpression*>::iterator j;
        RegExpression* rule = new RegExpression();
        for (j = beta.begin(); j != beta.end(); ++j) {
            RegExpression* tmp_rule = new RegExpression(*(*j));
            tmp_rule->addSymbol(temp_non_terminal);
            if(j != beta.begin())
                rule = rule->addOrRegExpression(tmp_rule);
            else
                rule = tmp_rule;
        }
        first_rule->setRule(rule);

        second_rule->setResNotTerm(temp_non_terminal);
        rule = new RegExpression();
        for (j = alpha.begin(); j != alpha.end(); ++j) {
            RegExpression* tmp_rule = new RegExpression(*(*j));
            tmp_rule->addSymbol(temp_non_terminal);
            if(j != alpha.begin())
                rule = rule->addOrRegExpression(tmp_rule);
            else
                rule = tmp_rule;
        }
        rule = rule->addOrRegExpression(new RegExpression(new Terminal("l")));
        second_rule->setRule(rule);

        non_recursive_grammar.push_back(first_rule);
        non_recursive_grammar.push_back(second_rule);

    } else {
        non_recursive_grammar.push_back(grammar_rule);
    }
}

std::list<Equation *> LeftFactoringElimination::get_left_factor_rules() {
    return non_recursive_grammar;
}



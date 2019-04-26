
#include "DeletingUnreachableCharacters.h"

DeletingUnreachableCharacters::DeletingUnreachableCharacters(Gramatic* gramatic) {
    this->gramatic = gramatic;
    this->not_terminals.push_back(gramatic->getStartSymbol());
    deleting_unreachable_characters();
}

std::list<Equation *> DeletingUnreachableCharacters::get_norm_rules() {
    return norm_grammar;
}

bool containsNotTerm(std::list<NotTerminal *> terms, NotTerminal * not_term){
    std::list<NotTerminal *>::iterator itr;
    for (itr = terms.begin(); itr != terms.end(); ++itr) {
        if((*itr)->getName() == not_term->getName())
            return true;
    }
    return false;
}

void DeletingUnreachableCharacters::deleting_unreachable_characters() {
    bool changed = true;
    std::list<NotTerminal *> old;
    while (changed) {
        old = this->not_terminals;

        std::list<NotTerminal *>::iterator it;
        for (it = old.begin(); it != old.end(); ++it) {
            Equation *eq = this->gramatic->findEquationForNotTerm(*(*it));
            std::list<NotTerminal *> res = eq->getRule()->getNotTerminals();
            std::list<NotTerminal *>::iterator itr;
            for (itr = res.begin(); itr != res.end(); ++itr) {
                if(!containsNotTerm(this->not_terminals, *itr)){
                    this->not_terminals.push_back(*itr);
                }
            }
        }

        if (this->not_terminals.size() == old.size()) {
            changed = false;
        }
    }

    std::list<NotTerminal *>::iterator it;
    for (it = this->not_terminals.begin(); it != this->not_terminals.end(); ++it) {
        norm_grammar.push_back( this->gramatic->findEquationForNotTerm(*(*it)));
    }
}

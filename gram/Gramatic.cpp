//
// Created by patutinaam on 11.03.19.
//

#include <iostream>
#include "Gramatic.h"

const std::list<Terminal> &Gramatic::getTerminals() const {
    return terminals;
}

void Gramatic::setTerminals(const std::list<Terminal> &terminals) {
    Gramatic::terminals = terminals;
}

const std::list<NotTerminal> &Gramatic::getNotTerminals() const {
    return notTerminals;
}

void Gramatic::setNotTerminals(const std::list<NotTerminal> &notTerminals) {
    Gramatic::notTerminals = notTerminals;
}

const std::list<Equation*> &Gramatic::getRules() const {
    return rules;
}

void Gramatic::setRules(const std::list<Equation*> &rules) {
    Gramatic::rules = rules;
}

NotTerminal* Gramatic::getStartSymbol() {
    return startSymbol;
}

void Gramatic::setStartSymbol(NotTerminal* startSymbol) {
    this->startSymbol = startSymbol;
}

Terminal* Gramatic::getTerminal(std::string termName) {
    if (termName == "") {
        return NULL;
    }

    std::list<Terminal>::iterator i;
    for(i = terminals.begin(); i != terminals.end(); ++i) {
        if (i->getName() == termName)
            return &(*i);
    }
    return NULL;
}

NotTerminal* Gramatic::getNotTerminal(std::string notTermName) {
    if (notTermName == "") {
        return NULL;
    }

    std::list<NotTerminal>::iterator i;
    for(i = notTerminals.begin(); i != notTerminals.end(); ++i) {
        if (i->getName() == notTermName)
            return &(*i);
    }
    return NULL;
}

Equation* Gramatic::findEquationForNotTerm(const NotTerminal &startSymbol) {
    std::list<Equation*>::iterator i;
    for(i = rules.begin(); i != rules.end(); ++i) {
        if ((*i)->getResNotTerm()->getName() == startSymbol.getName())
            return *i;
    }
    return NULL;
}

Gramatic::Gramatic(){}

void Gramatic::printGramm() {
    std::cout << "Grammar" << std::endl;

    std::cout << "Terminals:" << std::endl;
    std::list<Terminal>::iterator iterm;
    for(iterm = terminals.begin(); iterm != terminals.end(); ++iterm) {
        std::cout << "  " << (*iterm).getName();
    }
    std::cout << std::endl;

    std::cout << "No terminals:" << std::endl;
    std::list<NotTerminal>::iterator interm;
    for(interm = notTerminals.begin(); interm != notTerminals.end(); ++interm) {
        std::cout << "  " << (*interm).getName();
    }
    std::cout << std::endl;

    std::cout << "Rules:" << std::endl;
    std::list<Equation*>::iterator i;
    for(i = rules.begin(); i != rules.end(); ++i) {
        std::cout << "  " << (*i)->toString() << std::endl;
    }

    std::cout << "Start symbol:" << this->startSymbol->getName() << std::endl;
}

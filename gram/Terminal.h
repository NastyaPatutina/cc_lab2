//
// Created by patutinaam on 11.03.19.
//

#ifndef LAB1_TERMINAL_H
#define LAB1_TERMINAL_H


#include "GramSymbol.h"

class Terminal : public GramSymbol {
public:
    Terminal(std::string name) {
        this->setName(name);
    }

    Terminal() {}

    bool isTerm(){
        return true;
    }
};


#endif //LAB1_TERMINAL_H

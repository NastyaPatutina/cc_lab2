//
// Created by patutinaam on 11.03.19.
//

#ifndef LAB1_NOTTERMINAL_H
#define LAB1_NOTTERMINAL_H


#include "GramSymbol.h"

class NotTerminal : public GramSymbol {
public:
    NotTerminal(std::string name){
        this->name = name;
    }

    NotTerminal() {};

    bool isTerm(){
        return false;
    }
};


#endif //LAB1_NOTTERMINAL_H

//
// Created by Nastya Patutina on 2019-04-17.
//

#include "../gram/Equation.h"
#include "../gram/Gramatic.h"
#include <iterator>

class DeletingUnreachableCharacters {
public:
    DeletingUnreachableCharacters(Gramatic* gramatic);
    std::list<Equation*> get_norm_rules();

private:
    Gramatic* gramatic;
    std::list <Terminal*> terminals;
    std::list <NotTerminal*> not_terminals;

    std::list<Equation*> norm_grammar;

    void perform_deleting();

    void deleting_unreachable_characters();
};
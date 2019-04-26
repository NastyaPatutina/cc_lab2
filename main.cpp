#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>
#include <iostream>
#include <zconf.h>
#include "nlohmann/json.hpp"
#include "gram/GramSymbol.h"
#include "gram/Terminal.h"
#include "gram/NotTerminal.h"
#include "gram/Equation.h"
#include "gram/Gramatic.h"
#include "elimination/LeftFactoringElimination.h"
#include "elimination/DeletingUnreachableCharacters.h"

using json = nlohmann::json;

Gramatic* fill_gramm(json j) {
    Gramatic* gm = new Gramatic();
    std::list<NotTerminal> notterms;
    std::list<Terminal> terms;
    for(json::iterator it = j["notTerminal"].begin(); it != j["notTerminal"].end(); ++it) {
        NotTerminal* notTerm = new NotTerminal();
        notTerm->setName(*it);
        notterms.push_back(*notTerm);
    }
    for(json::iterator it = j["terminal"].begin(); it != j["terminal"].end(); ++it) {
        Terminal* term = new Terminal();
        term->setName(*it);
        terms.push_back(*term);
    }
    gm->setNotTerminals(notterms);
    gm->setTerminals(terms);
    std::list<Equation*> grammRules;
    for(json::iterator it = j["rules"].begin(); it != j["rules"].end(); ++it) {
        Equation* eq = new Equation();
        NotTerminal* term = new NotTerminal();
        term->setName((*it).at("res"));
        eq->setResNotTerm(term);
        RegExpression* rules = new RegExpression();
        bool isNewRule = true;
        json subj = *it;
        for(json::iterator itRule = subj["rules"].begin(); itRule != subj["rules"].end(); ++itRule) {
            std::string currentRule = (*itRule);
            RegExpression* regExp = new RegExpression();
            std::string lastChopedRule = currentRule;
            currentRule += "ARRR";
            while(lastChopedRule != currentRule) {
                currentRule = lastChopedRule;
                bool isModified = false;
                std::list<Terminal>::iterator i;
                for (i = terms.begin(); i != terms.end(); ++i) {
                    if (currentRule.find_first_of((*i).getName()) == 0) {
                        regExp->addSymbol(new Terminal(*i));
                        lastChopedRule = lastChopedRule.erase(0, (*i).getName().length());
                        isModified = true;
                    }
                }
                std::list<NotTerminal>::iterator it;
                for (it = notterms.begin(); it != notterms.end(); ++it) {
                    if (currentRule.find_first_of((*it).getName()) == 0) {
                        regExp->addSymbol(new NotTerminal(*it));
                        lastChopedRule = lastChopedRule.erase(0, (*it).getName().length());
                        isModified = true;
                    }
                }
                if (lastChopedRule !="" && !isModified){
                    std::cout << "Can't parse rule" << lastChopedRule;
                    return NULL;
                }
            }
            if (isNewRule){
                rules = regExp;
                isNewRule = false;
            } else {
                rules = rules->addOrRegExpression(regExp);
            }
        }
        eq->setRule(rules);
        grammRules.push_back(eq);
    }
    gm->setRules(grammRules);
    NotTerminal* notTerm = gm->getNotTerminal(j["start"]);
    gm->setStartSymbol(notTerm);
    return gm;
}
void testing(std::list<std::string> list){
    std::list<std::string>::iterator i;
    for (i = list.begin(); i != list.end(); ++i) {
        std::ifstream infile("../" + *i + ".json");
        std::cout << "\n\n----------------INPUT GRAMM----------------\n";
        json j = json::parse(infile);
        Gramatic* gm = fill_gramm(j);
        gm->printGramm();

        std::cout << "\n\n----------------Elimination----------------\n";
        LeftFactoringElimination* lf = new LeftFactoringElimination(gm->getRules());
        Gramatic* new_gm = new Gramatic(*gm);
        new_gm->setRules(lf->get_left_factor_rules());
        new_gm->printGramm();

        std::cout << "\n\n----------------Unreachable Characters----------------\n";
        DeletingUnreachableCharacters* duc = new DeletingUnreachableCharacters(gm);
        Gramatic* norm_gram = new Gramatic(*gm);
        norm_gram->setRules(duc->get_norm_rules());
        norm_gram->printGramm();
    }
}

int main(int argc, char *argv[]) {
    std::string file_name = "../inputGramm2.json";
    if (argc==2){
        if (strcmp(argv[1], "--test") == 0){
            std::list<std::string> test_names {"inputGramm", "inputGramm2", "inputGramm3", "inputGramm4"};
            testing(test_names);
            return 0;
        } else {
            file_name = argv[1];
        }
    }
    std::cout << "\n\n----------------INPUT GRAMM----------------\n";
    std::ifstream infile(file_name);
    json j = json::parse(infile);
    Gramatic* gm = fill_gramm(j);
    gm->printGramm();

    std::cout << "\n\n----------------Elimination----------------\n";
    LeftFactoringElimination* lf = new LeftFactoringElimination(gm->getRules());
    Gramatic* new_gm = new Gramatic(*gm);
    new_gm->setRules(lf->get_left_factor_rules());
    new_gm->printGramm();

    std::cout << "\n\n----------------Unreachable Characters----------------\n";
    DeletingUnreachableCharacters* duc = new DeletingUnreachableCharacters(gm);
    Gramatic* norm_gram = new Gramatic(*gm);
    norm_gram->setRules(duc->get_norm_rules());
    norm_gram->printGramm();

    return 0;
}
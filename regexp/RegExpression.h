//
// Created by patutinaam on 11.03.19.
//

#ifndef LAB1_REGEXPRESSION_H
#define LAB1_REGEXPRESSION_H

#include "../gram/Terminal.h"
#include "../gram/NotTerminal.h"
#include <list>


class RegExpression {
public:
    enum Quantifier {
        Non = 0,
        MoreNull = 1,
        MoreOne = 2
    };

    struct Item {
        GramSymbol* body;
        Quantifier quantifier;
        std::list<RegExpression*> regExpressions;
        bool isOr = false;
    public:
        bool operator==(const RegExpression::Item item) const{
            return body->getName() == item.body->getName() &&
                    quantifier == item.quantifier &&
                    isOr == item.isOr &&
                    quantifier == item.quantifier &&
                    regExpressions == item.regExpressions;
        }

        RegExpression*  getRegExpression(){
            return regExpressions.front();
        }

        std::string toString() {
            std::string res = "";
            std::list<RegExpression*>::iterator i;

            if (regExpressions.size() > 0) {
                res += regExpressions.front()->toString();
                for (i = std::next(regExpressions.begin()); i != regExpressions.end(); ++i) {
                    if (isOr) {
                        res += "|" + (*i)->toString();
                    } else {
                        res += (*i)->toString();
                    }
                }
                return res;
            }

            if (body->getName() != "")
                res += body->getName();

            if (quantifier == Quantifier::MoreNull) {
                res = "(" + res + ")";
                res += "*";
            }

            if (quantifier == Quantifier::MoreOne) {
                res = "(" + res + ")";
                res += "+";
            }

            return res;
        }

        std::list<Terminal*> getTerminals() {
            std::list<Terminal*> res;
            std::list<RegExpression*>::iterator i;

            if (regExpressions.size() > 0) {
                for (i = regExpressions.begin(); i != regExpressions.end(); ++i) {
                    res.merge((*i)->getTerminals());
                }
                return res;
            }

            if (body->getName() != "")
                if (body->isTerm())
                    res.push_back((Terminal*)body);


            return res;
        }

        std::list<NotTerminal*> getNotTerminals() {
            std::list<NotTerminal*> res;
            std::list<RegExpression*>::iterator i;

            if (regExpressions.size() > 0) {
                for (i = regExpressions.begin(); i != regExpressions.end(); ++i) {
                    res.merge((*i)->getNotTerminals());
                }
                return res;
            }

            if (body->getName() != "")
                if (!body->isTerm())
                    res.push_back((NotTerminal*)body);


            return res;
        }
    };
    RegExpression();
    RegExpression(GramSymbol* terminal);
    void addSymbol(GramSymbol* terminal);
    void addSymbol(RegExpression* terminal);
    void addSymbol(GramSymbol* terminal, Quantifier quantifier);
    std::string toString();
    RegExpression* addQuantifier(RegExpression::Quantifier quantifier);
    RegExpression* addOrRegExpression(RegExpression* regExpression);
    bool operator==(const RegExpression regExpression) const;
    RegExpression::Item getRegExpBody();
    std::list<RegExpression*> getNodes();
    void removeNode(RegExpression* regExpression);
    std::list<RegExpression *> getOrNodes();
    std::list<Terminal*> getTerminals();
    std::list<NotTerminal*> getNotTerminals();

private:
    Item regExpBody;
};


#endif //LAB1_REGEXPRESSION_H

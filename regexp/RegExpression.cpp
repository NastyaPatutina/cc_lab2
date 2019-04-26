//
// Created by patutinaam on 11.03.19.
//

#include "RegExpression.h"

RegExpression::RegExpression(GramSymbol* terminal) {
    Item item;
    item.body = terminal;
    item.quantifier = Quantifier::Non;
    this->regExpBody = item;
}

void RegExpression::addSymbol(GramSymbol* terminal, RegExpression::Quantifier quantifier) {
    RegExpression* regExpression = new RegExpression();
    Item item;
    item.body = terminal;
    item.quantifier = quantifier;
    regExpression->regExpBody = item;
    this->regExpBody.regExpressions.push_back(regExpression);
}

void RegExpression::addSymbol(RegExpression* terminal) {
    Item item;
    item.quantifier = Quantifier::Non;
    item.regExpressions.push_front(this);
    item.regExpressions.push_front(terminal);
    this->regExpBody = item;
}

RegExpression* RegExpression::addQuantifier(RegExpression::Quantifier quantifier) {
    RegExpression* regExpression = new RegExpression();
    Item item;
    item.regExpressions.push_back(new RegExpression(*this));
    item.quantifier = quantifier;
    regExpression->regExpBody = item;
    return regExpression;
}

void RegExpression::addSymbol(GramSymbol* terminal) {
    RegExpression* regExpression = new RegExpression();
    Item item;
    item.body = terminal;
    item.quantifier = Quantifier::Non;
    regExpression->regExpBody = item;
    this->regExpBody.regExpressions.push_back(regExpression);
}

std::string RegExpression::toString() {
    std::string res = "";
    res += regExpBody.toString();
    return res;
}

RegExpression::RegExpression() {}

bool RegExpression::operator==(const RegExpression regExpression) const {
    return this->regExpBody == regExpression.regExpBody;
}

RegExpression *RegExpression::addOrRegExpression(RegExpression* regExpression) {
    RegExpression* newRegExpression = new RegExpression();
    Item item;
    if (this->regExpBody.isOr){
        item.regExpressions.merge(this->regExpBody.regExpressions);
    } else {
        item.regExpressions.push_back(new RegExpression(*this));
    }
    item.regExpressions.push_back(new RegExpression(*regExpression));
    item.isOr = true;
    item.quantifier = Quantifier::Non;
    newRegExpression->regExpBody = item;
    return newRegExpression;
}

RegExpression::Item RegExpression::getRegExpBody() {
    return this->regExpBody;
}
std::list<RegExpression*> RegExpression::getNodes() {
        return this->regExpBody.regExpressions;
}

std::list<RegExpression*> RegExpression::getOrNodes() {
    if (this->regExpBody.isOr)
        return this->regExpBody.regExpressions;
    std::list<RegExpression*> res;
    res.push_back(this);
    return res;
}

void RegExpression::removeNode(RegExpression* regExpression) {
    this->regExpBody.regExpressions.remove(regExpression);
}

std::list<NotTerminal *> RegExpression::getNotTerminals() {
    return this->regExpBody.getNotTerminals();
}

std::list<Terminal *> RegExpression::getTerminals() {
    return this->regExpBody.getTerminals();
}
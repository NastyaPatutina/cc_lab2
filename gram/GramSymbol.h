//
// Created by patutinaam on 11.03.19.
//

#ifndef LAB1_GRAMSYMBOL_H
#define LAB1_GRAMSYMBOL_H

#include <string>


class GramSymbol {
protected:
    std::string name = "";

public:
    GramSymbol() {}

    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name) {
        GramSymbol::name = name;
    }
};


#endif //LAB1_GRAMSYMBOL_H

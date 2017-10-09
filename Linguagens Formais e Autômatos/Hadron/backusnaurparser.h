#ifndef BACKUSNAURPARSER_H
#define BACKUSNAURPARSER_H

#include <string>
#include <unordered_map>
#include <iostream>
#include "defs.h"

class BackusNaurParser
{
public:
    BackusNaurParser();
    BackusNaurParser(const std::string& grammar);

    void parse(const std::string& grammar);
    static inline bool isNonterminal(const std::string& str);
    void reset();
    void dumpRules(std::ostream& out = std::cout);

private:
    std::unordered_map<std::string, uint> index;
    std::vector<Productions> rules;
    std::vector<std::string> nonterminals;

    bool addRule(const std::string& nonterminal, const Productions& productions);
};

#endif // BACKUSNAURPARSER_H

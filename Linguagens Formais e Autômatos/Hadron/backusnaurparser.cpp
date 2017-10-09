#include "backusnaurparser.h"
#include "utils.h"
#include <sstream>
#include <regex>
#include <iostream>

BackusNaurParser::BackusNaurParser()
{

}

BackusNaurParser::BackusNaurParser(const std::string& grammar)
{
    parse(grammar);
}

void BackusNaurParser::parse(const std::string& grammar)
{
    std::string line;
    std::stringstream stream(grammar);
    std::regex regex("\\s*(<.+>)\\s*::=\\s*(.*)$");

    while (std::getline(stream, line)) {
        std::smatch m;
        std::regex_match(line, m, regex);

        if (m.size() != 3) {
            std::cerr << "Could not find right and left hand expressions.\n";
            return;
        }

        if (!addRule(m[1], Utils::split(m[2], '|'))) {
            reset();
            return;
        }
    }
}

bool BackusNaurParser::isNonterminal(const std::string& str)
{
    return str.front() == '<' && str.back() == '>';
}

void BackusNaurParser::reset()
{
    index.clear();
    rules.clear();
}

bool BackusNaurParser::addRule(const std::string& nonterminal, const Productions& productions)
{
    if (!isNonterminal(nonterminal)) {
        std::cerr << "Malformed nonterminal on left hand side.\n";
        return false;
    }

    auto ruleIt = index.find(nonterminal);
    if (ruleIt == index.end()) {
        ruleIt = index.insert({nonterminal, nonterminals.size()}).first;
        rules.push_back(Productions());
        nonterminals.push_back(nonterminal);
    }

    Productions& rule = rules[ruleIt->second];

    for (std::string p : productions) {
        Utils::trim(p);
        rule.push_back(p);
    }

    return true;
}

void BackusNaurParser::dumpRules(std::ostream& out)
{
    for (uint i = 0; i < nonterminals.size(); i++) {
        out << nonterminals[i] << "\n";
        for (const std::string& p : rules[i]) {
            out << "- " << p << "\n";
        }
    }
}

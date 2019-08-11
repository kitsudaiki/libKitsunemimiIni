/**
 *  @file    iniParserInterface.hpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef INIPARSERINTERFACE_HPP
#define INIPARSERINTERFACE_HPP

#include <vector>
#include <string>
#include <string>
#include <map>
#include <data_structure/dataItems.hpp>

#include <iostream>

using Kitsune::Common::DataItem;
using std::string;
using std::map;
using std::pair;

namespace Kitsune
{
namespace Ini
{
class location;

class IniParserInterface
{

public:
    IniParserInterface(const bool traceParsing);

    // connection the the scanner and parser
    void scan_begin(const std::string &inputString);
    void scan_end();
    bool parse(const std::string &inputString);
    std::string removeQuotes(std::string input);

    // output-handling
    void setOutput(DataItem* output);
    DataItem* getOutput() const;

    // Error handling.
    void error(const Kitsune::Ini::location &location,
               const std::string& message);
    std::string getErrorMessage() const;

private:
    DataItem* m_output;
    std::string m_errorMessage = "";
    std::string m_inputString = "";

    bool m_traceParsing = false;
};

}  // namespace Ini
}  // namespace Kitsune

#endif // INIPARSERINTERFACE_HPP

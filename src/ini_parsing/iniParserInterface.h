/**
 *  @file    iniParserInterface.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef INIPARSERINTERFACE_HH
#define INIPARSERINTERFACE_HH

#include <vector>
#include <string>
#include <string>
#include <map>
#include <jsonItems.h>

#include <iostream>

using namespace Kitsune::Json;
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

    // output-handling
    void setOutput(map<string, map<string, JsonItem *>> output);
    map<string, map<string, JsonItem *>> getOutput() const;

    // Error handling.
    void error(const Kitsune::Ini::location &location,
               const std::string& message);
    std::string getErrorMessage() const;

private:
    map<string, map<string, JsonItem *>> m_output;
    std::string m_errorMessage = "";
    std::string m_inputString = "";

    bool m_traceParsing = false;
};

}  // namespace Ini
}  // namespace Kitsune

#endif // ! INIPARSERINTERFACE_HH

/**
 *  @file    ini_parser_interface.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef INIPARSERINTERFACE_H
#define INIPARSERINTERFACE_H

#include <vector>
#include <string>
#include <map>
#include <mutex>
#include <libKitsunemimiCommon/common_items/data_items.h>

using Kitsunemimi::DataItem;
using std::string;
using std::map;
using std::pair;

namespace Kitsunemimi
{
namespace Ini
{
class location;

class IniParserInterface
{

public:
    static IniParserInterface* getInstance();

    // connection the the scanner and parser
    void scan_begin(const std::string &inputString);
    void scan_end();
    DataItem* parse(const std::string &inputString, std::string &errorMessage);
    const std::string removeQuotes(const std::string &input);

    // output-handling
    void setOutput(DataItem* output);

    // Error handling.
    void error(const Kitsunemimi::Ini::location &location,
               const std::string& message);

    // static variables, which are used in lexer and parser
    static bool m_outsideComment;

private:
    IniParserInterface(const bool traceParsing = false);

    static IniParserInterface* m_instance;

    DataItem* m_output = nullptr;
    std::string m_errorMessage = "";
    std::string m_inputString = "";
    std::mutex m_lock;

    bool m_traceParsing = false;
};

}  // namespace Ini
}  // namespace Kitsunemimi

#endif // INIPARSERINTERFACE_H

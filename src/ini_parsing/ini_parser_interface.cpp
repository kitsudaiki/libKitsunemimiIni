/**
 *  @file    ini_parser_interface.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include <ini_parsing/ini_parser_interface.h>
#include <ini_parser.h>
#include <libKitsunemimiCommon/common_methods/string_methods.h>

# define YY_DECL \
    Kitsunemimi::Ini::IniParser::symbol_type inilex (Kitsunemimi::Ini::IniParserInterface& driver)
YY_DECL;


namespace Kitsunemimi
{
namespace Ini
{

Kitsunemimi::Ini::IniParserInterface* IniParserInterface::m_instance = nullptr;

using Kitsunemimi::splitStringByDelimiter;

bool IniParserInterface::m_outsideComment = true;

/**
 * The class is the interface for the bison-generated parser.
 * It starts the parsing-process and store the returned values.
 *
 * @param traceParsing If set to true, the scanner prints all triggered rules.
 *                     It is only for better debugging.
 */
IniParserInterface::IniParserInterface(const bool traceParsing)
{
    m_traceParsing = traceParsing;
}

/**
 * @brief static methode to get instance of the interface
 *
 * @return pointer to the static instance
 */
IniParserInterface*
IniParserInterface::getInstance()
{
    if(m_instance == nullptr) {
        m_instance = new IniParserInterface();
    }

    return m_instance;
}

/**
 * @brief parse string
 *
 * @param inputString string which should be parsed
 * @param reference for error-message
 *
 * @return resulting object
 */
DataItem*
IniParserInterface::parse(const std::string &inputString,
                          std::string &errorMessage)
{
    DataItem* result = nullptr;

    m_lock.lock();

    // init global values
    m_inputString = inputString;
    m_errorMessage = "";
    if(m_output != nullptr) {
        delete m_output;
    }
    m_output = nullptr;

    // run parser-code
    this->scan_begin(inputString);
    Kitsunemimi::Ini::IniParser parser(*this);
    int res = parser.parse();
    this->scan_end();

    // handle negative result
    if(res != 0)
    {
        errorMessage = m_errorMessage;
        m_lock.unlock();
        return nullptr;
    }

    result = m_output->copy();

    m_lock.unlock();

    return result;
}

/**
 * @brief remove double quotes from the beginning and the end of a string
 *
 * @param input string to clear
 *
 * @return cleared string
 */
const std::string
IniParserInterface::removeQuotes(const std::string &input)
{
    // precheck
    if(input.length() == 0) {
        return input;
    }

    // clear
    if(input[0] == '\"'
            && input[input.length()-1] == '\"')
    {
        std::string result = "";
        for(uint32_t i = 1; i < input.length()-1; i++) {
            result += input[i];
        }

        return result;
    }

    return input;
}

/**
 * Is called for the parser after successfully parsing the input-string
 *
 * @param output parser-output as DataArray
 */
void
IniParserInterface::setOutput(DataItem *output)
{
     m_output = output;
}

/**
 * Is called from the parser in case of an error
 *
 * @param location location-object of the bison-parser,
 *                 which contains the informations of the location
 *                 of the syntax-error in the parsed string
 * @param message error-specific message from the parser
 */
void
IniParserInterface::error(const Kitsunemimi::Ini::location& location,
                          const std::string& message)
{
    // get the broken part of the parsed string
    const uint32_t errorStart = location.begin.column;
    const uint32_t errorLength = location.end.column - location.begin.column;
    const uint32_t linenumber = location.begin.line;

    std::vector<std::string> splittedContent;
    splitStringByDelimiter(splittedContent, m_inputString, '\n');

    // -1 because the number starts for user-readability at 1 instead of 0
    const std::string errorStringPart = splittedContent[linenumber - 1].substr(errorStart - 1,
                                                                               errorLength);

    // build error-message
    m_errorMessage =  "ERROR while parsing ini-formated string \n";
    m_errorMessage += "parser-message: " + message + " \n";
    m_errorMessage += "line-number: " + std::to_string(linenumber) + " \n";
    m_errorMessage += "position in line: " + std::to_string(location.begin.column) + " \n";
    m_errorMessage += "broken part in string: \"" + errorStringPart + "\" \n";
}

}  // namespace Ini
}  // namespace Kitsunemimi

/**
 *  @file    libKitsuneIni.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "libKitsuneIni.h"

#include <ini_parsing/iniParserInterface.h>

namespace Kitsune
{
namespace Ini
{

/**
 * constructor
 */
KitsuneIniConverter::KitsuneIniConverter(const bool traceParsing)
{
    m_parser = new IniParserInterface(traceParsing);
}

/**
 * destructor
 */
KitsuneIniConverter::~KitsuneIniConverter()
{
    delete m_parser;
}

/**
 * @brief KitsuneIniConverter::parse
 * @param content
 * @return
 */
pair<map<std::string, map<std::string, Json::JsonItem *> >, bool>
KitsuneIniConverter::parse(const std::string &content)
{
    pair<map<std::string, map<std::string, Json::JsonItem *> >, bool> result;

    // parse jinja2-template into a json-tree
    result.second = m_parser->parse(content);

    // process a failure
    if(result.second == false) {
        return result;
    }

    result.first = m_parser->getOutput();

    return result;
}

}  // namespace Ini
}  // namespace Kitsune

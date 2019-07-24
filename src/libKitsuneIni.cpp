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
 * @brief IniObject::IniObject
 */
IniObject::IniObject()
{

}

/**
 * @brief IniObject::parse
 * @param content
 * @return
 */
pair<std::string, bool>
IniObject::parse(const std::string &content,
                 const bool traceParsing)
{
    pair<std::string, bool> result;
    IniParserInterface parser(traceParsing);

    // parse jinja2-template into a json-tree
    result.second = parser.parse(content);

    // process a failure
    if(result.second == false) {
        result.first = parser.getErrorMessage();
        return result;
    }

    m_content = parser.getOutput();

    return result;
}

/**
 * @brief IniObject::get
 * @param group
 * @param item
 * @return
 */
Json::JsonItem*
IniObject::get(const std::string &group,
               const std::string &item)
{
    map<string, map<string, JsonItem*>>::iterator itGroup;
    itGroup = m_content.find(group);

    if(itGroup != m_content.end())
    {
        map<string, JsonItem*>::iterator itItem;
        itItem = itGroup->second.find(item);

        if(itItem != itGroup->second.end()) {
            return itItem->second->copy();
        }
    }

    return nullptr;
}

/**
 * @brief IniObject::print
 * @return
 */
std::string IniObject::print()
{
    std::string output = "";

    map<string, map<string, JsonItem*>>::iterator itGroup;
    for(itGroup = m_content.begin();
        itGroup != m_content.end();
        itGroup++)
    {
        output.append("[");
        output.append(itGroup->first);
        output.append("]\n");

        map<string, JsonItem*>::iterator itItem;
        for(itItem = itGroup->second.begin();
            itItem != itGroup->second.end();
            itItem++)
        {
            output.append(itItem->first);
            output.append(" = ");
            itItem->second->print(&output);
            output.append("\n");
        }

        output.append("\n");
    }

    return output;
}

}  // namespace Ini
}  // namespace Kitsune

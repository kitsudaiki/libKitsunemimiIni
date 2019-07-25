/**
 *  @file    iniItem.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "iniItem.h"

#include <ini_parsing/iniParserInterface.h>

namespace Kitsune
{
namespace Ini
{

/**
 * @brief IniObject::IniObject
 */
IniItem::IniItem()
{

}

/**
 * @brief IniObject::parse
 * @param content
 * @return
 */
pair<std::string, bool>
IniItem::parse(const std::string &content,
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
IniItem::get(const std::string &group,
             const std::string &item)
{
    JsonItem* groupContent = m_content->get(group);
    if(groupContent == nullptr) {
        return nullptr;
    }
    return groupContent->get(item);
}

/**
 * @brief IniObject::print
 * @return
 */
std::string IniItem::print()
{
    std::string output = "";

    std::map<std::string, JsonItem*> completeContent = m_content->toObject()->getComplete();
    std::map<std::string, JsonItem*>::iterator itGroup;
    for(itGroup = completeContent.begin();
        itGroup != completeContent.end();
        itGroup++)
    {
        output.append("[");
        output.append(itGroup->first);
        output.append("]\n");

        std::map<std::string, JsonItem*> groupContent = itGroup->second->toObject()->getComplete();
        map<string, JsonItem*>::iterator itItem;
        for(itItem = groupContent.begin();
            itItem != groupContent.end();
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

/**
 * @brief IniItem::setContent
 * @param item
 */
void
IniItem::setContent(JsonItem *item)
{
    if(m_content != nullptr) {
        delete m_content;
    }
    m_content = item;
}

}  // namespace Ini
}  // namespace Kitsune

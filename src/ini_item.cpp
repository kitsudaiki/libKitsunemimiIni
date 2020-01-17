/**
 *  @file    ini_item.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include <libKitsunemimiIni/ini_item.h>

#include <libKitsunemimiCommon/common_items/data_items.h>
#include <ini_parsing/ini_parser_interface.h>

using Kitsunemimi::DataItem;
using Kitsunemimi::DataArray;
using Kitsunemimi::DataValue;
using Kitsunemimi::DataMap;

namespace Kitsunemimi
{
namespace Ini
{

/**
 * constructor
 */
IniItem::IniItem()
{
    m_content = new DataMap();
}

/**
 * destructor
 */
IniItem::~IniItem()
{
    if(m_content != nullptr) {
        delete m_content;
    }
}

/**
 * @brief parse the content of an ini-file
 *
 * @param content content of an ini-file as string
 * @param traceParsing trace parser-actions for debugging only (defualt: false)
 *
 * @return pair of bool and string
 *         success: first is true, second is empty-string
 *         fail: first is false, second is error-message
 */
std::pair<bool, std::string>
IniItem::parse(const std::string &content,
               const bool traceParsing)
{
    std::pair<bool, std::string> result;
    IniParserInterface parser(traceParsing);

    // parse ini-template into a data-tree
    result.first = parser.parse(content);

    // process a failure
    if(result.first == false)
    {
        result.second = parser.getErrorMessage();
        return result;
    }

    // delete old content, if exist and get the new one from the parser
    if(m_content != nullptr) {
        delete m_content;
    }
    m_content = parser.getOutput();

    return result;
}

/**
 * @brief get a value from the ini-item
 *
 * @param group group-name
 * @param item item-key-name
 *
 * @return requested value as data-item
 */
DataItem*
IniItem::get(const std::string &group,
             const std::string &item)
{
    DataItem* groupContent = m_content->get(group);
    if(groupContent == nullptr) {
        return nullptr;
    }
    return groupContent->get(item);
}

/**
 * @brief set a value inside the ini-items
 *
 * @param group group-name
 * @param item item-key-name
 * @param value string as new Value
 * @param force overwrite, if already exist
 *
 * @return false, if item already exist with value and force is false, else it returns true
 */
bool
IniItem::set(const std::string &group,
             const std::string &item,
             const std::string value,
             const bool force)
{
    return set(group, item, new DataValue(value), force);
}

/**
 * @brief set a value inside the ini-items
 *
 * @param group group-name
 * @param item item-key-name
 * @param value long as new Value
 * @param force overwrite, if already exist
 *
 * @return false, if item already exist with value and force is false, else it returns true
 */
bool
IniItem::set(const std::string &group,
             const std::string &item,
             const long value,
             const bool force)
{
    return set(group, item, new DataValue(value), force);
}

/**
 * @brief set a value inside the ini-items
 *
 * @param group group-name
 * @param item item-key-name
 * @param value double new Value
 * @param force overwrite, if already exist
 *
 * @return false, if item already exist with value and force is false, else it returns true
 */
bool
IniItem::set(const std::string &group,
             const std::string &item,
             const double value,
             const bool force)
{
    return set(group, item, new DataValue(value), force);
}

/**
 * @brief set a value inside the ini-items
 *
 * @param group group-name
 * @param item item-key-name
 * @param value string-list as new value
 * @param force overwrite, if already exist
 *
 * @return false, if item already exist with value and force is false, else it returns true
 */
bool
IniItem::set(const std::string &group,
             const std::string &item,
             const std::vector<std::string> value,
             const bool force)
{
    DataArray* array = new DataArray();
    for(uint64_t i = 0; i < value.size(); i++)
    {
        array->append(new DataValue(value.at(i)));
    }

    return set(group, item, array, force);
}

/**
 * @brief remove an entire group together with all its items from the ini-item
 *
 * @param group group-name
 *
 * @return false, if group doesn't exist, else true
 */
bool
IniItem::removeGroup(const std::string &group)
{
    return m_content->remove(group);
}

/**
 * @brief remove an item for the ini-item
 *
 * @param group group-name
 * @param item item-key-name
 *
 * @return false, if group or item doesn't exist, else true
 */
bool
IniItem::removeEntry(const std::string &group,
                     const std::string &item)
{
    DataItem* groupItem = m_content->get(group);
    if(groupItem == nullptr) {
        return false;
    }

    return groupItem->remove(item);
}

/**
 * @brief set a value inside the ini-items
 *
 * @param group group-name
 * @param item item-key-name
 * @param value new Value
 * @param force overwrite, if already exist
 *
 * @return false, if item already exist with value and force is false, else it returns true
 */
bool
IniItem::set(const std::string &group,
             const std::string &item,
             DataItem *value,
             const bool force)
{
    DataItem* groupContent = m_content->get(group);

    // if group doesn't exist, create the group with the new content
    if(groupContent == nullptr)
    {
        groupContent = new DataMap();
        groupContent->toMap()->insert(item, value);
        m_content->toMap()->insert(group, groupContent);
        return true;
    }

    DataItem* groupItem = groupContent->get(item);

    // item doesn't exist or should be overrided by force
    if(groupItem == nullptr
            || force)
    {
        groupContent->toMap()->insert(item, value, force);
        return true;
    }

    // I delete the value here already to avoid too much redundant code in the other set-methods
    // even this is not so nice. Thats why this is only a private methods with should be used only
    // interally
    delete value;

    return false;
}

/**
 * @brief convert the content of the ini-item into a string-output to write it into a new ini-file
 *
 * @return converted string
 */
std::string IniItem::toString()
{
    std::string output = "";

    // iterate over all groups
    std::map<std::string, DataItem*> completeContent = m_content->toMap()->m_map;
    std::map<std::string, DataItem*>::iterator itGroup;
    for(itGroup = completeContent.begin();
        itGroup != completeContent.end();
        itGroup++)
    {
        // print group-header
        output.append("[");
        output.append(itGroup->first);
        output.append("]\n");

        // iterate over group-content
        std::map<std::string, DataItem*> groupContent = itGroup->second->toMap()->m_map;
        map<string, DataItem*>::iterator itItem;
        for(itItem = groupContent.begin();
            itItem != groupContent.end();
            itItem++)
        {
            // print line of group-content
            output.append(itItem->first);
            output.append(" = ");

            if(itItem->second->getType() == DataItem::ARRAY_TYPE)
            {
                // print arrays
                std::vector<DataItem*> array = itItem->second->toArray()->m_array;
                for(uint64_t i = 0; i < array.size(); i++)
                {
                    if(i != 0) {
                        output.append(", ");
                    }
                    output.append(array.at(i)->toString());
                }
            }
            else
            {
                // print simple items
                itItem->second->toString(false, &output);
            }

            output.append("\n");
        }

        output.append("\n");
    }

    return output;
}

}  // namespace Ini
}  // namespace Kitsunemimi

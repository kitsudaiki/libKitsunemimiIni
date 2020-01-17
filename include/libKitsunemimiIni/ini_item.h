/**
 *  @file    ini_item.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef INIITEM_H
#define INIITEM_H

#include <utility>
#include <string>
#include <vector>
#include <map>

namespace Kitsunemimi
{
class DataItem;
namespace Ini
{
class IniParserInterface;

class IniItem
{

public:
    IniItem();
    ~IniItem();

    bool parse(const std::string &content,
               std::string &errorMessage,
               const bool traceParsing = false);

    // get
    DataItem* get(const std::string &group,
                  const std::string &item);

    // set
    bool set(const std::string &group,
             const std::string &item,
             const std::string value,
             const bool force=false);
    bool set(const std::string &group,
             const std::string &item,
             const long value,
             const bool force=false);
    bool set(const std::string &group,
             const std::string &item,
             const double value,
             const bool force=false);
    bool set(const std::string &group,
             const std::string &item,
             const std::vector<std::string> value,
             const bool force=false);

    // remove
    bool removeGroup(const std::string& group);
    bool removeEntry(const std::string& group,
                     const std::string& item);

    // output
    std::string toString();

    DataItem* m_content = nullptr;

private:
    bool set(const std::string& group,
             const std::string& item,
             DataItem* value,
             bool force=false);
};

}  // namespace Ini
}  // namespace Kitsunemimi

#endif // INIITEM_H

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

namespace Kitsune
{
namespace Common {
class DataItem;
}
namespace Ini
{
class IniParserInterface;

class IniItem
{

public:
    IniItem();
    ~IniItem();

    std::pair<bool, std::string> parse(const std::string &content,
                                       const bool traceParsing = false);

    // get
    Common::DataItem* get(const std::string& group,
                          const std::string& item);

    // set
    bool set(const std::string& group,
             const std::string& item,
             const std::string value,
             const bool force=false);
    bool set(const std::string& group,
             const std::string& item,
             const int value,
             const bool force=false);
    bool set(const std::string& group,
             const std::string& item,
             const float value,
             const bool force=false);
    bool set(const std::string& group,
             const std::string& item,
             const std::vector<std::string> value,
             const bool force=false);

    // remove
    bool removeGroup(const std::string& group);
    bool removeEntry(const std::string& group,
                     const std::string& item);

    // output
    std::string toString();

    Common::DataItem* m_content = nullptr;

private:
    bool set(const std::string& group,
             const std::string& item,
             Common::DataItem* value,
             bool force=false);
};

}  // namespace Ini
}  // namespace Kitsune

#endif // INIITEM_H

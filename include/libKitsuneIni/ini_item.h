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

using std::string;
using std::map;
using std::pair;

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

    pair<std::string, bool> parse(const string &content,
                                  const bool traceParsing = false);

    Common::DataItem* get(const std::string& group,
                          const std::string& item);
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

    bool removeGroup(const std::string& group);
    bool removeEntry(const std::string& group,
                     const std::string& item);

    std::string print();

    void setContent(Common::DataItem* item);

private:
    Common::DataItem* m_content = nullptr;

    bool set(const std::string& group,
             const std::string& item,
             Common::DataItem* value,
             bool force=false);
};

}  // namespace Ini
}  // namespace Kitsune

#endif // INIITEM_H

/**
 *  @file    iniItem.hpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef INIITEM_HPP
#define INIITEM_HPP

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

#endif // INIITEM_HPP

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
#include <jsonItems.hpp>

using namespace Kitsune::Json;
using std::string;
using std::map;
using std::pair;

namespace Kitsune
{
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

    JsonItem* get(const std::string& group,
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

    void setContent(JsonItem* item);

private:
    JsonItem* m_content = nullptr;

    bool set(const std::string& group,
             const std::string& item,
             JsonItem* value,
             bool force=false);
};

}  // namespace Ini
}  // namespace Kitsune

#endif // INIITEM_HPP

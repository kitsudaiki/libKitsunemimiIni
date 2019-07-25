/**
 *  @file    iniItem.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef INIITEM_H
#define INIITEM_H

#include <utility>
#include <string>
#include <jsonItems.h>

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

    pair<std::string, bool> parse(const string &content,
                                  const bool traceParsing = false);

    JsonItem* get(const std::string& group,
                  const std::string& item);
    std::string print();

    void setContent(JsonItem* item);

private:
    JsonItem* m_content = nullptr;
};

}  // namespace Ini
}  // namespace Kitsune

#endif // INIITEM_H

/**
 *  @file    libKitsuneIni.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef LIBKITSUNEINI_H
#define LIBKITSUNEINI_H

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

    map<string, map<string, JsonItem*>> m_content;
};

}  // namespace Ini
}  // namespace Kitsune

#endif // LIBKITSUNEINI_H

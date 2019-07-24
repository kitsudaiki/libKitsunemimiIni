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

using Kitsune::Json::JsonItem;
using std::string;
using std::map;
using std::pair;

namespace Kitsune
{
namespace Ini
{
class IniParserInterface;

class KitsuneIniConverter
{
public:
    KitsuneIniConverter(const bool traceParsing = false);
    ~KitsuneIniConverter();

    pair<map<string, map<string, JsonItem*>>, bool> parse(const string &content);

private:
    IniParserInterface* m_parser = nullptr;
};

}  // namespace Ini
}  // namespace Kitsune

#endif // LIBKITSUNEINI_H

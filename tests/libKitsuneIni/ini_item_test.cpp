/**
 *  @file    ini_item_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "ini_item_test.h"
#include <ini_item.h>
#include <common_items/data_items.h>

namespace Kitsune
{
namespace Ini
{

IniItem_Test::IniItem_Test()
    : Kitsune::Common::UnitTest("IniItem_Test")
{
    parse_test();
    get_test();
    set_test();
    removeGroup_test();
    removeEntry_test();
    print_test();
}

/**
 * parse_test
 */
void
IniItem_Test::parse_test()
{
    IniItem object;
    std::pair<bool, std::string> result = object.parse(getTestString());

    UNITTEST(result.first, true);
}

/**
 * get_test
 */
void
IniItem_Test::get_test()
{
    IniItem object;
    std::pair<bool, std::string> result = object.parse(getTestString());

    std::string get1 = object.get("DEFAULT", "x")->toValue()->toString();
    UNITTEST(get1, "2");

    std::string get2= object.get("hmmm", "poi_poi")->toValue()->toString();
    UNITTEST(get2, "1.300000");
}

/**
 * set_test
 */
void
IniItem_Test::set_test()
{
    IniItem object;
    std::pair<bool, std::string> result = object.parse(getTestString());

    UNITTEST(object.set("hmmm2", "poi", "asdf"), true);
    UNITTEST(object.set("hmmm2", "poi", "asdf"), false);

    UNITTEST(object.set("hmmm", "poi_poi", "asdf", true), true);

    std::string get2= object.get("hmmm", "poi_poi")->toValue()->getString();
    UNITTEST(get2, "asdf");
}

/**
 * removeGroup_test
 */
void
IniItem_Test::removeGroup_test()
{
    IniItem object;
    std::pair<bool, std::string> result = object.parse(getTestString());

    UNITTEST(object.removeGroup("hmmm"), true);
    UNITTEST(object.removeGroup("hmmm"), false);

    std::string compare = "[DEFAULT]\n"
                          "asdf = \"asdf.asdf\"\n"
                          "id = \"550e8400-e29b-11d4-a716-446655440000\"\n"
                          "x = 2\n"
                          "\n";

    UNITTEST(object.toString(), compare);
}

/**
 * removeEntry_test
 */
void
IniItem_Test::removeEntry_test()
{
    IniItem object;
    std::pair<bool, std::string> result = object.parse(getTestString());

    UNITTEST(object.removeEntry("DEFAULT", "x"), true);
    UNITTEST(object.removeEntry("DEFAULT", "x"), false);
    UNITTEST(object.removeEntry("fail", "x"), false);

    std::string compare = "[DEFAULT]\n"
                          "asdf = \"asdf.asdf\"\n"
                          "id = \"550e8400-e29b-11d4-a716-446655440000\"\n"
                          "\n"
                          "[hmmm]\n"
                          "poi_poi = 1.300000\n"
                          "\n";

    UNITTEST(object.toString(), compare);
}

/**
 * @brief helper-function for remove characters
 */
bool
isSlash(char c)
{
    if(c == '\"') {
        return true;
    } else {
        return false;
    }
}

/**
 * print_test
 */
void
IniItem_Test::print_test()
{
    IniItem object;
    std::pair<bool, std::string> result = object.parse(getTestString());

    std::string outputStringObjects = object.toString();
    outputStringObjects.erase(std::remove_if(outputStringObjects.begin(),
                                             outputStringObjects.end(),
                                             &isSlash),
                              outputStringObjects.end());
    UNITTEST(outputStringObjects, getTestString());
}

/**
 * @brief IniItem_Test::getTestString
 * @return
 */
std::string
IniItem_Test::getTestString()
{
    const std::string testString(
                "[DEFAULT]\n"
                "asdf = asdf.asdf\n"
                "id = 550e8400-e29b-11d4-a716-446655440000\n"
                "x = 2\n"
                "\n"
                "[hmmm]\n"
                "poi_poi = 1.300000\n"
                "\n");
    return testString;
}

}  // namespace Ini
}  // namespace Kitsune


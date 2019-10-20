/**
 *  @file    ini_item_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "ini_item_test.h"
#include <libKitsuneIni/ini_item.h>
#include <libKitsuneCommon/common_items/data_items.h>

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
    if(result.first == false) {
        std::cout<<"result.second: "<<result.second<<std::endl;
    }
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

    const std::string compare(
                "[DEFAULT]\n"
                "asdf = asdf.asdf\n"
                "id = 550e8400-e29b-11d4-a716-446655440000\n"
                "x = 2\n"
                "\n");

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

    const std::string compare(
                "[DEFAULT]\n"
                "asdf = asdf.asdf\n"
                "id = 550e8400-e29b-11d4-a716-446655440000\n"
                "\n"
                "[hmmm]\n"
                "poi_poi = 1.300000\n"
                "\n");

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

    const std::string outputStringObjects = object.toString();

    const std::string compare(
                "[DEFAULT]\n"
                "asdf = asdf.asdf\n"
                "id = 550e8400-e29b-11d4-a716-446655440000\n"
                "x = 2\n"
                "\n"
                "[hmmm]\n"
                "poi_poi = 1.300000\n"
                "\n");
    UNITTEST(outputStringObjects, compare);


    // negative test
    const std::string badString(
                "[DEFAULT]\n"
                "asdf = asdf.asdf\n"
                "id = 550e8400-e29b-11d4-a716-446655440000\n"
                "x = 2\n"
                "\n"
                "[hmmm]\n"
                "poi.poi = 1.300000\n"
                "\n");
    result = object.parse(badString);
    UNITTEST(result.first, false);

    const std::string compareError("ERROR while parsing ini-formated string \n"
                                   "parser-message: syntax error \n"
                                   "line-number: 7 \n"
                                   "position in line: 1 \n"
                                   "broken part in string: \"poi.poi\" \n");
    UNITTEST(result.second, compareError);
}

/**
 * @brief IniItem_Test::getTestString
 * @return
 */
const std::string
IniItem_Test::getTestString()
{
    const std::string testString(
                "[DEFAULT]\n"
                "asdf = asdf.asdf\n"
                "id = 550e8400-e29b-11d4-a716-446655440000\n"
                "x = 2\n"
                "\n\n"
                "[hmmm]\n"
                "# this is only a simple 0815 testcommit\n\n"
                "poi_poi = 1.300000\n"
                "\n");
    return testString;
}

}  // namespace Ini
}  // namespace Kitsune


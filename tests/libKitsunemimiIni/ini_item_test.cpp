/**
 *  @file    ini_item_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "ini_item_test.h"
#include <libKitsunemimiIni/ini_item.h>
#include <libKitsunemimiCommon/common_items/data_items.h>

namespace Kitsunemimi
{
namespace Ini
{

IniItem_Test::IniItem_Test()
    : Kitsunemimi::CompareTestHelper("IniItem_Test")
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
    std::string errorMessage = "";

    bool result = object.parse(getTestString(), errorMessage);

    TEST_EQUAL(result, true);
    if(result == false) {
        std::cout<<"errorMessage: "<<errorMessage<<std::endl;
    }
}

/**
 * get_test
 */
void
IniItem_Test::get_test()
{
    IniItem object;
    std::string errorMessage = "";

    object.parse(getTestString(), errorMessage);

    std::string get1 = object.get("DEFAULT", "x")->toValue()->toString();
    TEST_EQUAL(get1, "2");

    std::string get2 = object.get("hmmm", "poi_poi")->toValue()->toString();
    TEST_EQUAL(get2, "1.300000");
}

/**
 * set_test
 */
void
IniItem_Test::set_test()
{
    IniItem object;
    std::string errorMessage = "";

    object.parse(getTestString(), errorMessage);

    TEST_EQUAL(object.set("hmmm2", "poi", "asdf"), true);
    TEST_EQUAL(object.set("hmmm2", "poi", "asdf"), false);

    TEST_EQUAL(object.set("hmmm", "poi_poi", "asdf", true), true);

    std::string get2= object.get("hmmm", "poi_poi")->toValue()->getString();
    TEST_EQUAL(get2, "asdf");
}

/**
 * removeGroup_test
 */
void
IniItem_Test::removeGroup_test()
{
    IniItem object;
    std::string errorMessage = "";

    object.parse(getTestString(), errorMessage);

    TEST_EQUAL(object.removeGroup("hmmm"), true);
    TEST_EQUAL(object.removeGroup("hmmm"), false);

    const std::string compare(
                "[DEFAULT]\n"
                "asdf = asdf.asdf\n"
                "id = 550e8400-e29b-11d4-a716-446655440000\n"
                "x = 2\n"
                "\n");

    TEST_EQUAL(object.toString(), compare);
}

/**
 * removeEntry_test
 */
void
IniItem_Test::removeEntry_test()
{
    IniItem object;
    std::string errorMessage = "";

    object.parse(getTestString(), errorMessage);

    TEST_EQUAL(object.removeEntry("DEFAULT", "x"), true);
    TEST_EQUAL(object.removeEntry("DEFAULT", "x"), false);
    TEST_EQUAL(object.removeEntry("fail", "x"), false);

    const std::string compare(
                "[DEFAULT]\n"
                "asdf = asdf.asdf\n"
                "id = 550e8400-e29b-11d4-a716-446655440000\n"
                "\n"
                "[hmmm]\n"
                "poi_poi = 1.300000\n"
                "\n");

    TEST_EQUAL(object.toString(), compare);
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
    std::string errorMessage = "";

    object.parse(getTestString(), errorMessage);

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
    TEST_EQUAL(outputStringObjects, compare);


    // negative test
    const std::string badString(
                "[DEFAULT]\n"
                "asdf = asdf.asdf\n"
                "id = 550e8400-e29b-11d4-a716-446655440000\n"
                "x = 2\n"
                "\n"
                "(hmmm]\n"
                "poi_poi = 1.300000\n"
                "\n");
    bool result = object.parse(badString, errorMessage);
    TEST_EQUAL(result, false);

    const std::string compareError("ERROR while parsing ini-formated string \n"
                                   "parser-message: syntax error \n"
                                   "line-number: 6 \n"
                                   "position in line: 6 \n"
                                   "broken part in string: \"]\" \n");
    TEST_EQUAL(errorMessage, compareError);
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
}  // namespace Kitsunemimi


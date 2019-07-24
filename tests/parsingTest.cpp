/**
 *  @file    parsingTest.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "parsingTest.h"
#include <libKitsuneIni.h>

using namespace Kitsune::Json;

namespace Kitsune
{
namespace Ini
{

ParsingTest::ParsingTest() : Kitsune::CommonTest("ParsingTest")
{
    initTestCase();
    parserPositiveTest();
    cleanupTestCase();
}

void ParsingTest::initTestCase()
{
}

void ParsingTest::parserPositiveTest()
{
    std::string input("[DEFAULT]\n"
                      "x=2\n"
                      "asdf=asdfasdf"
                      "\n"
                      "[hmmm]\n"
                      "poi=1.3"
                      "\n");


    IniObject object;
    pair<std::string, bool> result = object.parse(input);
    UNITTEST(result.second, true);

    JsonItem* item1 = object.get("DEFAULT", "x");
    std::string get1 = item1->print();
    UNITTEST(get1, "2");

    JsonItem* item2 = object.get("hmmm", "poi");
    std::string get2 = item2->print();
    UNITTEST(get2, "1.300000");

    std::string outputStringObjects = object.print();
    std::string compareObjects("[DEFAULT]\n"
                               "asdf = \"asdfasdf\"\n"
                               "x = 2\n"
                               "\n"
                               "[hmmm]\n"
                               "poi = 1.300000\n"
                               "\n");
    UNITTEST(outputStringObjects, compareObjects);
}

void ParsingTest::cleanupTestCase()
{
}

}  // namespace Ini
}  // namespace Kitsune


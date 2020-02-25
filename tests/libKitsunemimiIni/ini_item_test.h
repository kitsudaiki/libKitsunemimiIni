/**
 *  @file    ini_item_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef PARSERTEST_H
#define PARSERTEST_H

#include <algorithm>
#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

namespace Kitsunemimi
{
namespace Ini
{
class IniItem_Test
        : public Kitsunemimi::CompareTestHelper
{
public:
    IniItem_Test();

private:
    void parse_test();
    void get_test();
    void set_test();
    void removeGroup_test();
    void removeEntry_test();
    void print_test();

    const std::string getTestString();
};

}  // namespace Ini
}  // namespace Kitsunemimi

#endif // PARSERTEST_H

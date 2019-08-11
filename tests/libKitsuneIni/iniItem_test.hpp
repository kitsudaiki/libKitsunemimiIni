/**
 *  @file    iniItem_test.hpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef PARSERTEST_HPP
#define PARSERTEST_HPP

#include <testing/test.hpp>

namespace Kitsune
{
namespace Ini
{
class IniItem_Test : public Kitsune::Common::Test
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

    std::string getTestString();
};

}  // namespace Ini
}  // namespace Kitsune

#endif // PARSERTEST_HPP

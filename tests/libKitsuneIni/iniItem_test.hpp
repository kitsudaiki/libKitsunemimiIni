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

#include <testing/commonTest.hpp>

namespace Kitsune
{
namespace Ini
{
class IniItem_Test : public Kitsune::CommonTest
{
public:
    IniItem_Test();

private:
    void parse_test();
    void get_test();
    void set_test();
    void print_test();
    void setContent_test();

    std::string getTestString();
};

}  // namespace Ini
}  // namespace Kitsune

#endif // PARSERTEST_HPP

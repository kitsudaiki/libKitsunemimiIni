/**
 *  @file    parsingTest.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef PARSERTEST_H
#define PARSERTEST_H

#include <testing/commonTest.hpp>

namespace Kitsune
{
namespace Ini
{
class ParsingTest : public Kitsune::CommonTest
{
public:
    ParsingTest();

private:
    void initTestCase();
    void parserPositiveTest();
    void cleanupTestCase();
};

}  // namespace Ini
}  // namespace Kitsune

#endif // PARSERTEST_H

/**
 *  @file    iniparser.y
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

%skeleton "lalr1.cc"

%defines

//requires 3.2 to avoid the creation of the stack.hh
%require "3.0.4"
%define parser_class_name {IniParser}

%define api.prefix {ini}
%define api.namespace {Kitsune::Ini}
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires
{
#include <string>
#include <map>
#include <utility>
#include <iostream>
#include <vector>
#include <jsonItems.hpp>

namespace Kitsune
{
namespace Ini
{

class IniParserInterface;
using namespace Kitsune::Json;

}  // namespace Ini
}  // namespace Kitsune
}

// The parsing context.
%param { Kitsune::Ini::IniParserInterface& driver }

%locations

%code
{
#include <ini_parsing/iniParserInterface.hpp>
# undef YY_DECL
# define YY_DECL \
    Kitsune::Ini::IniParser::symbol_type inilex (Kitsune::Ini::IniParserInterface& driver)
YY_DECL;
}

// Token
%define api.token.prefix {Ini_}
%token
    END  0  "end of file"
    LINEBREAK "lbreak"
    EQUAL "="
    BRACKOPEN "["
    BRACKCLOSE "]"
    COMMA ","
;


%token <std::string> IDENTIFIER "identifier"
%token <std::string> STRING "string"
%token <int> NUMBER "number"
%token <float> FLOAT "float"

%type <JsonObject*> grouplist
%type <std::string> groupheader
%type <JsonObject*> itemlist
%type <JsonItem*> itemValue
%type <JsonItem*> identifierlist

%%
%start startpoint;


startpoint:
    grouplist
    {
        driver.setOutput($1);
    }

grouplist:
    grouplist groupheader linebreaks itemlist
    {
        $1->insert($2, $4);
        $$ = $1;
    }
|
    groupheader linebreaks itemlist
    {
        JsonObject* newMap = new JsonObject();
        newMap->insert($1, $3);
        $$ = newMap;
    }

groupheader:
    "[" "identifier" "]"
    {
        $$ = $2;
    }

itemlist:
    itemlist "identifier" "=" itemValue linebreaks
    {
        $1->insert($2, $4);
        $$ = $1;
    }
|
    "identifier" "=" itemValue linebreaks
    {
        JsonObject* newMap = new JsonObject();
        newMap->insert($1, $3);
        $$ = newMap;
    }

itemValue:
    "identifier"
    {
        $$ = new JsonValue($1);
    }
|
    identifierlist
    {
        $$ = $1;
    }
|
    "string"
    {
        $$ = new JsonValue($1);
    }
|
    "number"
    {
        $$ = new JsonValue($1);
    }
|
    "float"
    {
        $$ = new JsonValue($1);
    }


identifierlist:
    identifierlist "," "identifier"
    {
        JsonArray* array = dynamic_cast<JsonArray*>($1);
        array->append(new JsonValue($3));
        $$ = $1;
    }
|
    "identifier"
    {
        JsonArray* tempItem = new JsonArray();
        tempItem->append(new JsonValue($1));
        $$ = tempItem;
    }


linebreaks:
   linebreaks "lbreak"
|
   "lbreak"

%%

void Kitsune::Ini::IniParser::error(const Kitsune::Ini::location& location,
                                    const std::string& message)
{
    driver.error(location, message);
}

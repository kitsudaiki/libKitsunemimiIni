%{ /* -*- C++ -*-*/
/**
 *  @file    ini_lexer.l
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
*/

# include <cerrno>
# include <climits>
# include <cstdlib>
# include <string>
# include <ini_parsing/ini_parser_interface.h>
# include <ini_parser.h>

# undef yywrap
# define yywrap() 1

// The location of the current token.
# ifdef YY_DECL
# undef YY_DECL
# endif
# define YY_DECL \
    Kitsunemimi::Ini::IniParser::symbol_type inilex (Kitsunemimi::Ini::IniParserInterface& driver)
YY_DECL;

Kitsunemimi::Ini::location iniloc;
%}


%option noyywrap nounput batch debug yylineno prefix="ini"
id    [%\-+\/@.:a-zA-Z_0-9]*
long   -?([0-9]+)
blank [ \t]

%{
    # define YY_USER_ACTION  iniloc.columns (yyleng);
%}

%%

%{
    iniloc.step();
%}


{blank}+    if(Kitsunemimi::Ini::IniParserInterface::m_outsideComment) { iniloc.step();  } else { return Kitsunemimi::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }
[\n]        {iniloc.lines(1); return Kitsunemimi::Ini::IniParser::make_LINEBREAK (iniloc); }
"="         if(Kitsunemimi::Ini::IniParserInterface::m_outsideComment) { return Kitsunemimi::Ini::IniParser::make_EQUAL (iniloc); } else { return Kitsunemimi::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }
"["         if(Kitsunemimi::Ini::IniParserInterface::m_outsideComment) { return Kitsunemimi::Ini::IniParser::make_BRACKOPEN (iniloc); } else { return Kitsunemimi::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }
"]"         if(Kitsunemimi::Ini::IniParserInterface::m_outsideComment) { return Kitsunemimi::Ini::IniParser::make_BRACKCLOSE (iniloc); } else { return Kitsunemimi::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }
","         if(Kitsunemimi::Ini::IniParserInterface::m_outsideComment) { return Kitsunemimi::Ini::IniParser::make_COMMA (iniloc); } else { return Kitsunemimi::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }
"#"         if(Kitsunemimi::Ini::IniParserInterface::m_outsideComment) { return Kitsunemimi::Ini::IniParser::make_COMMENT (iniloc); } else { return Kitsunemimi::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }
\"(\\.|[^"\\])*\" {
            if(Kitsunemimi::Ini::IniParserInterface::m_outsideComment) { return Kitsunemimi::Ini::IniParser::make_STRING(yytext, iniloc); } else { return Kitsunemimi::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }
}


{long}      {
    errno = 0;
    long length = strtol(yytext, NULL, 10);
    if (!(LONG_MIN <= length
        && length <= LONG_MAX
        && errno != ERANGE))
    {
        driver.error(iniloc, "integer is out of range");
    }
    if(Kitsunemimi::Ini::IniParserInterface::m_outsideComment) { return Kitsunemimi::Ini::IniParser::make_NUMBER (length, iniloc); } else { return Kitsunemimi::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }
}

{long}+"."{long}*       {
    double value = strtod( yytext , NULL );
    if(Kitsunemimi::Ini::IniParserInterface::m_outsideComment) { return Kitsunemimi::Ini::IniParser::make_FLOAT(value, iniloc); } else { return Kitsunemimi::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }
}

{id} if(Kitsunemimi::Ini::IniParserInterface::m_outsideComment) { return Kitsunemimi::Ini::IniParser::make_IDENTIFIER(yytext, iniloc); } else { return Kitsunemimi::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }


[a-zA-Z_0-9|\-|.]* {
    if(Kitsunemimi::Ini::IniParserInterface::m_outsideComment) { return Kitsunemimi::Ini::IniParser::make_STRING_PLN(yytext, iniloc); } else { return Kitsunemimi::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }
}

.          if(Kitsunemimi::Ini::IniParserInterface::m_outsideComment) { driver.error(iniloc, "invalid character"); } else { return Kitsunemimi::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }
<<EOF>>    return Kitsunemimi::Ini::IniParser::make_END(iniloc);

%%


void Kitsunemimi::Ini::IniParserInterface::scan_begin(const std::string &inputString)
{
    Kitsunemimi::Ini::location newLoc;
    iniloc = newLoc;
    yy_flex_debug = m_traceParsing;
    yy_scan_string(inputString.c_str());
}

void Kitsunemimi::Ini::IniParserInterface::scan_end()
{
    yy_delete_buffer(YY_CURRENT_BUFFER);
}

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
    Kitsune::Ini::IniParser::symbol_type inilex (Kitsune::Ini::IniParserInterface& driver)
YY_DECL;

Kitsune::Ini::location iniloc;
%}


%option noyywrap nounput batch debug yylineno prefix="ini"

id    [a-zA-Z_0-9]*
int   -?([0-9]+)
blank [ \t]

%{
    # define YY_USER_ACTION  iniloc.columns (yyleng);
%}

%%

%{
    iniloc.step();
%}


{blank}+    if(Kitsune::Ini::IniParserInterface::m_outsideComment) { iniloc.step();  } else { return Kitsune::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }
[\n]        {iniloc.lines(1); return Kitsune::Ini::IniParser::make_LINEBREAK (iniloc); }
"="         if(Kitsune::Ini::IniParserInterface::m_outsideComment) { return Kitsune::Ini::IniParser::make_EQUAL (iniloc); } else { return Kitsune::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }
"["         if(Kitsune::Ini::IniParserInterface::m_outsideComment) { return Kitsune::Ini::IniParser::make_BRACKOPEN (iniloc); } else { return Kitsune::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }
"]"         if(Kitsune::Ini::IniParserInterface::m_outsideComment) { return Kitsune::Ini::IniParser::make_BRACKCLOSE (iniloc); } else { return Kitsune::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }
","         if(Kitsune::Ini::IniParserInterface::m_outsideComment) { return Kitsune::Ini::IniParser::make_COMMA (iniloc); } else { return Kitsune::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }
"#"         if(Kitsune::Ini::IniParserInterface::m_outsideComment) { return Kitsune::Ini::IniParser::make_COMMENT (iniloc); } else { return Kitsune::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }
\"(\\.|[^"\\])*\" {
            if(Kitsune::Ini::IniParserInterface::m_outsideComment) { return Kitsune::Ini::IniParser::make_STRING(yytext, iniloc); } else { return Kitsune::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }
}


{int}      {
    errno = 0;
    long length = strtol(yytext, NULL, 10);
    if (!(INT_MIN <= length
        && length <= INT_MAX
        && errno != ERANGE))
    {
        driver.error(iniloc, "integer is out of range");
    }
    if(Kitsune::Ini::IniParserInterface::m_outsideComment) { return Kitsune::Ini::IniParser::make_NUMBER (length, iniloc); } else { return Kitsune::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }
}

{int}+"."{int}*	{
    float value = atof( yytext );
    if(Kitsune::Ini::IniParserInterface::m_outsideComment) { return Kitsune::Ini::IniParser::make_FLOAT(value, iniloc); } else { return Kitsune::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }
}

{id} if(Kitsune::Ini::IniParserInterface::m_outsideComment) { return Kitsune::Ini::IniParser::make_IDENTIFIER(yytext, iniloc); } else { return Kitsune::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }


[a-zA-Z_0-9|\-|.]* {
    if(Kitsune::Ini::IniParserInterface::m_outsideComment) { return Kitsune::Ini::IniParser::make_STRING_PLN(yytext, iniloc); } else { return Kitsune::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }
}

.          if(Kitsune::Ini::IniParserInterface::m_outsideComment) { driver.error(iniloc, "invalid character"); } else { return Kitsune::Ini::IniParser::make_DEFAULTRULE(yytext, iniloc); }
<<EOF>>    return Kitsune::Ini::IniParser::make_END(iniloc);

%%


void Kitsune::Ini::IniParserInterface::scan_begin(const std::string &inputString)
{
    Kitsune::Ini::location newLoc;
    iniloc = newLoc;
    yy_flex_debug = m_traceParsing;
    yy_scan_string(inputString.c_str());
}

void Kitsune::Ini::IniParserInterface::scan_end()
{
    yy_delete_buffer(YY_CURRENT_BUFFER);
}



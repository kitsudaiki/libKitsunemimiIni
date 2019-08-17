%{ /* -*- C++ -*- */
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

id    [a-zA-Z][a-zA-Z_0-9]*
int   -?([0-9]+)
blank [ \t]

%{
    # define YY_USER_ACTION  iniloc.columns (yyleng);
%}

%%

%{
    iniloc.step();
%}

{blank}+    iniloc.step();
[\n]        return Kitsune::Ini::IniParser::make_LINEBREAK (iniloc);
"="         return Kitsune::Ini::IniParser::make_EQUAL (iniloc);
"["         return Kitsune::Ini::IniParser::make_BRACKOPEN (iniloc);
"]"         return Kitsune::Ini::IniParser::make_BRACKCLOSE (iniloc);
","         return Kitsune::Ini::IniParser::make_COMMA (iniloc);

#(\\.|[^"\\])*\n {
    iniloc.step();
}

\"(\\.|[^"\\])*\" {
    return Kitsune::Ini::IniParser::make_STRING(yytext, iniloc);
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
    return Kitsune::Ini::IniParser::make_NUMBER (length, iniloc);
}

{int}+"."{int}*	{
    float value = atof( yytext );
    return Kitsune::Ini::IniParser::make_FLOAT(value, iniloc);
}

{id}       return Kitsune::Ini::IniParser::make_IDENTIFIER(yytext, iniloc);
.          driver.error(iniloc, "invalid character");
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



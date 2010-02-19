
/* 
   EVCD Lexer
*/

%{
#include <string>

using namespace std;
#define YYSTYPE string

#include "evcd_yacc.hpp"
#include "scanner.h"

#include <stdio.h>
#include <stdlib.h>    
#include <string.h>
#include <iostream>
#include <fstream>

typedef evcd::Parser::token      token;
typedef evcd::Parser::token_type token_type;

%}

%option noyywrap batch debug
%option c++
%option stack
%option yylineno
/*%option noyywrap nounput batch debug*/
/*%option C++ noyywrap nounput batch debug*/
%option prefix="Evcd"
%{
#define YY_USER_ACTION  *yylval = std::string(yytext, yyleng); \
	                    yylloc->columns(yyleng);
%}
%s ALIAS
%x SIMULATION

/**************************************/
/*      Header Directives             */
/**************************************/
END_KYWD            "$end"
COMMENT_KYWD        "$comment"
DATE_KYWD           "$date"
ENDDEFINITIONS_KYWD "$enddefinitions"
SCOPE_KYWD          "$scope"
TIMESCALE_KYWD      "$timescale"
UPSCOPE_KYWD        "$upscope"
VAR_KYWD            "$var"
VERSION_KYWD        "$version"
VCDCLOSE_KYWD       "$vcdclose"
/**************************************/
/*      Simulation Directives         */
/**************************************/
DUMPALL_KYWD        "$dumpall"
DUMPOFF_KYWD        "$dumpoff"
DUMPON_KYWD         "$dumpon"
DUMPVARS_KYWD       "$dumpvars"
DUMPPORTS_KYWD      "$dumpports"
/**************************************/
/*      Keywords                      */
/**************************************/

EVENT_KYWD          "event"
INTEGER_KYWD        "integer"
PARAMETER_KYWD      "parameter"
REAL_KYWD           "real"
REG_KYWD            "reg"
SUPPLY0_KYWD        "supply0"
SUPPLY1_KYWD        "supply1"
TIME_KYWD           "time"
TRI_KYWD            "tri"
TRIAND_KYWD         "triand"
TRIOR_KYWD          "trior"
TRIREG_KYWD         "trireg"
TRI0_KYWD           "tri0"
TRI1_KYWD           "tri1"
WAND_KYWD           "wand"
WIRE_KYWD           "wire"
WOR_KYWD            "wor"
MODULE_KYWD         "module"
TASK_KYWD           "task"
FUNCTION_KYWD       "function"
BEGIN_KYWD          "begin"
FORK_KYWD           "fork"

INOUT_KYWD          "inout"
INPUT_KYWD          "input"
OUTPUT_KYWD         "output"
PORT_KYWD           "port"

/**************************************/
/*      Tokens                        */
/**************************************/
hash                    "#"
lbracket                "["
rbracket                "]"
langular                "<"
rangular                ">"
colon                   ":"
alphanum                [a-zA-Z0-9._]
digit                   [0-9]
dot                     "."
extended                [a-zA-Z!#%&()*+'-.,\/\\:";<>=?@^_{}|~`0-9]
letter                  [a-zA-Z_]
letter_or_dot           [a-zA-Z_.]
digit_or_dot            [0-9.]
decimal                 {digit_or_dot}+{digit}*
integer                 {digit}+
net_name                {letter}{extended}*
identifier              {letter}+{alphanum}*
identifier_code         [\[\]A-Za-z!"#\$%&()*+,-.0123456789:;<=>@\\\/\^`{}~'?_|]
simulation_time         [#]{integer}
scalar_change           [p][UuDdNZLlHhTX01?FfAaBbCc]
vector_change           [BbRr][xX01]+
vector_change_2         [p][UuDdNZLlHhTX01?FfAaBbCc][UuDdNZLlHhTX01?FfAaBbCc]+


%%
%{
	yylloc->step();
%}

{lbracket}                          {                       return(token::LBRACKET_TOK);        }
{rbracket}                          {                       return(token::RBRACKET_TOK);        }
{colon}                             {                       return(token::COLON_TOK);           }
<INITIAL,SIMULATION>{END_KYWD}      {                       return(token::END_TOK);             }
<ALIAS>{END_KYWD}                   {     BEGIN(prevState); return(token::END_TOK); }
{REG_KYWD}                          {                       return(token::REG_TOK);             }
{SCOPE_KYWD}                        {                       return(token::SCOPE_TOK);           }
{VAR_KYWD}                          { prevState = YY_START;
                                              BEGIN(ALIAS); return(token::VAR_TOK);             }
                                                                                      
{MODULE_KYWD}                       {                       return(token::MODULE_TOK);          }
{TASK_KYWD}                         {                       return(token::TASK_TOK);            }
{FUNCTION_KYWD}                     {                       return(token::FUNCTION_TOK);        }
{BEGIN_KYWD}                        {                       return(token::BEGIN_TOK);           }
{FORK_KYWD}                         {                       return(token::FORK_TOK);            }
{INOUT_KYWD}                        {                       return(token::INOUT_TOK);           }
{INPUT_KYWD}                        {                       return(token::INPUT_TOK);           }
{OUTPUT_KYWD}                       {                       return(token::OUTPUT_TOK);          }
{PORT_KYWD}                         {                       return(token::PORT_TOK);            }
                                                                                      
{DATE_KYWD}                         {     untilEnd(yylval, yylloc); return(token::DATE_TOK);            }
{ENDDEFINITIONS_KYWD}               {    BEGIN(SIMULATION); return(token::ENDDEFINITIONS_TOK);  }
{TIMESCALE_KYWD}                    {                       return(token::TIMESCALE_TOK);       }
{UPSCOPE_KYWD}                      {                       return(token::UPSCOPE_TOK);         }
{VCDCLOSE_KYWD}                     {                       return(token::VCDCLOSE_TOK);        }
{VERSION_KYWD}                      {     untilEnd(yylval, yylloc); return(token::VERSION_TOK);         }
<INITIAL>{COMMENT_KYWD}             {      comment(yylval, yylloc); return(token::DEC_COMMENT_TOK);     }
<SIMULATION>{COMMENT_KYWD}          {      comment(yylval, yylloc); return(token::SIM_COMMENT_TOK);     }
                                    
<SIMULATION>{DUMPPORTS_KYWD}        {                       return(token::DUMPPORTS_TOK);       }
                                                                                
<INITIAL,ALIAS,SIMULATION>{integer} {                       return(token::INTEGER_TOK); }
{identifier}                        {                       return(token::IDENTIFIER_TOK);      }
<ALIAS>{identifier_code}+           {     BEGIN(prevState); return(procIdCode());               }
<SIMULATION>{simulation_time}       {                       return(token::SIMULATION_TIME_TOK); }
<SIMULATION>{scalar_change}         { prevState = YY_START;
                                              BEGIN(ALIAS); return(token::SCALAR_CHANGE_TOK);   }
<SIMULATION>{vector_change}         { prevState = YY_START; 
                                              BEGIN(ALIAS); return(token::VECTOR_CHANGE_TOK);   }
<SIMULATION>{vector_change_2}       { prevState = YY_START;
                                              BEGIN(ALIAS); return(token::VECTOR_CHANGE_2_TOK);   }

{langular}                          {                       return(token::LANGULAR_TOK);        }
{rangular}                          {                       return(token::RANGULAR_TOK);        }

<INITIAL,SIMULATION>[ \t]+          {  }
<INITIAL,SIMULATION>[\n]            { yylloc->lines(yyleng); yylloc->step();                    }
<ALIAS>[\n]+                        { yylloc->lines(yyleng); yylloc->step();  BEGIN(prevState); }

<INITIAL,SIMULATION>.               {                       return(token::LEX_ERROR_TOK);       }

%%

namespace evcd {

    Scanner::Scanner(std::istream* in, std::ostream* out)
        : EvcdFlexLexer(in, out)
    {
    }

    Scanner::~Scanner()
    {
    }

    void Scanner::set_debug(bool b)
    {
        yy_flex_debug = b;
    }

    inline void Scanner::comment(string* lval, location *yylloc) {
        register int c1,c2,c3,c4;
        // input needs to be renamed to by yyinput in c_plus_plus
        string comment;
        while ((c1 = yyinput()))
        {
            comment += c1;
            if (c1 == '$')
            {
                if ((c2 = yyinput()) == 'e') {
                    comment += c2;

                    if ((c3 = yyinput()) == 'n') {
                        comment += c3;
                        if ((c4 = yyinput()) == 'd') {
                            comment += c4;
                            break;
                        }
                        else
                            yyunput( c4, (yytext));
                    }
                    else
                        yyunput( c3, (yytext));
                }
                else
                    yyunput( c2, (yytext));
            }

            if (c1 == '\n')
                yylloc->lines(1);
        }

        comment.erase( comment.size() - 4, 4);

        *lval = comment;
        strcpy(yytext, comment.c_str());

    }

    void Scanner::untilEnd(string* lval, location *yylloc) {
        register int c1,c2,c3,c4;
        // input needs to be renamed to by yyinput in c_plus_plus
        string comment;
    /*    comment = yytext;*/
        string prefix = yytext;
        while ((c1 = yyinput()))
        {
            comment += c1;
            if (c1 == '$')
            {
                if ((c2 = yyinput()) == 'e') {
                    comment += c2;

                    if ((c3 = yyinput()) == 'n') {
                        comment += c3;
                        if ((c4 = yyinput()) == 'd') {
                            comment += c4;
                            break;
                        }
                        else
                            yyunput( c4, (yytext));
                    }
                    else
                        yyunput( c3, (yytext));
                }
                else
                    yyunput( c2, (yytext));
            }
            if (c1 == '\n')
                yylloc->lines(1);
        }

        comment.erase( comment.size() - 4, 4);
        *lval = comment;
        strcpy(yytext, comment.c_str());

    }

    int Scanner::procIdCode() {
        int  intval;
        int  i            = 0;
        bool isIdentifier = 1;
        intval = (int) (yytext[0] - '\0');
        if(((intval >= 65) && (intval <=90)) || 
                ((intval >= 97) && (intval <= 122)) ||
                (yytext[0] == '.') ||
                (yytext[0] == '_')) {
        }
        else {
            isIdentifier = 0;
        }
        if(yytext[1] != '\0') {
            for (i = 1; yytext[i] != '\0'; i++) {
                intval = (int) (yytext[0] - '\0');
                if(((intval >= 65) && (intval <=90)) || 
                        ((intval >= 97) && (intval <= 122)) ||
                        ((intval >= 48) && (intval <= 57)) ||
                        (yytext[i] == '.') ||
                        (yytext[i] == '_')) {
                }
                else {
                    isIdentifier = 0;
                }
            }
        }
        if(isIdentifier) {
            return(token::IDENTIFIER_TOK);
        }
        else {
            return(token::IDENTIFIER_CODE_TOK);
        }

    }

    void Scanner::LexerOutput( const char* buf, int size ) {
        // Purposely do nothing here
    }

}

/* This implementation of EvcdFlexLexer::yylex() is required to fill the
 * vtable of the class EvcdFlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the Scanner class instead. */

#ifdef yylex
#undef yylex
#endif

int EvcdFlexLexer::yylex()
{
    std::cerr << "in " << __PRETTY_FUNCTION__ << " !" << std::endl;
    return 0;
}



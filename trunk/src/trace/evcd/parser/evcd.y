%{
#include <cstdio>
#include <cstdlib>
#include <string>    
#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace std;
    
#define YYSTYPE string

template <typename T>
T stringToType(string str) {
    T val;
    val = boost::lexical_cast< T, string>(str);
    return val;
}

%}

%require "2.3"
%debug
%defines
%skeleton "lalr1.cc"
%name-prefix="evcd"
%define "parser_class_name" "Parser"
%locations
%initial-action
{
    // initialize the initial location object
	@$.begin.filename = @$.end.filename = &driver.streamname;
};

/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class Driver& driver }
/*%error-verbose*/

%token LBRACKET_TOK RBRACKET_TOK COLON_TOK
%token REG_TOK END_TOK VAR_TOK
%token INOUT_TOK INPUT_TOK OUTPUT_TOK PORT_TOK
%token DATE_TOK TIMESCALE_TOK VERSION_TOK VCDCLOSE_TOK ENDDEFINITIONS_TOK UPSCOPE_TOK SCOPE_TOK
%token DEC_COMMENT_TOK SIM_COMMENT_TOK
%token MODULE_TOK TASK_TOK FUNCTION_TOK BEGIN_TOK FORK_TOK

%token INTEGER_TOK IDENTIFIER_CODE_TOK IDENTIFIER_TOK
%token SIMULATION_TIME_TOK SCALAR_CHANGE_TOK VECTOR_CHANGE_TOK
%token DUMPPORTS_TOK
%token LANGULAR_TOK RANGULAR_TOK
%token LEX_ERROR_TOK

%{
#include "scanner.h"
#include "driver.h"

#undef yylex
#define yylex driver.lexer->lex
%}

%%

evcd_file:
	declaration_statements enddefinitions_statement simulation_statements
	{
		driver.onEOF();
	}
;

simulation_statements:
	simulation_statement
	| simulation_statements simulation_statement
;

simulation_statement:
	SIMULATION_TIME_TOK { driver.onTimestamp( stringToType<unsigned long long>(($1.erase( 0, 1))) ); }
	| value_change
	| dumpports_statement
	| sim_comment_statement
;

dumpports_statement:
	DUMPPORTS_TOK { driver.onDumpportsBegin(); } value_changes END_TOK { driver.onDumpportsEnd(); }
;

value_changes:
	value_change
	| value_changes value_change
;

value_change:
	scalar_value_change
	| vector_value_change
;

scalar_value_change:
	SCALAR_CHANGE_TOK INTEGER_TOK INTEGER_TOK alias
	{
		driver.onScalarChange( $4, ($1.erase( 0, 1)).c_str(), atoi($2.c_str()), atoi($3.c_str()));
	}
;

vector_value_change:
	VECTOR_CHANGE_TOK alias
	{
		driver.onVectorChange( $2, ($1.erase( 0, 1)).c_str());
	}
;

declaration_statements:
	declaration_statement
	| declaration_statements declaration_statement
;

declaration_statement:
	dec_comment_statement
	| date_statement
	| timescale_statement
	| version_statement
	| scope_statement
	| upscope_statement
	| var_statement
;


sim_comment_statement:
	SIM_COMMENT_TOK ;

dec_comment_statement:
	DEC_COMMENT_TOK ;

date_statement:
	DATE_TOK { 
		driver.onDate($1);
	}
;

enddefinitions_statement:
	ENDDEFINITIONS_TOK END_TOK
	{
		driver.onEndDefinitions();
	}
;

/*        if(yylen > 1) {*/
/*            yyval = (yysemantic_stack_[(yylen) - (1)]);*/
/*            for(int i = 2; i <= yylen; i++)*/
/*                (yyval) += " " + (yysemantic_stack_[(yylen) - (i)]);*/
/*        }*/
scope_statement:
	SCOPE_TOK scope_type IDENTIFIER_TOK  END_TOK
    { 
		driver.onScope( $3, $2);
	}
;

scope_type:
	MODULE_TOK 
	| TASK_TOK 
	| FUNCTION_TOK 
	| BEGIN_TOK 
	| FORK_TOK 
;

timescale_statement:
	TIMESCALE_TOK INTEGER_TOK IDENTIFIER_TOK END_TOK
	{ 
		driver.onTimescale( stringToType<unsigned long long>( $2), $3);
	}
;

upscope_statement:
	UPSCOPE_TOK END_TOK
    { 
		driver.onUpScope(); 
	}
;

version_statement:
	VERSION_TOK
    {
		driver.onVersion($1);
	}
;

var_statement:
	// Net
	VAR_TOK var_type var_size alias IDENTIFIER_TOK END_TOK
	{
		driver.onVar( $5, $2, atoi($3.c_str()), $4);
	}
	// Register
	| VAR_TOK var_type var_size alias IDENTIFIER_TOK LBRACKET_TOK INTEGER_TOK COLON_TOK INTEGER_TOK RBRACKET_TOK END_TOK
	{
		driver.onVar( $5, $2, atoi($3.c_str()), $4, atoi($7.c_str()), atoi($9.c_str()));
	}
	// Port
	| VAR_TOK PORT_TOK var_size alias IDENTIFIER_TOK END_TOK
	{
		driver.onVar( $5, $2, atoi($3.c_str()), $4);
	}
	// Task , Empty Port
	| VAR_TOK PORT_TOK var_size alias LANGULAR_TOK INTEGER_TOK RANGULAR_TOK END_TOK
	{
	}
;

alias:
	IDENTIFIER_CODE_TOK
	| IDENTIFIER_TOK
	| INTEGER_TOK
	| COLON_TOK
	| LBRACKET_TOK
	| RBRACKET_TOK
;

var_size:
	INTEGER_TOK
;

var_type:
	REG_TOK
	| INPUT_TOK
	| INOUT_TOK
	| OUTPUT_TOK
;

%%

void evcd::Parser::error(const Parser::location_type& l, const std::string& m)
{
    driver.error(l, m);
}



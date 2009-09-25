
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++

      Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008 Free Software
   Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

// Take the name prefix into account.
#define yylex   evcdlex

/* First part of user declarations.  */

/* Line 311 of lalr1.cc  */
#line 1 "evcd.y"

#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace std;

#define YYSTYPE string

template <typename T>
T stringToType(string str)
{
    T val;
    val = boost::lexical_cast< T, string>(str);
    return val;
}


/* Line 311 of lalr1.cc  */
#line 53 "evcd.y"

#include "scanner.h"
#include "driver.h"

#undef yylex
#define yylex driver.lexer->lex


/* Line 311 of lalr1.cc  */
#line 73 "evcd_yacc.cpp"


#include "evcd_yacc.hpp"

/* User implementation prologue.  */


/* Line 317 of lalr1.cc  */
#line 82 "evcd_yacc.cpp"

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location) \
do {       \
  if (yydebug_)      \
    {       \
      *yycdebug_ << Title << ' ';   \
      yy_symbol_print_ ((Type), (Value), (Location)); \
      *yycdebug_ << std::endl;    \
    }       \
} while (false)

# define YY_REDUCE_PRINT(Rule)  \
do {     \
  if (yydebug_)    \
    yy_reduce_print_ (Rule);  \
} while (false)

# define YY_STACK_PRINT()  \
do {     \
  if (yydebug_)    \
    yystack_print_ ();   \
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define yyerrok  (yyerrstatus_ = 0)
#define yyclearin (yychar = yyempty_)

#define YYACCEPT goto yyacceptlab
#define YYABORT  goto yyabortlab
#define YYERROR  goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


/* Line 380 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

namespace evcd
{

    /* Line 380 of lalr1.cc  */
#line 151 "evcd_yacc.cpp"
#if YYERROR_VERBOSE

    /* Return YYSTR after stripping away unnecessary quotes and
       backslashes, so that it's suitable for yyerror.  The heuristic is
       that double-quoting is unnecessary unless the string contains an
       apostrophe, a comma, or backslash (other than backslash-backslash).
       YYSTR is taken from yytname.  */
    std::string
    Parser::yytnamerr_ (const char *yystr)
    {
        if (*yystr == '"')
        {
            std::string yyr = "";
            char const *yyp = yystr;

            for (;;)
                switch (*++yyp)
                {
                case '\'':
                case ',':
                    goto do_not_strip_quotes;

                case '\\':
                    if (*++yyp != '\\')
                        goto do_not_strip_quotes;
                    /* Fall through.  */
                default:
                    yyr += *yyp;
                    break;

                case '"':
                    return yyr;
                }
do_not_strip_quotes:
            ;
        }

        return yystr;
    }

#endif

    /// Build a parser object.
    Parser::Parser (class Driver& driver_yyarg)
            :
#if YYDEBUG
            yydebug_ (false),
            yycdebug_ (&std::cerr),
#endif
            driver (driver_yyarg)
    {
    }

    Parser::~Parser ()
    {
    }

#if YYDEBUG
    /*--------------------------------.
    | Print this symbol on YYOUTPUT.  |
    `--------------------------------*/

    inline void
    Parser::yy_symbol_value_print_ (int yytype,
                                    const semantic_type* yyvaluep, const location_type* yylocationp)
    {
        YYUSE (yylocationp);
        YYUSE (yyvaluep);
        switch (yytype)
        {
        default:
            break;
        }
    }


    void
    Parser::yy_symbol_print_ (int yytype,
                              const semantic_type* yyvaluep, const location_type* yylocationp)
    {
        *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << *yylocationp << ": ";
        yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
        *yycdebug_ << ')';
    }
#endif

    void
    Parser::yydestruct_ (const char* yymsg,
                         int yytype, semantic_type* yyvaluep, location_type* yylocationp)
    {
        YYUSE (yylocationp);
        YYUSE (yymsg);
        YYUSE (yyvaluep);

        YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

        switch (yytype)
        {

        default:
            break;
        }
    }

    void
    Parser::yypop_ (unsigned int n)
    {
        yystate_stack_.pop (n);
        yysemantic_stack_.pop (n);
        yylocation_stack_.pop (n);
    }

#if YYDEBUG
    std::ostream&
    Parser::debug_stream () const
    {
        return *yycdebug_;
    }

    void
    Parser::set_debug_stream (std::ostream& o)
    {
        yycdebug_ = &o;
    }


    Parser::debug_level_type
    Parser::debug_level () const
    {
        return yydebug_;
    }

    void
    Parser::set_debug_level (debug_level_type l)
    {
        yydebug_ = l;
    }
#endif

    int
    Parser::parse ()
    {
        /// Lookahead and lookahead in internal form.
        int yychar = yyempty_;
        int yytoken = 0;

        /* State.  */
        int yyn;
        int yylen = 0;
        int yystate = 0;

        /* Error handling.  */
        int yynerrs_ = 0;
        int yyerrstatus_ = 0;

        /// Semantic value of the lookahead.
        semantic_type yylval;
        /// Location of the lookahead.
        location_type yylloc;
        /// The locations where the error started and ended.
        location_type yyerror_range[2];

        /// $$.
        semantic_type yyval;
        /// @$.
        location_type yyloc;

        int yyresult;

        YYCDEBUG << "Starting parse" << std::endl;


        /* User initialization code.  */

        /* Line 553 of lalr1.cc  */
#line 29 "evcd.y"
        {
            // initialize the initial location object
            yylloc.begin.filename = yylloc.end.filename = &driver.streamname;
        }

        /* Line 553 of lalr1.cc  */
#line 335 "evcd_yacc.cpp"

        /* Initialize the stacks.  The initial state will be pushed in
           yynewstate, since the latter expects the semantical and the
           location values to have been already stored, initialize these
           stacks with a primary value.  */
        yystate_stack_ = state_stack_type (0);
        yysemantic_stack_ = semantic_stack_type (0);
        yylocation_stack_ = location_stack_type (0);
        yysemantic_stack_.push (yylval);
        yylocation_stack_.push (yylloc);

        /* New state.  */
yynewstate:
        yystate_stack_.push (yystate);
        YYCDEBUG << "Entering state " << yystate << std::endl;

        /* Accept?  */
        if (yystate == yyfinal_)
            goto yyacceptlab;

        goto yybackup;

        /* Backup.  */
yybackup:

        /* Try to take a decision without lookahead.  */
        yyn = yypact_[yystate];
        if (yyn == yypact_ninf_)
            goto yydefault;

        /* Read a lookahead token.  */
        if (yychar == yyempty_)
        {
            YYCDEBUG << "Reading a token: ";
            yychar = yylex (&yylval, &yylloc);
        }


        /* Convert token to internal form.  */
        if (yychar <= yyeof_)
        {
            yychar = yytoken = yyeof_;
            YYCDEBUG << "Now at end of input." << std::endl;
        }
        else
        {
            yytoken = yytranslate_ (yychar);
            YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
        }

        /* If the proper action on seeing token YYTOKEN is to reduce or to
           detect an error, take that action.  */
        yyn += yytoken;
        if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
            goto yydefault;

        /* Reduce or error.  */
        yyn = yytable_[yyn];
        if (yyn <= 0)
        {
            if (yyn == 0 || yyn == yytable_ninf_)
                goto yyerrlab;
            yyn = -yyn;
            goto yyreduce;
        }

        /* Shift the lookahead token.  */
        YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

        /* Discard the token being shifted.  */
        yychar = yyempty_;

        yysemantic_stack_.push (yylval);
        yylocation_stack_.push (yylloc);

        /* Count tokens shifted since error; after three, turn off error
           status.  */
        if (yyerrstatus_)
            --yyerrstatus_;

        yystate = yyn;
        goto yynewstate;

        /*-----------------------------------------------------------.
        | yydefault -- do the default action for the current state.  |
        `-----------------------------------------------------------*/
yydefault:
        yyn = yydefact_[yystate];
        if (yyn == 0)
            goto yyerrlab;
        goto yyreduce;

        /*-----------------------------.
        | yyreduce -- Do a reduction.  |
        `-----------------------------*/
yyreduce:
        yylen = yyr2_[yyn];
        /* If YYLEN is nonzero, implement the default value of the action:
           `$$ = $1'.  Otherwise, use the top of the stack.

           Otherwise, the following line sets YYVAL to garbage.
           This behavior is undocumented and Bison
           users should not rely upon it.  */
        if (yylen)
            yyval = yysemantic_stack_[yylen - 1];
        else
            yyval = yysemantic_stack_[0];

        {
            slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
            YYLLOC_DEFAULT (yyloc, slice, yylen);
        }
        YY_REDUCE_PRINT (yyn);
        switch (yyn)
        {
        case 2:

            /* Line 678 of lalr1.cc  */
#line 65 "evcd.y"
            {
                driver.onEOF();
            }
            break;

        case 5:

            /* Line 678 of lalr1.cc  */
#line 76 "evcd.y"
            {
                driver.onTimestamp( stringToType<unsigned long long>(((yysemantic_stack_[(1) - (1)]).erase( 0, 1))) );
            }
            break;

        case 9:

            /* Line 678 of lalr1.cc  */
#line 83 "evcd.y"
            {
                driver.onDumpportsBegin();
            }
            break;

        case 10:

            /* Line 678 of lalr1.cc  */
#line 83 "evcd.y"
            {
                driver.onDumpportsEnd();
            }
            break;

        case 15:

            /* Line 678 of lalr1.cc  */
#line 98 "evcd.y"
            {
                driver.onScalarChange( (yysemantic_stack_[(4) - (4)]), ((yysemantic_stack_[(4) - (1)]).erase( 0, 1)).c_str(), atoi((yysemantic_stack_[(4) - (2)]).c_str()), atoi((yysemantic_stack_[(4) - (3)]).c_str()));
            }
            break;

        case 16:

            /* Line 678 of lalr1.cc  */
#line 105 "evcd.y"
            {
                driver.onVectorChange( (yysemantic_stack_[(2) - (2)]), ((yysemantic_stack_[(2) - (1)]).erase( 0, 1)).c_str());
            }
            break;

        case 28:

            /* Line 678 of lalr1.cc  */
#line 133 "evcd.y"
            {
                driver.onDate((yysemantic_stack_[(1) - (1)]));
            }
            break;

        case 29:

            /* Line 678 of lalr1.cc  */
#line 140 "evcd.y"
            {
                driver.onEndDefinitions();
            }
            break;

        case 30:

            /* Line 678 of lalr1.cc  */
#line 152 "evcd.y"
            {
                driver.onScope( (yysemantic_stack_[(4) - (3)]), (yysemantic_stack_[(4) - (2)]));
            }
            break;

        case 36:

            /* Line 678 of lalr1.cc  */
#line 167 "evcd.y"
            {
                driver.onTimescale( stringToType<unsigned long long>( (yysemantic_stack_[(4) - (2)])), (yysemantic_stack_[(4) - (3)]));
            }
            break;

        case 37:

            /* Line 678 of lalr1.cc  */
#line 174 "evcd.y"
            {
                driver.onUpScope();
            }
            break;

        case 38:

            /* Line 678 of lalr1.cc  */
#line 181 "evcd.y"
            {
                driver.onVersion((yysemantic_stack_[(1) - (1)]));
            }
            break;

        case 39:

            /* Line 678 of lalr1.cc  */
#line 189 "evcd.y"
            {
                driver.onVar( (yysemantic_stack_[(6) - (5)]), (yysemantic_stack_[(6) - (2)]), atoi((yysemantic_stack_[(6) - (3)]).c_str()), (yysemantic_stack_[(6) - (4)]));
            }
            break;

        case 40:

            /* Line 678 of lalr1.cc  */
#line 194 "evcd.y"
            {
                driver.onVar( (yysemantic_stack_[(11) - (5)]), (yysemantic_stack_[(11) - (2)]), atoi((yysemantic_stack_[(11) - (3)]).c_str()), (yysemantic_stack_[(11) - (4)]), atoi((yysemantic_stack_[(11) - (7)]).c_str()), atoi((yysemantic_stack_[(11) - (9)]).c_str()));
            }
            break;

        case 41:

            /* Line 678 of lalr1.cc  */
#line 199 "evcd.y"
            {
                driver.onVar( (yysemantic_stack_[(6) - (5)]), (yysemantic_stack_[(6) - (2)]), atoi((yysemantic_stack_[(6) - (3)]).c_str()), (yysemantic_stack_[(6) - (4)]));
            }
            break;

        case 42:

            /* Line 678 of lalr1.cc  */
#line 204 "evcd.y"
            {
            }
            break;



            /* Line 678 of lalr1.cc  */
#line 591 "evcd_yacc.cpp"
        default:
            break;
        }
        YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

        yypop_ (yylen);
        yylen = 0;
        YY_STACK_PRINT ();

        yysemantic_stack_.push (yyval);
        yylocation_stack_.push (yyloc);

        /* Shift the result of the reduction.  */
        yyn = yyr1_[yyn];
        yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
        if (0 <= yystate && yystate <= yylast_
                && yycheck_[yystate] == yystate_stack_[0])
            yystate = yytable_[yystate];
        else
            yystate = yydefgoto_[yyn - yyntokens_];
        goto yynewstate;

        /*------------------------------------.
        | yyerrlab -- here on detecting error |
        `------------------------------------*/
yyerrlab:
        /* If not already recovering from an error, report this error.  */
        if (!yyerrstatus_)
        {
            ++yynerrs_;
            error (yylloc, yysyntax_error_ (yystate));
        }

        yyerror_range[0] = yylloc;
        if (yyerrstatus_ == 3)
        {
            /* If just tried and failed to reuse lookahead token after an
             error, discard it.  */

            if (yychar <= yyeof_)
            {
                /* Return failure if at end of input.  */
                if (yychar == yyeof_)
                    YYABORT;
            }
            else
            {
                yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
                yychar = yyempty_;
            }
        }

        /* Else will try to reuse lookahead token after shifting the error
           token.  */
        goto yyerrlab1;


        /*---------------------------------------------------.
        | yyerrorlab -- error raised explicitly by YYERROR.  |
        `---------------------------------------------------*/
yyerrorlab:

        /* Pacify compilers like GCC when the user code never invokes
           YYERROR and the label yyerrorlab therefore never appears in user
           code.  */
        if (false)
            goto yyerrorlab;

        yyerror_range[0] = yylocation_stack_[yylen - 1];
        /* Do not reclaim the symbols of the rule which action triggered
           this YYERROR.  */
        yypop_ (yylen);
        yylen = 0;
        yystate = yystate_stack_[0];
        goto yyerrlab1;

        /*-------------------------------------------------------------.
        | yyerrlab1 -- common code for both syntax error and YYERROR.  |
        `-------------------------------------------------------------*/
yyerrlab1:
        yyerrstatus_ = 3; /* Each real token shifted decrements this.  */

        for (;;)
        {
            yyn = yypact_[yystate];
            if (yyn != yypact_ninf_)
            {
                yyn += yyterror_;
                if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                    yyn = yytable_[yyn];
                    if (0 < yyn)
                        break;
                }
            }

            /* Pop the current state because it cannot handle the error token.  */
            if (yystate_stack_.height () == 1)
                YYABORT;

            yyerror_range[0] = yylocation_stack_[0];
            yydestruct_ ("Error: popping",
                         yystos_[yystate],
                         &yysemantic_stack_[0], &yylocation_stack_[0]);
            yypop_ ();
            yystate = yystate_stack_[0];
            YY_STACK_PRINT ();
        }

        yyerror_range[1] = yylloc;
        // Using YYLLOC is tempting, but would change the location of
        // the lookahead.  YYLOC is available though.
        YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
        yysemantic_stack_.push (yylval);
        yylocation_stack_.push (yyloc);

        /* Shift the error token.  */
        YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
                         &yysemantic_stack_[0], &yylocation_stack_[0]);

        yystate = yyn;
        goto yynewstate;

        /* Accept.  */
yyacceptlab:
        yyresult = 0;
        goto yyreturn;

        /* Abort.  */
yyabortlab:
        yyresult = 1;
        goto yyreturn;

yyreturn:
        if (yychar != yyempty_)
            yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval, &yylloc);

        /* Do not reclaim the symbols of the rule which action triggered
           this YYABORT or YYACCEPT.  */
        yypop_ (yylen);
        while (yystate_stack_.height () != 1)
        {
            yydestruct_ ("Cleanup: popping",
                         yystos_[yystate_stack_[0]],
                         &yysemantic_stack_[0],
                         &yylocation_stack_[0]);
            yypop_ ();
        }

        return yyresult;
    }

    // Generate an error message.
    std::string
    Parser::yysyntax_error_ (int yystate)
    {
        std::string res;
        YYUSE (yystate);
#if YYERROR_VERBOSE
        int yyn = yypact_[yystate];
        if (yypact_ninf_ < yyn && yyn <= yylast_)
        {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;

            /* Stay within bounds of both yycheck and yytname.  */
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            int count = 0;
            for (int x = yyxbegin; x < yyxend; ++x)
                if (yycheck_[x + yyn] == x && x != yyterror_)
                    ++count;

            // FIXME: This method of building the message is not compatible
            // with internationalization.  It should work like yacc.c does it.
            // That is, first build a string that looks like this:
            // "syntax error, unexpected %s or %s or %s"
            // Then, invoke YY_ on this string.
            // Finally, use the string as a format to output
            // yytname_[tok], etc.
            // Until this gets fixed, this message appears in English only.
            res = "syntax error, unexpected ";
            res += yytnamerr_ (yytname_[tok]);
            if (count < 5)
            {
                count = 0;
                for (int x = yyxbegin; x < yyxend; ++x)
                    if (yycheck_[x + yyn] == x && x != yyterror_)
                    {
                        res += (!count++) ? ", expecting " : " or ";
                        res += yytnamerr_ (yytname_[x]);
                    }
            }
        }
        else
#endif
            res = YY_("syntax error");
        return res;
    }


    /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
       STATE-NUM.  */
    const signed char Parser::yypact_ninf_ = -62;
    const signed char
    Parser::yypact_[] =
    {
        22,    37,   -62,   -18,   -62,     9,    28,   -62,    31,     0,
        -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,
        -62,   -62,    11,    11,    26,   -62,   -62,   -62,   -62,   -62,
        -62,    27,   -62,    25,   -62,    -9,   -62,    -2,    -2,    50,
        51,   -62,   -62,   -62,    32,    -2,   -62,    -9,   -62,   -62,
        -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,
        5,    33,   -62,   -62,    34,   -62,    13,   -62,    53,    36,
        3,    -2,    -3,   -62,   -62,    29,    38,   -62,   -62,   -62,
        -62,    59,    62,   -62,    41,    65,    63,   -62
    };

    /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
       doesn't specify something else to do.  Zero means the default is an
       error.  */
    const unsigned char
    Parser::yydefact_[] =
    {
        0,     0,    28,     0,    38,     0,     0,    27,     0,     0,
        17,    19,    20,    23,    21,    24,    22,    25,    50,    52,
        51,    53,     0,     0,     0,    37,    31,    32,    33,    34,
        35,     0,     1,     0,    18,     0,    49,     0,     0,     0,
        0,    29,    26,     5,     0,     0,     9,     2,     3,     7,
        6,    13,    14,     8,    47,    48,    46,    45,    43,    44,
        0,     0,    36,    30,     0,    16,     0,     4,     0,     0,
        0,     0,     0,    11,    41,     0,     0,    39,    15,    10,
        12,     0,     0,    42,     0,     0,     0,    40
    };

    /* YYPGOTO[NTERM-NUM].  */
    const signed char
    Parser::yypgoto_[] =
    {
        -62,   -62,   -62,    24,   -62,   -62,   -62,   -61,   -62,   -62,
        -62,    64,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,
        -62,   -62,   -38,    49,   -62
    };

    /* YYDEFGOTO[NTERM-NUM].  */
    const signed char
    Parser::yydefgoto_[] =
    {
        -1,     8,    47,    48,    49,    66,    72,    50,    51,    52,
        9,    10,    53,    11,    12,    35,    13,    31,    14,    15,
        16,    17,    60,    37,    23
    };

    /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
       positive, shift that token.  If negative, reduce the rule which
       number is the opposite.  If zero, do what YYDEFACT says.  */
    const signed char Parser::yytable_ninf_ = -1;
    const unsigned char
    Parser::yytable_[] =
    {
        61,    54,    55,    56,    79,    73,    76,    65,     1,    24,
        77,    80,    42,     2,     3,     4,    25,    33,     5,     6,
        7,    43,    44,    45,    46,    57,    58,    59,    44,    45,
        1,    32,    41,    78,    68,     2,     3,     4,    36,    69,
        5,     6,     7,    18,    44,    45,    19,    20,    21,    22,
        26,    27,    28,    29,    30,    39,    40,    62,    63,    64,
        74,    71,    70,    75,    81,    82,    83,    84,    85,    86,
        87,    67,    38,    34
    };

    /* YYCHECK.  */
    const unsigned char
    Parser::yycheck_[] =
    {
        38,     3,     4,     5,     7,    66,     3,    45,     8,    27,
        7,    72,    21,    13,    14,    15,     7,    17,    18,    19,
        20,    30,    31,    32,    33,    27,    28,    29,    31,    32,
        8,     0,     7,    71,    29,    13,    14,    15,    27,    34,
        18,    19,    20,     6,    31,    32,     9,    10,    11,    12,
        22,    23,    24,    25,    26,    29,    29,     7,     7,    27,
        7,    27,    29,    27,    35,    27,     7,     5,    27,     4,
        7,    47,    23,     9
    };

    /* STOS_[STATE-NUM] -- The (internal number of the) accessing
       symbol of state STATE-NUM.  */
    const unsigned char
    Parser::yystos_[] =
    {
        0,     8,    13,    14,    15,    18,    19,    20,    38,    47,
        48,    50,    51,    53,    55,    56,    57,    58,     6,     9,
        10,    11,    12,    61,    27,     7,    22,    23,    24,    25,
        26,    54,     0,    17,    48,    52,    27,    60,    60,    29,
        29,     7,    21,    30,    31,    32,    33,    39,    40,    41,
        44,    45,    46,    49,     3,     4,     5,    27,    28,    29,
        59,    59,     7,     7,    27,    59,    42,    40,    29,    34,
        29,    27,    43,    44,     7,    27,     3,     7,    59,     7,
        44,    35,    27,     7,     5,    27,     4,     7
    };

#if YYDEBUG
    /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
       to YYLEX-NUM.  */
    const unsigned short int
    Parser::yytoken_number_[] =
    {
        0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
        265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
        275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
        285,   286,   287,   288,   289,   290,   291
    };
#endif

    /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
    const unsigned char
    Parser::yyr1_[] =
    {
        0,    37,    38,    39,    39,    40,    40,    40,    40,    42,
        41,    43,    43,    44,    44,    45,    46,    47,    47,    48,
        48,    48,    48,    48,    48,    48,    49,    50,    51,    52,
        53,    54,    54,    54,    54,    54,    55,    56,    57,    58,
        58,    58,    58,    59,    59,    59,    59,    59,    59,    60,
        61,    61,    61,    61
    };

    /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
    const unsigned char
    Parser::yyr2_[] =
    {
        0,     2,     3,     1,     2,     1,     1,     1,     1,     0,
        4,     1,     2,     1,     1,     4,     2,     1,     2,     1,
        1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
        4,     1,     1,     1,     1,     1,     4,     2,     1,     6,
        11,     6,     8,     1,     1,     1,     1,     1,     1,     1,
        1,     1,     1,     1
    };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
    /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
       First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
    const char*
    const Parser::yytname_[] =
    {
        "$end", "error", "$undefined", "LBRACKET_TOK", "RBRACKET_TOK",
        "COLON_TOK", "REG_TOK", "END_TOK", "VAR_TOK", "INOUT_TOK", "INPUT_TOK",
        "OUTPUT_TOK", "PORT_TOK", "DATE_TOK", "TIMESCALE_TOK", "VERSION_TOK",
        "VCDCLOSE_TOK", "ENDDEFINITIONS_TOK", "UPSCOPE_TOK", "SCOPE_TOK",
        "DEC_COMMENT_TOK", "SIM_COMMENT_TOK", "MODULE_TOK", "TASK_TOK",
        "FUNCTION_TOK", "BEGIN_TOK", "FORK_TOK", "INTEGER_TOK",
        "IDENTIFIER_CODE_TOK", "IDENTIFIER_TOK", "SIMULATION_TIME_TOK",
        "SCALAR_CHANGE_TOK", "VECTOR_CHANGE_TOK", "DUMPPORTS_TOK",
        "LANGULAR_TOK", "RANGULAR_TOK", "LEX_ERROR_TOK", "$accept", "evcd_file",
        "simulation_statements", "simulation_statement", "dumpports_statement",
        "$@1", "value_changes", "value_change", "scalar_value_change",
        "vector_value_change", "declaration_statements", "declaration_statement",
        "sim_comment_statement", "dec_comment_statement", "date_statement",
        "enddefinitions_statement", "scope_statement", "scope_type",
        "timescale_statement", "upscope_statement", "version_statement",
        "var_statement", "alias", "var_size", "var_type", 0
    };
#endif

#if YYDEBUG
    /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
    const Parser::rhs_number_type
    Parser::yyrhs_[] =
    {
        38,     0,    -1,    47,    52,    39,    -1,    40,    -1,    39,
        40,    -1,    30,    -1,    44,    -1,    41,    -1,    49,    -1,
        -1,    33,    42,    43,     7,    -1,    44,    -1,    43,    44,
        -1,    45,    -1,    46,    -1,    31,    27,    27,    59,    -1,
        32,    59,    -1,    48,    -1,    47,    48,    -1,    50,    -1,
        51,    -1,    55,    -1,    57,    -1,    53,    -1,    56,    -1,
        58,    -1,    21,    -1,    20,    -1,    13,    -1,    17,     7,
        -1,    19,    54,    29,     7,    -1,    22,    -1,    23,    -1,
        24,    -1,    25,    -1,    26,    -1,    14,    27,    29,     7,
        -1,    18,     7,    -1,    15,    -1,     8,    61,    60,    59,
        29,     7,    -1,     8,    61,    60,    59,    29,     3,    27,
        5,    27,     4,     7,    -1,     8,    12,    60,    59,    29,
        7,    -1,     8,    12,    60,    59,    34,    27,    35,     7,
        -1,    28,    -1,    29,    -1,    27,    -1,     5,    -1,     3,
        -1,     4,    -1,    27,    -1,     6,    -1,    10,    -1,     9,
        -1,    11,    -1
    };

    /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
       YYRHS.  */
    const unsigned char
    Parser::yyprhs_[] =
    {
        0,     0,     3,     7,     9,    12,    14,    16,    18,    20,
        21,    26,    28,    31,    33,    35,    40,    43,    45,    48,
        50,    52,    54,    56,    58,    60,    62,    64,    66,    68,
        71,    76,    78,    80,    82,    84,    86,    91,    94,    96,
        103,   115,   122,   131,   133,   135,   137,   139,   141,   143,
        145,   147,   149,   151
    };

    /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
    const unsigned char
    Parser::yyrline_[] =
    {
        0,    64,    64,    71,    72,    76,    77,    78,    79,    83,
        83,    87,    88,    92,    93,    97,   104,   111,   112,   116,
        117,   118,   119,   120,   121,   122,   127,   130,   133,   139,
        151,   158,   159,   160,   161,   162,   166,   173,   180,   188,
        193,   198,   203,   209,   210,   211,   212,   213,   214,   218,
        222,   223,   224,   225
    };

    // Print the state stack on the debug stream.
    void
    Parser::yystack_print_ ()
    {
        *yycdebug_ << "Stack now";
        for (state_stack_type::const_iterator i = yystate_stack_.begin ();
                i != yystate_stack_.end (); ++i)
            *yycdebug_ << ' ' << *i;
        *yycdebug_ << std::endl;
    }

    // Report on the debug stream that the rule \a yyrule is going to be reduced.
    void
    Parser::yy_reduce_print_ (int yyrule)
    {
        unsigned int yylno = yyrline_[yyrule];
        int yynrhs = yyr2_[yyrule];
        /* Print the symbols being reduced, and their result.  */
        *yycdebug_ << "Reducing stack by rule " << yyrule - 1
        << " (line " << yylno << "):" << std::endl;
        /* The symbols being reduced.  */
        for (int yyi = 0; yyi < yynrhs; yyi++)
            YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                             yyrhs_[yyprhs_[yyrule] + yyi],
                             &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
                             &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
    }
#endif // YYDEBUG

    /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
    Parser::token_number_type
    Parser::yytranslate_ (int t)
    {
        static
        const token_number_type
        translate_table[] =
        {
            0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
            2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
            5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
            15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
            25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
            35,    36
        };
        if ((unsigned int) t <= yyuser_token_number_max_)
            return translate_table[t];
        else
            return yyundef_token_;
    }

    const int Parser::yyeof_ = 0;
    const int Parser::yylast_ = 73;
    const int Parser::yynnts_ = 25;
    const int Parser::yyempty_ = -2;
    const int Parser::yyfinal_ = 32;
    const int Parser::yyterror_ = 1;
    const int Parser::yyerrcode_ = 256;
    const int Parser::yyntokens_ = 37;

    const unsigned int Parser::yyuser_token_number_max_ = 291;
    const Parser::token_number_type Parser::yyundef_token_ = 2;


    /* Line 1054 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

} // evcd

/* Line 1054 of lalr1.cc  */
#line 1096 "evcd_yacc.cpp"


/* Line 1056 of lalr1.cc  */
#line 228 "evcd.y"


void evcd::Parser::error(const Parser::location_type& l, const std::string& m)
{
    driver.error(l, m);
}




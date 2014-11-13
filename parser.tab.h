/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TK_ID = 258,
    TK_STRING = 259,
    TK_INT = 260,
    TK_COMMA = 261,
    TK_COLON = 262,
    TK_LPAREN = 263,
    TK_RPAREN = 264,
    TK_LBRACK = 265,
    TK_RBRACK = 266,
    TK_LBRACE = 267,
    TK_RBRACE = 268,
    TK_DOT = 269,
    TK_ARRAY = 270,
    TK_IF = 271,
    TK_THEN = 272,
    TK_ELSE = 273,
    TK_WHILE = 274,
    TK_FOR = 275,
    TK_TO = 276,
    TK_LET = 277,
    TK_IN = 278,
    TK_END = 279,
    TK_OF = 280,
    TK_BREAK = 281,
    TK_NIL = 282,
    TK_FUNCTION = 283,
    TK_VAR = 284,
    TK_TYPE = 285,
    TK_SEMICOLON = 286,
    TK_DO = 287,
    TK_ASSIGN = 288,
    TK_OR = 289,
    TK_AND = 290,
    TK_EQ = 291,
    TK_NEQ = 292,
    TK_LT = 293,
    TK_LE = 294,
    TK_GT = 295,
    TK_GE = 296,
    TK_PLUS = 297,
    TK_MINUS = 298,
    TK_TIMES = 299,
    TK_DIVIDE = 300,
    TK_UMINUS = 301
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 13 "parser.y" /* yacc.c:1909  */

    int pos;
    int ival;
    string sval;
    L_list list;
    S_symbol sym;
    ABS_var var;
    ABS_expr expr;
    ABS_dec dec;
    ABS_fundec func;
    ABS_type type;

#line 114 "parser.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

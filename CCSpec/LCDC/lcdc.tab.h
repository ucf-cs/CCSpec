/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_LCDC_TAB_H_INCLUDED
# define YY_YY_LCDC_TAB_H_INCLUDED
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
    INTEGER = 258,
    VARIABLE = 259,
    ALPHANUM = 260,
    POSTINC = 261,
    POSTDEC = 262,
    PREINC = 263,
    PREDEC = 264,
    WHILE = 265,
    IF = 266,
    PRINT = 267,
    FOR = 268,
    FORALL = 269,
    EXISTS = 270,
    FPRINTF = 271,
    HISTORYOBJECT = 272,
    NUMTHREADS = 273,
    STACKLENGTH = 274,
    HISTORYSTACK = 275,
    ACTGETTYPE = 276,
    ACTGETORDER = 277,
    ACTGETTID = 278,
    ACTGETSEQNUM = 279,
    ACTTYPE_INVOCATION = 280,
    ACTTYPE_RESPONSE = 281,
    METHODID = 282,
    ISACTIVE = 283,
    HAPPENSBEFORE = 284,
    METHODNAME = 285,
    IFX = 286,
    ELSE = 287,
    RANGE = 288,
    AND = 289,
    OR = 290,
    GE = 291,
    LE = 292,
    EQ = 293,
    NE = 294,
    INC = 295,
    DEC = 296,
    UMINUS = 297
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 34 "lcdc.y" /* yacc.c:1909  */

    int iValue;                 /* integer value */
    char sIndex;                /* symbol table index */
    nodeType *nPtr;             /* node pointer */
    char *charArray;

#line 104 "lcdc.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_LCDC_TAB_H_INCLUDED  */

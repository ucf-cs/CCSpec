/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "lcdc.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <string.h>
#include "lcdc.h"
#include "HistoryShell.h"

FILE * pFile;

/* prototypes */
extern "C"
{
    nodeType *opr(int oper, int nops, ...);
    nodeType *id(int i);
    nodeType *idString(char *i);
    nodeType *con(int value);
    void freeNode(nodeType *p);
    int ex(nodeType *p);
    unsigned long hash(char *str);
    int yylex(void);

    void yyerror(char *s);
}

//int sym[26];                    /* symbol table */

symbolType sym[SIZE];             /* symbol table */
HistoryShell *h;


#line 99 "lcdc.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "lcdc.tab.h".  */
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
#line 34 "lcdc.y" /* yacc.c:355  */

    int iValue;                 /* integer value */
    char sIndex;                /* symbol table index */
    nodeType *nPtr;             /* node pointer */
    char *charArray;

#line 189 "lcdc.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_LCDC_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 206 "lcdc.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   768

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  7
/* YYNRULES -- Number of rules.  */
#define YYNRULES  60
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  178

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   297

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      51,    52,    44,    42,    58,    43,    55,    45,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    59,    49,
      41,    50,    40,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    56,     2,    57,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    53,     2,    54,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    65,    65,    69,    70,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    89,    90,    94,
      95,    96,    97,    98,    99,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "VARIABLE", "ALPHANUM",
  "POSTINC", "POSTDEC", "PREINC", "PREDEC", "WHILE", "IF", "PRINT", "FOR",
  "FORALL", "EXISTS", "FPRINTF", "HISTORYOBJECT", "NUMTHREADS",
  "STACKLENGTH", "HISTORYSTACK", "ACTGETTYPE", "ACTGETORDER", "ACTGETTID",
  "ACTGETSEQNUM", "ACTTYPE_INVOCATION", "ACTTYPE_RESPONSE", "METHODID",
  "ISACTIVE", "HAPPENSBEFORE", "METHODNAME", "IFX", "ELSE", "RANGE", "AND",
  "OR", "GE", "LE", "EQ", "NE", "'>'", "'<'", "'+'", "'-'", "'*'", "'/'",
  "INC", "DEC", "UMINUS", "';'", "'='", "'('", "')'", "'{'", "'}'", "'.'",
  "'['", "']'", "','", "':'", "$accept", "program", "function", "stmt",
  "stmt_list", "stmt_partial", "expr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
      62,    60,    43,    45,    42,    47,   295,   296,   297,    59,
      61,    40,    41,   123,   125,    46,    91,    93,    44,    58
};
# endif

#define YYPACT_NINF -45

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-45)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -45,     1,   178,   -45,   -45,   -44,   -43,   -41,   -35,   229,
     -31,     9,    29,   229,     4,   -45,   -45,    30,    33,    35,
     229,    58,    76,   -45,   229,   178,   -45,   362,   -45,   -45,
     229,   229,   229,   229,    -4,   -45,   587,   178,    26,    28,
      31,    32,   603,    11,   229,   229,   229,   -45,   -45,   -45,
     378,   -45,   126,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   -45,   619,   635,   397,
     416,   -45,   229,   229,   229,   229,   229,   -45,   -45,   -45,
      37,    34,   226,   251,   -45,   -45,   -45,   651,   274,   274,
     -17,   -17,   -17,   -17,   -17,   -17,    13,    13,   -45,   -45,
     -45,   -45,   178,   178,   667,   684,   697,   710,   723,   229,
     229,   229,   229,   -45,   -45,    56,    14,   229,   229,   229,
     229,    78,   435,   454,   473,   178,   -38,    39,    90,    91,
      44,   263,   288,   300,   325,    42,   -45,   -45,    60,   -45,
     -45,   -45,   229,   229,   -45,   -45,   178,    48,    53,    55,
      73,    17,    77,   175,   175,   -45,   229,   229,   229,   229,
     -45,   -45,   -45,   -45,    74,   492,   511,   530,   549,   229,
     -45,   -45,   -45,   -45,   337,   229,   568,   -45
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,     1,    25,    26,    27,     0,     0,     0,
       0,     0,     0,     0,     0,    28,    29,     0,     0,     0,
       0,     0,     0,     5,     0,     0,     3,     0,    52,    53,
       0,     0,     0,     0,    26,    27,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    39,    54,    55,
       0,    17,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,     0,     0,     0,
       0,     7,     0,     0,     0,     0,     0,     8,    30,    31,
       0,     0,     0,     0,    60,    16,    18,     0,    50,    51,
      46,    47,    49,    48,    45,    44,    40,    41,    42,    43,
       9,    10,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    11,    12,    13,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    36,    37,     0,    14,
      21,    22,     0,     0,    23,    24,     0,     0,     0,     0,
       0,     0,     0,    19,    20,    15,     0,     0,     0,     0,
      32,    33,    34,    35,     0,     0,     0,     0,     0,     0,
      56,    57,    58,    59,     0,     0,     0,    38
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -45,   -45,   -45,   -20,   -45,   -45,    -9
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    26,    52,   130,    27
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      36,     3,    28,    29,    42,    51,    30,    31,   140,   141,
      32,    47,   142,    38,    39,    50,    33,    72,   126,   127,
      37,    67,    68,    69,    70,    62,    63,    64,    65,    78,
      79,    80,    86,    40,    41,    81,    82,    83,   160,   161,
     162,   163,    28,    29,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,    64,    65,    43,
     128,   129,    48,   104,   105,   106,   107,   108,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      49,    44,   114,   115,    45,    73,    46,    74,   125,   143,
      75,    76,   110,   109,   144,   145,   146,   151,   152,   156,
     121,   122,   123,   124,   157,   139,   158,   164,   131,   132,
     133,   134,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,   159,   169,   155,     0,     0,     4,
       5,     6,     0,   153,   154,   135,     7,     8,     9,    10,
      11,    12,    13,    14,     0,     0,     0,   165,   166,   167,
     168,    15,    16,    17,    18,     0,    19,     0,     0,     0,
     174,     0,     0,     0,     0,     0,   176,     0,     0,    20,
       0,     0,    21,    22,     0,    23,     0,    24,     0,    25,
      85,     4,     5,     6,     0,     0,     0,     0,     7,     8,
       9,    10,    11,    12,    13,    14,     0,     0,     0,     0,
       0,     0,     0,    15,    16,    17,    18,     0,    19,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    20,     0,     0,    21,    22,     0,    23,     0,    24,
       0,    25,     4,    34,    35,     0,     0,     0,     0,     0,
       0,     0,     0,    11,    12,     0,    14,     0,     0,     0,
       0,     0,     0,     0,    15,    16,    17,    18,     0,    19,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    20,     0,     0,    21,    22,     0,     0,     0,
      24,     0,     0,     0,   111,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,   112,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
       0,   147,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,   148,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   149,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,   150,     0,     0,     0,     0,     0,     0,
       0,    53,     0,     0,     0,   175,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,     0,     0,
       0,    66,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,     0,     0,     0,     0,     0,     0,
      84,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,     0,     0,     0,     0,     0,     0,   102,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,     0,     0,     0,     0,     0,     0,   103,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,     0,     0,     0,     0,     0,     0,   136,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
       0,     0,     0,     0,     0,     0,   137,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,     0,
       0,     0,     0,     0,     0,   138,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,     0,     0,
       0,     0,     0,     0,   170,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,     0,     0,     0,
       0,     0,     0,   171,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,     0,     0,     0,     0,
       0,     0,   172,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,     0,     0,     0,     0,     0,
       0,   173,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,     0,     0,     0,     0,     0,     0,
     177,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,     0,     0,     0,    71,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,     0,
       0,     0,    77,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,     0,     0,     0,   100,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,     0,     0,     0,   101,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,     0,     0,     0,
     113,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,     0,     0,     0,   116,   117,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
     118,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,   119,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,   120,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65
};

static const yytype_int16 yycheck[] =
{
       9,     0,    46,    47,    13,    25,    50,    50,    46,    47,
      51,    20,    50,     4,     5,    24,    51,    37,     4,     5,
      51,    30,    31,    32,    33,    42,    43,    44,    45,    18,
      19,    20,    52,     4,     5,    44,    45,    46,    21,    22,
      23,    24,    46,    47,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    44,    45,    55,
      46,    47,     4,    72,    73,    74,    75,    76,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
       4,    51,   102,   103,    51,    59,    51,    59,    32,    50,
      59,    59,    58,    56,     4,     4,    52,    55,    38,    51,
     109,   110,   111,   112,    51,   125,    51,    30,   117,   118,
     119,   120,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    51,    51,   146,    -1,    -1,     3,
       4,     5,    -1,   142,   143,    57,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    -1,   156,   157,   158,
     159,    25,    26,    27,    28,    -1,    30,    -1,    -1,    -1,
     169,    -1,    -1,    -1,    -1,    -1,   175,    -1,    -1,    43,
      -1,    -1,    46,    47,    -1,    49,    -1,    51,    -1,    53,
      54,     3,     4,     5,    -1,    -1,    -1,    -1,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    25,    26,    27,    28,    -1,    30,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    43,    -1,    -1,    46,    47,    -1,    49,    -1,    51,
      -1,    53,     3,     4,     5,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    14,    15,    -1,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    25,    26,    27,    28,    -1,    30,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    43,    -1,    -1,    46,    47,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    58,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    58,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    58,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    58,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    29,    -1,    -1,    -1,    58,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    -1,
      -1,    49,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    52,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    52,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    52,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    -1,    -1,    49,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      -1,    -1,    49,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    -1,    -1,    49,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    49,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      49,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    -1,    -1,    49,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    61,    62,     0,     3,     4,     5,    10,    11,    12,
      13,    14,    15,    16,    17,    25,    26,    27,    28,    30,
      43,    46,    47,    49,    51,    53,    63,    66,    46,    47,
      50,    50,    51,    51,     4,     5,    66,    51,     4,     5,
       4,     5,    66,    55,    51,    51,    51,    66,     4,     4,
      66,    63,    64,    29,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    49,    66,    66,    66,
      66,    49,    63,    59,    59,    59,    59,    49,    18,    19,
      20,    66,    66,    66,    52,    54,    63,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      49,    49,    52,    52,    66,    66,    66,    66,    66,    56,
      58,    58,    58,    49,    63,    63,    49,    33,    33,    33,
      33,    66,    66,    66,    66,    32,     4,     5,    46,    47,
      65,    66,    66,    66,    66,    57,    52,    52,    52,    63,
      46,    47,    50,    50,     4,     4,    52,    58,    58,    58,
      58,    55,    38,    66,    66,    63,    51,    51,    51,    51,
      21,    22,    23,    24,    30,    66,    66,    66,    66,    51,
      52,    52,    52,    52,    66,    58,    66,    52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    60,    61,    62,    62,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    64,    64,    65,
      65,    65,    65,    65,    65,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     2,     3,     3,     4,
       4,     4,     5,     5,     7,     8,     3,     1,     2,     3,
       3,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       3,     3,     8,     8,     8,     8,     6,     6,    13,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     2,    10,    10,    10,    10,
       3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 65 "lcdc.y" /* yacc.c:1646  */
    { /*exit(0);*/ ; }
#line 1509 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 69 "lcdc.y" /* yacc.c:1646  */
    { ex((yyvsp[0].nPtr)); freeNode((yyvsp[0].nPtr)); }
#line 1515 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 74 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(';', 2, NULL, NULL); }
#line 1521 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 75 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = (yyvsp[-1].nPtr); }
#line 1527 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 76 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(PRINT, 1, (yyvsp[-1].nPtr)); }
#line 1533 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 77 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(FPRINTF, 1, (yyvsp[-1].nPtr)); }
#line 1539 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 78 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('=', 2, id((yyvsp[-3].sIndex)), (yyvsp[-1].nPtr)); }
#line 1545 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 79 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('=', 2, idString((yyvsp[-3].charArray)), (yyvsp[-1].nPtr)); }
#line 1551 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 80 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(HAPPENSBEFORE, 2, (yyvsp[-3].nPtr), (yyvsp[-1].nPtr)); }
#line 1557 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 81 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(WHILE, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1563 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 82 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(IF, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1569 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 83 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(IF, 3, (yyvsp[-4].nPtr), (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1575 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 84 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(FOR, 4, (yyvsp[-5].nPtr), (yyvsp[-4].nPtr), (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1581 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 85 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = (yyvsp[-1].nPtr); }
#line 1587 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 89 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = (yyvsp[0].nPtr); }
#line 1593 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 90 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(';', 2, (yyvsp[-1].nPtr), (yyvsp[0].nPtr)); }
#line 1599 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 94 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('=', 2, id((yyvsp[-2].sIndex)), (yyvsp[0].nPtr)); }
#line 1605 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 95 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('=', 2, idString((yyvsp[-2].charArray)), (yyvsp[0].nPtr)); }
#line 1611 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 96 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(POSTINC, 1, id((yyvsp[-1].sIndex))); }
#line 1617 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 97 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(POSTDEC, 1, id((yyvsp[-1].sIndex))); }
#line 1623 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 98 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(PREINC, 1, id((yyvsp[0].sIndex))); }
#line 1629 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 99 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(PREDEC, 1, id((yyvsp[0].sIndex))); }
#line 1635 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 103 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = con((yyvsp[0].iValue)); }
#line 1641 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 104 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = id((yyvsp[0].sIndex)); }
#line 1647 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 105 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = idString((yyvsp[0].charArray)); }
#line 1653 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 106 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(ACTTYPE_INVOCATION, 0); }
#line 1659 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 107 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(ACTTYPE_RESPONSE, 0); }
#line 1665 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 108 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(NUMTHREADS, 0); }
#line 1671 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 109 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(STACKLENGTH, 0); }
#line 1677 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 110 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(ACTGETTYPE, 1, (yyvsp[-3].nPtr)); }
#line 1683 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 111 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(ACTGETORDER, 1, (yyvsp[-3].nPtr)); }
#line 1689 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 112 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(ACTGETTID, 1, (yyvsp[-3].nPtr)); }
#line 1695 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 113 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(ACTGETSEQNUM, 1, (yyvsp[-3].nPtr)); }
#line 1701 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 114 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(METHODID, 2, (yyvsp[-3].nPtr), (yyvsp[-1].nPtr)); }
#line 1707 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 115 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(ISACTIVE, 2, (yyvsp[-3].nPtr), (yyvsp[-1].nPtr)); }
#line 1713 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 117 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(METHODNAME, 4, (yyvsp[-10].nPtr), (yyvsp[-8].nPtr), (yyvsp[-3].nPtr), (yyvsp[-1].nPtr)); }
#line 1719 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 118 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(UMINUS, 1, (yyvsp[0].nPtr)); }
#line 1725 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 119 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('+', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1731 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 120 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('-', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1737 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 121 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('*', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1743 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 122 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('/', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1749 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 123 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('<', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1755 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 124 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('>', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1761 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 125 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(GE, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1767 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 126 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(LE, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1773 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 127 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(NE, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1779 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 128 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(EQ, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1785 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 129 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(AND, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1791 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 130 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(OR, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1797 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 131 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(POSTINC, 1, id((yyvsp[-1].sIndex))); }
#line 1803 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 132 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(POSTDEC, 1, id((yyvsp[-1].sIndex))); }
#line 1809 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 133 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(PREINC, 1, id((yyvsp[0].sIndex))); }
#line 1815 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 134 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(PREDEC, 1, id((yyvsp[0].sIndex))); }
#line 1821 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 135 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(FORALL, 4, id((yyvsp[-8].sIndex)), (yyvsp[-6].nPtr), (yyvsp[-4].nPtr), (yyvsp[-1].nPtr)); }
#line 1827 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 136 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(FORALL, 4, idString((yyvsp[-8].charArray)), (yyvsp[-6].nPtr), (yyvsp[-4].nPtr), (yyvsp[-1].nPtr)); }
#line 1833 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 137 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(EXISTS, 4, id((yyvsp[-8].sIndex)), (yyvsp[-6].nPtr), (yyvsp[-4].nPtr), (yyvsp[-1].nPtr)); }
#line 1839 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 138 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(EXISTS, 4, idString((yyvsp[-8].charArray)), (yyvsp[-6].nPtr), (yyvsp[-4].nPtr), (yyvsp[-1].nPtr)); }
#line 1845 "lcdc.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 139 "lcdc.y" /* yacc.c:1646  */
    { (yyval.nPtr) = (yyvsp[-1].nPtr); }
#line 1851 "lcdc.tab.c" /* yacc.c:1646  */
    break;


#line 1855 "lcdc.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
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
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 145 "lcdc.y" /* yacc.c:1906  */


nodeType *con(int value) {
    nodeType *p;

    /* allocate node */
    if ((p = (nodeType*) malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeCon;
    p->con.value = value;

    return p;
}

nodeType *id(int i) {
    nodeType *p;

    /* allocate node */
    if ((p = (nodeType*) malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeId;
    p->id.i = i;
    printf("p->id.i = %d\n", i);

    return p;
}

nodeType *idString(char *i) {
    nodeType *p;
    unsigned long hashId;

    /* allocate node */
    if ((p = (nodeType*) malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeIdString;
    
    hashId = hash(i);
    printf("hashId = %lu\n", hashId);
    if(sym[hashId].key == NULL)
    {
        p->id.i = hashId;
    } else if (strcmp(i, sym[hashId].key) == 0)
    {
        p->id.i = hashId;
    } else 
    {
        int count = 0;
        do{
            hashId = (hashId + 1)%SIZE; //linear probing
            if(hashId < 26)
                hashId = hashId + 26; //first 26 reserved for single letter variables
            if(sym[hashId].key == NULL)
                break;
            if(++count > SIZE)
            {
                printf("Symbol Table is full\n");
                break;          
            }
        } while (strcmp(i, sym[hashId].key) != 0);
        p->id.i = hashId; 
    }

    return p;
}

nodeType *opr(int oper, int nops, ...) {
    va_list ap;
    nodeType *p;
    int i;

    /* allocate node */
    if ((p = (nodeType*) malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");
    if ((p->opr.op = (nodeType**) malloc(nops * sizeof(nodeType *))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
    va_start(ap, nops);
    for (i = 0; i < nops; i++)
        p->opr.op[i] = va_arg(ap, nodeType*);
    va_end(ap);
    return p;
}

void freeNode(nodeType *p) {
    int i;

    if (!p) return;
    if (p->type == typeOpr) {
        for (i = 0; i < p->opr.nops; i++)
            freeNode(p->opr.op[i]);
        free(p->opr.op);
    }
    free (p);
}

void yyerror(char *s) {
    fprintf(stdout, "%s\n", s);
}

int main(int argc, char *argv[]) {
    
    HistoryShell obj;
    h = &obj;
    
    pFile = fopen("LCDC/output.txt", "w");
    h->retrieve_history(pFile);
    
	
    yyparse();

	h->topological_sort(pFile);
	h->get_legal_seq_histories(pFile);
	h->map_legal_seq_histories(pFile); 

    fclose(pFile); 
    return 0;
}

int ex(nodeType *p) {
    
    if (!p) return 0;
    switch(p->type) {
    case typeCon:       return p->con.value; //fprintf(pFile, "%d\n", p->con.value); 
    case typeId:        return sym[p->id.i].value; //fprintf(pFile, "sym[%d] = %d\n", p->id.i, sym[p->id.i].value); 
    case typeIdString:  return sym[p->id.i].value; //fprintf(pFile, "sym[%d] = %d\n", p->id.i, sym[p->id.i].value); 
    case typeOpr:
        switch(p->opr.oper) {
        case WHILE:     while(ex(p->opr.op[0])) ex(p->opr.op[1]); return 0;
        case IF:        if (ex(p->opr.op[0]))
                            ex(p->opr.op[1]);
                        else if (p->opr.nops > 2)
                            ex(p->opr.op[2]);
                        return 0;
        case FOR:       for(ex(p->opr.op[0]); ex(p->opr.op[1]); ex(p->opr.op[2])) ex(p->opr.op[3]); return 0;
        case FORALL:    for(sym[p->opr.op[0]->id.i].value = ex(p->opr.op[1]); sym[p->opr.op[0]->id.i].value <= ex(p->opr.op[2]); sym[p->opr.op[0]->id.i].value++)
                        {
                            if(!ex(p->opr.op[3]))
                                return 0; 
                        }             
                        return 1;
        case EXISTS:    for(sym[p->opr.op[0]->id.i].value = ex(p->opr.op[1]); sym[p->opr.op[0]->id.i].value <= ex(p->opr.op[2]); sym[p->opr.op[0]->id.i].value++)
                        {
                            if(ex(p->opr.op[3]))
                                return 1; 
                        }   
                        return 0;                                                        
        case PRINT:     printf("%d\n", ex(p->opr.op[0])); return 0;
        case FPRINTF:   fprintf(pFile, "%d\n", ex(p->opr.op[0])); return 0;
        case ';':       ex(p->opr.op[0]); return ex(p->opr.op[1]);
        case '=':       return sym[p->opr.op[0]->id.i].value = ex(p->opr.op[1]);
        case UMINUS:    return -ex(p->opr.op[0]);
        case '+':       return ex(p->opr.op[0]) + ex(p->opr.op[1]);
        case '-':       return ex(p->opr.op[0]) - ex(p->opr.op[1]);
        case '*':       return ex(p->opr.op[0]) * ex(p->opr.op[1]);
        case '/':       return ex(p->opr.op[0]) / ex(p->opr.op[1]);
        case '<':       return ex(p->opr.op[0]) < ex(p->opr.op[1]);
        case '>':       return ex(p->opr.op[0]) > ex(p->opr.op[1]);
        case GE:        return ex(p->opr.op[0]) >= ex(p->opr.op[1]);
        case LE:        return ex(p->opr.op[0]) <= ex(p->opr.op[1]);
        case NE:        return ex(p->opr.op[0]) != ex(p->opr.op[1]);
        case EQ:        return ex(p->opr.op[0]) == ex(p->opr.op[1]);
        case AND:       return ex(p->opr.op[0]) && ex(p->opr.op[1]);
        case OR:        return ex(p->opr.op[0]) || ex(p->opr.op[1]);
		case POSTINC:       return sym[p->opr.op[0]->id.i].value++;
		case POSTDEC:       return sym[p->opr.op[0]->id.i].value--;
		case PREINC:        return ++sym[p->opr.op[0]->id.i].value;
		case PREDEC:        return --sym[p->opr.op[0]->id.i].value;
        case NUMTHREADS:    return h->p;
        case STACKLENGTH:   return h->length;
        case ACTGETTYPE:    return h->s[ex(p->opr.op[0])].type;
        case ACTGETORDER:   return h->s[ex(p->opr.op[0])].order;
        case ACTGETTID:     return h->s[ex(p->opr.op[0])].tid;
        case ACTGETSEQNUM:  return h->s[ex(p->opr.op[0])].seq_num;
		case METHODID:		return h->method_id((unsigned int) ex(p->opr.op[0]), ex(p->opr.op[1]));
		case ISACTIVE:		return h->is_active((unsigned int) ex(p->opr.op[0]), ex(p->opr.op[1]));
		case METHODNAME:	if(strcmp(h->method_name((unsigned int) ex(p->opr.op[0]), ex(p->opr.op[1])), h->method_name((unsigned int) ex(p->opr.op[2]), ex(p->opr.op[3]))) == 0)
								return 1;
							else
								return 0;
		case HAPPENSBEFORE:	fprintf(pFile, "%d happens before", ex(p->opr.op[0])); fprintf(pFile, " %d\n", ex(p->opr.op[1])); 
							h->happens_before(pFile, ex(p->opr.op[0]), ex(p->opr.op[1]));
							h->print_graph(pFile);
	 						return 0;
		case ACTTYPE_INVOCATION:	return INVOCATION;
		case ACTTYPE_RESPONSE:		return RESPONSE;
        }
    }
    return 0;
}

unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    hash = hash%SIZE;
    if(hash < 26)
        hash = hash + 26;
    
    return hash;
}



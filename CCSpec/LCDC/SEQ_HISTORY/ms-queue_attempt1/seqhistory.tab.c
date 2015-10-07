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
#line 1 "seqhistory.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <string.h>
#include <atomic>
#include "seqhistory.h"
#include "my_queue.h" //For now, this has to be stripped of the annotations

FILE * pFile;

//HWQueue<int> *q;

/* prototypes */
extern "C"
{
    nodeType *opr(int oper, int nops, ...);
    nodeType *id(int i);
    nodeType *idString(char *i);
    nodeType *con(int value);
    nodeType *ptr(void *addr);
    void freeNode(nodeType *p);
    int ex(nodeType *p);
    unsigned long hash_function(char *str);
    int yylex(void);

    void yyerror(char *s);
}

//int sym[26];                    /* symbol table */

symbolType sym[SIZE];             /* symbol table */


#line 102 "seqhistory.tab.c" /* yacc.c:339  */

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
   by #include "seqhistory.tab.h".  */
#ifndef YY_YY_SEQHISTORY_TAB_H_INCLUDED
# define YY_YY_SEQHISTORY_TAB_H_INCLUDED
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
    WHILE = 261,
    IF = 262,
    PRINT = 263,
    FOR = 264,
    FORALL = 265,
    EXISTS = 266,
    FPRINTF = 267,
    ENQUEUE = 268,
    DEQUEUE = 269,
    QUEUE = 270,
    IFX = 271,
    ELSE = 272,
    RANGE = 273,
    HEX = 274,
    AND = 275,
    OR = 276,
    GE = 277,
    LE = 278,
    EQ = 279,
    NE = 280,
    UMINUS = 281
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 37 "seqhistory.y" /* yacc.c:355  */

    int iValue;                 /* integer value */
    char sIndex;                /* symbol table index */
    nodeType *nPtr;             /* node pointer */
    char *charArray;

#line 176 "seqhistory.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SEQHISTORY_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 193 "seqhistory.tab.c" /* yacc.c:358  */

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
#define YYLAST   483

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  7
/* YYNRULES -- Number of rules.  */
#define YYNRULES  42
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  138

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

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
      35,    36,    30,    28,    39,    29,     2,    31,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    40,    33,
      27,    34,    26,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,    38,     2,     2,     2,     2,
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
      25,    32
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    65,    65,    69,    70,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    90,    91,
      95,    96,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "VARIABLE", "ALPHANUM",
  "WHILE", "IF", "PRINT", "FOR", "FORALL", "EXISTS", "FPRINTF", "ENQUEUE",
  "DEQUEUE", "QUEUE", "IFX", "ELSE", "RANGE", "HEX", "AND", "OR", "GE",
  "LE", "EQ", "NE", "'>'", "'<'", "'+'", "'-'", "'*'", "'/'", "UMINUS",
  "';'", "'='", "'('", "')'", "'{'", "'}'", "','", "':'", "$accept",
  "program", "function", "stmt", "stmt_list", "stmt_partial", "expr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,    62,    60,    43,    45,
      42,    47,   281,    59,    61,    40,    41,   123,   125,    44,
      58
};
# endif

#define YYPACT_NINF -25

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-25)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -25,     8,   117,   -25,   -25,   -24,   -22,   -14,     9,    20,
      10,    -2,     1,    20,    11,    12,    20,   -25,    20,   117,
     -25,   314,    20,    20,    20,    20,   -25,   -25,   328,   117,
      40,    41,    42,    43,   342,    33,    70,   -25,   195,   -25,
      65,    20,    20,    20,    20,    20,    20,    20,    20,    20,
      20,    20,    20,   -25,   356,   370,   212,   229,   -25,    20,
      20,    20,    20,    20,   -25,    47,    52,   -25,   -25,   -25,
      34,    34,   -11,   -11,   -11,   -11,   -11,   -11,    -4,    -4,
     -25,   -25,   -25,   -25,   117,   117,   384,   398,   412,   426,
     440,    89,    74,   -25,    78,    24,    20,    20,    20,    20,
      60,    94,   117,    67,    72,    71,   112,   135,   155,   175,
      75,    73,   -25,    20,    20,   117,    76,    77,    79,    80,
     -25,   111,   452,   452,   -25,    20,    20,    20,    20,   -25,
     246,   263,   280,   297,   -25,   -25,   -25,   -25
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,     1,    22,    23,    24,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     5,     0,     0,
       3,     0,     0,     0,     0,     0,    23,    24,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    25,     0,    18,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     6,     0,     0,     0,     0,     7,     0,
       0,     0,     0,     0,     8,     0,     0,    42,    15,    19,
      36,    37,    32,    33,    35,    34,    31,    30,    26,    27,
      28,    29,     9,    10,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    11,    12,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    13,     0,     0,     0,     0,     0,     0,     0,
      16,     0,    20,    21,    14,     0,     0,     0,     0,    17,
       0,     0,     0,     0,    38,    39,    40,    41
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -25,   -25,   -25,   -18,   -25,   -25,    -9
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    20,    40,   105,    21
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      28,    39,    30,    31,    34,    32,    33,    37,     3,    38,
      22,    59,    23,    54,    55,    56,    57,    49,    50,    51,
      52,    24,    69,     4,    26,    27,    51,    52,   103,   104,
      11,    12,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    25,    29,    35,    36,    65,    16,
      86,    87,    88,    89,    90,    18,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    93,    94,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      60,    61,    62,    63,   112,    66,    91,   106,   107,   108,
     109,    92,   100,   101,    16,   102,   110,   124,    17,   111,
      18,   113,    19,    68,   122,   123,   114,   115,   120,   121,
       0,   125,   126,     0,   127,   128,   130,   131,   132,   133,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,   129,     0,    16,     0,     0,     0,
      17,   116,    18,     0,    19,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,     0,     0,     0,
       0,     0,     0,     0,   117,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,     0,     0,     0,
       0,     0,     0,     0,   118,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,     0,     0,     0,
       0,     0,     0,     0,   119,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,     0,     0,     0,
       0,    67,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,     0,     0,     0,     0,    84,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,     0,     0,     0,     0,    85,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,     0,     0,
       0,     0,   134,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,     0,     0,     0,     0,   135,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,     0,     0,     0,     0,   136,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,     0,
       0,     0,     0,   137,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,     0,    53,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
       0,    58,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,     0,    64,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,     0,    82,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,     0,    83,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    96,    95,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      97,     0,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    98,     0,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    99,     0,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52
};

static const yytype_int16 yycheck[] =
{
       9,    19,     4,     5,    13,     4,     5,    16,     0,    18,
      34,    29,    34,    22,    23,    24,    25,    28,    29,    30,
      31,    35,    40,     3,     4,     5,    30,    31,     4,     5,
      10,    11,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    35,    35,    35,    35,    15,    29,
      59,    60,    61,    62,    63,    35,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    84,    85,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      40,    40,    40,    40,   102,    15,    39,    96,    97,    98,
      99,    39,     3,    19,    29,    17,    36,   115,    33,     5,
      35,    34,    37,    38,   113,   114,    34,    36,    33,    36,
      -1,    35,    35,    -1,    35,    35,   125,   126,   127,   128,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    33,    -1,    29,    -1,    -1,    -1,
      33,    39,    35,    -1,    37,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    36,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    -1,    36,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    -1,    -1,    -1,    36,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    -1,
      -1,    -1,    36,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,    36,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,    -1,    -1,    36,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    36,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    33,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    33,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    33,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    33,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    33,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    18,    33,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      18,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    18,    -1,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    18,    -1,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    42,    43,     0,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    29,    33,    35,    37,
      44,    47,    34,    34,    35,    35,     4,     5,    47,    35,
       4,     5,     4,     5,    47,    35,    35,    47,    47,    44,
      45,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    33,    47,    47,    47,    47,    33,    44,
      40,    40,    40,    40,    33,    15,    15,    36,    38,    44,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    33,    33,    36,    36,    47,    47,    47,    47,
      47,    39,    39,    44,    44,    33,    18,    18,    18,    18,
       3,    19,    17,     4,     5,    46,    47,    47,    47,    47,
      36,     5,    44,    34,    34,    36,    39,    39,    39,    39,
      33,    36,    47,    47,    44,    35,    35,    35,    35,    33,
      47,    47,    47,    47,    36,    36,    36,    36
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    45,    45,
      46,    46,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     2,     3,     3,     4,
       4,     5,     5,     7,     8,     3,     7,     8,     1,     2,
       3,     3,     1,     1,     1,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,    10,    10,
      10,    10,     3
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
#line 65 "seqhistory.y" /* yacc.c:1646  */
    { /*exit(0);*/ ; }
#line 1416 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 69 "seqhistory.y" /* yacc.c:1646  */
    { ex((yyvsp[0].nPtr)); freeNode((yyvsp[0].nPtr)); }
#line 1422 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 74 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(';', 2, NULL, NULL); }
#line 1428 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 75 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = (yyvsp[-1].nPtr); }
#line 1434 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 76 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(PRINT, 1, (yyvsp[-1].nPtr)); }
#line 1440 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 77 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(FPRINTF, 1, (yyvsp[-1].nPtr)); }
#line 1446 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 78 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('=', 2, id((yyvsp[-3].sIndex)), (yyvsp[-1].nPtr)); }
#line 1452 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 79 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('=', 2, idString((yyvsp[-3].charArray)), (yyvsp[-1].nPtr)); }
#line 1458 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 80 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(WHILE, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1464 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 81 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(IF, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1470 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 82 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(IF, 3, (yyvsp[-4].nPtr), (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1476 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 83 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(FOR, 4, (yyvsp[-5].nPtr), (yyvsp[-4].nPtr), (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1482 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 84 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = (yyvsp[-1].nPtr); }
#line 1488 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 85 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(ENQUEUE, 1, con((yyvsp[-2].iValue))); }
#line 1494 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 86 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(DEQUEUE, 1, ptr((yyvsp[-2].charArray))); }
#line 1500 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 90 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = (yyvsp[0].nPtr); }
#line 1506 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 91 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(';', 2, (yyvsp[-1].nPtr), (yyvsp[0].nPtr)); }
#line 1512 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 95 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('=', 2, id((yyvsp[-2].sIndex)), (yyvsp[0].nPtr)); }
#line 1518 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 96 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('=', 2, idString((yyvsp[-2].charArray)), (yyvsp[0].nPtr)); }
#line 1524 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 100 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = con((yyvsp[0].iValue)); }
#line 1530 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 101 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = id((yyvsp[0].sIndex)); }
#line 1536 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 102 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = idString((yyvsp[0].charArray)); }
#line 1542 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 103 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(UMINUS, 1, (yyvsp[0].nPtr)); }
#line 1548 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 104 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('+', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1554 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 105 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('-', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1560 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 106 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('*', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1566 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 107 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('/', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1572 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 108 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('<', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1578 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 109 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('>', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1584 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 110 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(GE, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1590 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 111 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(LE, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1596 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 112 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(NE, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1602 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 113 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(EQ, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1608 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 114 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(AND, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1614 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 115 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(OR, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1620 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 116 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(FORALL, 4, id((yyvsp[-8].sIndex)), (yyvsp[-6].nPtr), (yyvsp[-4].nPtr), (yyvsp[-1].nPtr)); }
#line 1626 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 117 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(FORALL, 4, idString((yyvsp[-8].charArray)), (yyvsp[-6].nPtr), (yyvsp[-4].nPtr), (yyvsp[-1].nPtr)); }
#line 1632 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 118 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(EXISTS, 4, id((yyvsp[-8].sIndex)), (yyvsp[-6].nPtr), (yyvsp[-4].nPtr), (yyvsp[-1].nPtr)); }
#line 1638 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 119 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(EXISTS, 4, idString((yyvsp[-8].charArray)), (yyvsp[-6].nPtr), (yyvsp[-4].nPtr), (yyvsp[-1].nPtr)); }
#line 1644 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 120 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = (yyvsp[-1].nPtr); }
#line 1650 "seqhistory.tab.c" /* yacc.c:1646  */
    break;


#line 1654 "seqhistory.tab.c" /* yacc.c:1646  */
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
#line 124 "seqhistory.y" /* yacc.c:1906  */


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
    
    hashId = hash_function(i);
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

nodeType *ptr(void *addr)
{
    nodeType *p;

    /* allocate node */
    if ((p = (nodeType*) malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeCon;
    p->ptr.addr = addr;

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
       
    //HWQueue<int> queue;
    //q = &queue;
	pFile = fopen("LCDC/SEQ_HISTORY/output.txt", "a");

	//pFile = fopen("example.txt", "a");     
  
    yyparse();

	fprintf(pFile, "\n");

	fclose(pFile);
	
    return 0;
}

int ex(nodeType *p) {

	//uint64_t result;
    
    if (!p) return 0;
    switch(p->type) {
    case typeCon:       return p->con.value;
    case typeId:        return sym[p->id.i].value;
    case typeIdString:  return sym[p->id.i].value;
	case typePtr:		return 0; //p->ptr.addr
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
        //case FPRINTF:   fprintf(pFile, "%d\n", ex(p->opr.op[0])); return 0;
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
        case ENQUEUE:   return 0; //fprintf(pFile, "0 "); q->enq(ex(p->opr.op[0])); 
        case DEQUEUE:   return 0; //result = q->deq(); fprintf(pFile, "%lu ", result); return result;
        }
    }
    return 0;
}

unsigned long hash_function(char *str)
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



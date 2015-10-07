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
#include "seqhistory.h"
#include <queue>
#include <stack>
#include <map>
#include <deque>

#define EMPTY (uint64_t) 18446744073709551615

FILE * pFile;

std::queue<uint64_t> *q;
std::stack<uint64_t> *s;
std::map<uint64_t,uint64_t> *m;
std::deque<uint64_t> *dq; 
std::priority_queue<uint64_t, std::vector<uint64_t>, std::greater<uint64_t> > *pq_min;

/* prototypes */
extern "C"
{
    nodeType *opr(int oper, int nops, ...);
    nodeType *id(int i);
    nodeType *idString(char *i);
    nodeType *con(int value);
	nodeType *con64(uint64_t value);
    void freeNode(nodeType *p);
    int ex(nodeType *p);
    unsigned long hash(char *str);
    int yylex(void);

    void yyerror(char *s);
}

//int sym[26];                    /* symbol table */

symbolType sym[SIZE];             /* symbol table */


#line 110 "seqhistory.tab.c" /* yacc.c:339  */

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
    INTEGER64 = 261,
    WHILE = 262,
    IF = 263,
    PRINT = 264,
    FOR = 265,
    FORALL = 266,
    EXISTS = 267,
    FPRINTF = 268,
    ENQUEUE = 269,
    DEQUEUE = 270,
    PUSH = 271,
    POP = 272,
    PUT = 273,
    GET = 274,
    REMOVE = 275,
    PUSHBACK = 276,
    POPBACK = 277,
    POPFRONT = 278,
    PUSHFRONT = 279,
    INSERT = 280,
    DELETEMIN = 281,
    IFX = 282,
    ELSE = 283,
    RANGE = 284,
    HEX = 285,
    AND = 286,
    OR = 287,
    GE = 288,
    LE = 289,
    EQ = 290,
    NE = 291,
    UMINUS = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 45 "seqhistory.y" /* yacc.c:355  */

    int iValue;                 /* integer value */
    char sIndex;                /* symbol table index */
    nodeType *nPtr;             /* node pointer */
    char *charArray;
	uint64_t iValue64;			 

#line 196 "seqhistory.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SEQHISTORY_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 213 "seqhistory.tab.c" /* yacc.c:358  */

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
#define YYLAST   695

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  7
/* YYNRULES -- Number of rules.  */
#define YYNRULES  54
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  186

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

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
      46,    47,    41,    39,    50,    40,     2,    42,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    51,    44,
      38,    45,    37,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,     2,    49,     2,     2,     2,     2,
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
      35,    36,    43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    79,    79,    83,    84,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   115,
     116,   120,   121,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "VARIABLE", "ALPHANUM",
  "INTEGER64", "WHILE", "IF", "PRINT", "FOR", "FORALL", "EXISTS",
  "FPRINTF", "ENQUEUE", "DEQUEUE", "PUSH", "POP", "PUT", "GET", "REMOVE",
  "PUSHBACK", "POPBACK", "POPFRONT", "PUSHFRONT", "INSERT", "DELETEMIN",
  "IFX", "ELSE", "RANGE", "HEX", "AND", "OR", "GE", "LE", "EQ", "NE",
  "'>'", "'<'", "'+'", "'-'", "'*'", "'/'", "UMINUS", "';'", "'='", "'('",
  "')'", "'{'", "'}'", "','", "':'", "$accept", "program", "function",
  "stmt", "stmt_list", "stmt_partial", "expr", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,    62,    60,    43,
      45,    42,    47,   292,    59,    61,    40,    41,   123,   125,
      44,    58
};
# endif

#define YYPACT_NINF -35

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-35)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -35,    16,   212,   -35,   -35,   -28,   -26,   -35,   -25,   -24,
      74,   -23,    -2,     5,    74,   -18,   -17,   -16,   -15,   -14,
     -12,   -11,    -8,    -6,    -1,     0,     3,     4,    74,   -35,
      74,   212,   -35,   505,    74,    74,    74,    74,   -35,   -35,
     519,   212,     1,     2,    15,    17,   533,    74,    20,    74,
      22,    74,    74,    74,    74,    23,    24,    74,    74,    34,
     -35,   250,   -35,   165,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,   -35,   547,   561,   267,
     284,   -35,    74,    74,    74,    74,    74,   -35,   301,     7,
     318,    38,    59,   335,   352,   369,    39,    40,   386,   403,
      43,   -35,   -35,   -35,   653,   653,   -34,   -34,   -34,   -34,
     -34,   -34,   -29,   -29,   -35,   -35,   -35,   -35,   212,   212,
     575,   589,   603,   617,   631,    58,   -35,    60,   -35,    74,
      61,    62,    63,   -35,   -35,    64,    66,   -35,   -35,     8,
      10,    74,    74,    74,    74,   -35,   -35,   420,   -35,   -35,
     -35,   -35,   -35,   212,    67,    68,    56,   105,   162,   209,
     230,    71,   -35,    74,    74,   212,    65,    70,    72,    75,
     -35,   643,   643,   -35,    74,    74,    74,    74,   437,   454,
     471,   488,   -35,   -35,   -35,   -35
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,     1,    33,    35,    36,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       0,     0,     3,     0,     0,     0,     0,     0,    35,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      37,     0,    29,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,     0,     0,     0,
       0,     7,     0,     0,     0,     0,     0,     8,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    54,    15,    30,    48,    49,    44,    45,    47,    46,
      43,    42,    38,    39,    40,    41,     9,    10,     0,     0,
       0,     0,     0,     0,     0,     0,    17,     0,    19,     0,
       0,     0,     0,    24,    25,     0,     0,    28,    11,    12,
       0,     0,     0,     0,     0,    16,    18,     0,    21,    22,
      23,    26,    27,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    13,     0,     0,     0,     0,     0,     0,     0,
      20,    31,    32,    14,     0,     0,     0,     0,     0,     0,
       0,     0,    50,    51,    52,    53
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -35,   -35,   -35,   -30,   -35,   -35,   -10
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    32,    63,   156,    33
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      40,    62,    42,    43,    46,    72,    73,    74,    75,    44,
      45,    82,    74,    75,   154,   155,     3,    34,    60,    35,
      61,    36,    37,    41,    77,    78,    79,    80,    47,    48,
      49,    50,    51,   103,    52,    53,   153,    88,    54,    90,
      55,    92,    93,    94,    95,    56,    57,    98,    99,    58,
      59,   126,    83,    84,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,    85,    89,    86,    91,
      96,    97,   120,   121,   122,   123,   124,     4,    38,    39,
       7,   100,   128,   133,   134,    12,    13,   137,   138,   139,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,   145,   165,   146,   148,   149,   150,   151,   129,
     152,   174,   163,   164,    28,   170,   175,     0,   176,   147,
      30,   177,     0,   162,     0,     0,     0,     0,     0,     0,
       0,   157,   158,   159,   160,   173,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,     0,     0,
       0,     0,     0,   171,   172,   166,     0,     0,     0,     0,
       0,     0,     0,     0,   178,   179,   180,   181,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,     0,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    28,     0,     0,     0,    29,
       0,    30,   167,    31,   102,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,     0,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    28,     0,     0,     0,    29,     0,    30,   168,
      31,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,     0,     0,     0,     0,     0,     0,     0,
     169,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,     0,     0,     0,     0,   101,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
       0,     0,     0,     0,   118,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,     0,     0,     0,
       0,   119,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,     0,     0,     0,     0,   125,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,     0,     0,     0,     0,   127,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,     0,     0,
       0,     0,   130,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,     0,     0,     0,     0,   131,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,     0,     0,     0,     0,   132,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,     0,
       0,     0,     0,   135,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,     0,     0,     0,     0,
     136,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,     0,     0,     0,     0,   161,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
       0,     0,     0,     0,   182,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,     0,     0,     0,
       0,   183,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,     0,     0,     0,     0,   184,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,     0,     0,     0,     0,   185,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,     0,    76,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,     0,    81,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,     0,    87,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
       0,   116,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,     0,   117,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,   141,   140,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,   142,     0,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,   143,     0,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
     144,     0,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75
};

static const yytype_int16 yycheck[] =
{
      10,    31,     4,     5,    14,    39,    40,    41,    42,     4,
       5,    41,    41,    42,     4,     5,     0,    45,    28,    45,
      30,    46,    46,    46,    34,    35,    36,    37,    46,    46,
      46,    46,    46,    63,    46,    46,    28,    47,    46,    49,
      46,    51,    52,    53,    54,    46,    46,    57,    58,    46,
      46,    44,    51,    51,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    51,    47,    51,    47,
      47,    47,    82,    83,    84,    85,    86,     3,     4,     5,
       6,    47,    44,    44,    44,    11,    12,    44,   118,   119,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    44,    47,    44,    44,    44,    44,    44,    50,
      44,    46,    45,    45,    40,    44,    46,    -1,    46,   129,
      46,    46,    -1,   153,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   141,   142,   143,   144,   165,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,   163,   164,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   174,   175,   176,   177,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    40,    -1,    -1,    -1,    44,
      -1,    46,    50,    48,    49,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    40,    -1,    -1,    -1,    44,    -1,    46,    50,
      48,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    -1,    -1,    -1,    47,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    -1,    -1,    -1,    47,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    -1,    -1,
      -1,    47,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    -1,    -1,    -1,    47,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    -1,    -1,    -1,    47,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    -1,
      -1,    -1,    47,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    -1,    -1,    -1,    47,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    -1,    -1,    -1,    47,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      -1,    -1,    -1,    47,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    -1,    -1,    -1,
      47,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    -1,    -1,    -1,    47,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    -1,    -1,    -1,    47,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    -1,    -1,
      -1,    47,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    -1,    -1,    -1,    47,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    -1,    -1,    -1,    47,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    44,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    44,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    44,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    44,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    44,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    29,    44,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    29,    -1,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    29,    -1,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      29,    -1,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    53,    54,     0,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    40,    44,
      46,    48,    55,    58,    45,    45,    46,    46,     4,     5,
      58,    46,     4,     5,     4,     5,    58,    46,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    46,
      58,    58,    55,    56,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    44,    58,    58,    58,
      58,    44,    55,    51,    51,    51,    51,    44,    58,    47,
      58,    47,    58,    58,    58,    58,    47,    47,    58,    58,
      47,    47,    49,    55,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    44,    44,    47,    47,
      58,    58,    58,    58,    58,    47,    44,    47,    44,    50,
      47,    47,    47,    44,    44,    47,    47,    44,    55,    55,
      44,    29,    29,    29,    29,    44,    44,    58,    44,    44,
      44,    44,    44,    28,     4,     5,    57,    58,    58,    58,
      58,    47,    55,    45,    45,    47,    50,    50,    50,    50,
      44,    58,    58,    55,    46,    46,    46,    46,    58,    58,
      58,    58,    47,    47,    47,    47
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    54,    54,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    56,
      56,    57,    57,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     2,     3,     3,     4,
       4,     5,     5,     7,     8,     3,     5,     4,     5,     4,
       7,     5,     5,     5,     4,     4,     5,     5,     4,     1,
       2,     3,     3,     1,     1,     1,     1,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
      10,    10,    10,    10,     3
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
#line 79 "seqhistory.y" /* yacc.c:1646  */
    { /*exit(0);*/ ; }
#line 1500 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 83 "seqhistory.y" /* yacc.c:1646  */
    { ex((yyvsp[0].nPtr)); freeNode((yyvsp[0].nPtr)); }
#line 1506 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 88 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(';', 2, NULL, NULL); }
#line 1512 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 89 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = (yyvsp[-1].nPtr); }
#line 1518 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 90 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(PRINT, 1, (yyvsp[-1].nPtr)); }
#line 1524 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 91 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(FPRINTF, 1, (yyvsp[-1].nPtr)); }
#line 1530 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 92 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('=', 2, id((yyvsp[-3].sIndex)), (yyvsp[-1].nPtr)); }
#line 1536 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 93 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('=', 2, idString((yyvsp[-3].charArray)), (yyvsp[-1].nPtr)); }
#line 1542 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 94 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(WHILE, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1548 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 95 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(IF, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1554 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 96 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(IF, 3, (yyvsp[-4].nPtr), (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1560 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 97 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(FOR, 4, (yyvsp[-5].nPtr), (yyvsp[-4].nPtr), (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1566 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 98 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = (yyvsp[-1].nPtr); }
#line 1572 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 99 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(ENQUEUE, 1, (yyvsp[-2].nPtr)); }
#line 1578 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 100 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(DEQUEUE,0); }
#line 1584 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 101 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(PUSH, 1, (yyvsp[-2].nPtr)); }
#line 1590 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 102 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(POP,0); }
#line 1596 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 103 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(PUT, 2, (yyvsp[-4].nPtr), (yyvsp[-2].nPtr)); }
#line 1602 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 104 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(GET, 1, (yyvsp[-2].nPtr)); }
#line 1608 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 105 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(REMOVE, 1, (yyvsp[-2].nPtr)); }
#line 1614 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 106 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(PUSHBACK, 1, (yyvsp[-2].nPtr)); }
#line 1620 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 107 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(POPBACK,0); }
#line 1626 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 108 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(POPFRONT,0); }
#line 1632 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 109 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(PUSHFRONT, 1, (yyvsp[-2].nPtr)); }
#line 1638 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 110 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(INSERT, 1, (yyvsp[-2].nPtr)); }
#line 1644 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 111 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(DELETEMIN, 0); }
#line 1650 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 115 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = (yyvsp[0].nPtr); }
#line 1656 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 116 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(';', 2, (yyvsp[-1].nPtr), (yyvsp[0].nPtr)); }
#line 1662 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 120 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('=', 2, id((yyvsp[-2].sIndex)), (yyvsp[0].nPtr)); }
#line 1668 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 121 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('=', 2, idString((yyvsp[-2].charArray)), (yyvsp[0].nPtr)); }
#line 1674 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 125 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = con((yyvsp[0].iValue)); }
#line 1680 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 126 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = con64((yyvsp[0].iValue64)); }
#line 1686 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 127 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = id((yyvsp[0].sIndex)); }
#line 1692 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 128 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = idString((yyvsp[0].charArray)); }
#line 1698 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 129 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(UMINUS, 1, (yyvsp[0].nPtr)); }
#line 1704 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 130 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('+', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1710 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 131 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('-', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1716 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 132 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('*', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1722 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 133 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('/', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1728 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 134 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('<', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1734 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 135 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr('>', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1740 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 136 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(GE, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1746 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 137 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(LE, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1752 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 138 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(NE, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1758 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 139 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(EQ, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1764 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 140 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(AND, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1770 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 141 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(OR, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1776 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 142 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(FORALL, 4, id((yyvsp[-8].sIndex)), (yyvsp[-6].nPtr), (yyvsp[-4].nPtr), (yyvsp[-1].nPtr)); }
#line 1782 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 143 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(FORALL, 4, idString((yyvsp[-8].charArray)), (yyvsp[-6].nPtr), (yyvsp[-4].nPtr), (yyvsp[-1].nPtr)); }
#line 1788 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 144 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(EXISTS, 4, id((yyvsp[-8].sIndex)), (yyvsp[-6].nPtr), (yyvsp[-4].nPtr), (yyvsp[-1].nPtr)); }
#line 1794 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 145 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = opr(EXISTS, 4, idString((yyvsp[-8].charArray)), (yyvsp[-6].nPtr), (yyvsp[-4].nPtr), (yyvsp[-1].nPtr)); }
#line 1800 "seqhistory.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 146 "seqhistory.y" /* yacc.c:1646  */
    { (yyval.nPtr) = (yyvsp[-1].nPtr); }
#line 1806 "seqhistory.tab.c" /* yacc.c:1646  */
    break;


#line 1810 "seqhistory.tab.c" /* yacc.c:1646  */
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
#line 150 "seqhistory.y" /* yacc.c:1906  */


nodeType *con(int value) {
    nodeType *p;

    /* allocate node */
    if ((p = (nodeType*) malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeCon;
    p->con.value = value;

	/* copy information to con64 */
    p->con64.value = (uint64_t) value;

    return p;
}

nodeType *con64(uint64_t value) {
    nodeType *p;

    /* allocate node */
    if ((p = (nodeType*) malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeCon64;
    p->con64.value = value;
    //fprintf(pFile, "%lu ", p->con64.value); 
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
       
    std::queue<uint64_t> queue;
    q = &queue;
    
    std::stack<uint64_t> stack;  
    s = &stack; 

	std::map<uint64_t,uint64_t> map;
	m = &map;

	std::deque<uint64_t> deque; 
	dq = &deque;
	
	std::priority_queue<uint64_t, std::vector<uint64_t>, std::greater<uint64_t> > priorityqueue_min;
	pq_min = &priorityqueue_min;
    
	pFile = fopen("LCDC/SEQ_HISTORY/output.txt", "a");

	//pFile = fopen("example.txt", "a");     
  
    yyparse();

	fprintf(pFile, "\n");

	fclose(pFile);
	
    return 0;
}

int ex(nodeType *p) {

	int result;
	
	uint64_t result64;

	std::pair<std::map<uint64_t,uint64_t>::iterator,bool> got;
	std::map<uint64_t,uint64_t>::iterator it;
    
    if (!p) return 0;
    switch(p->type) {
    case typeCon:       return p->con.value; //fprintf(pFile, "%d ", p->con.value); 
	case typeCon64:     return 0;  //Need to directly access this parameter since it is type uint64_t //fprintf(pFile, "%lu ", p->con64.value); 
    case typeId:        return sym[p->id.i].value;
    case typeIdString:  return sym[p->id.i].value;
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
        case ENQUEUE:   fprintf(pFile, "0 "); q->push(p->opr.op[0]->con64.value); return 0;
        case DEQUEUE:   if(!q->empty()) 
						{ 
							result64 = q->front(); 
							q->pop(); 
						} else {
							result64 = 0;
						}
						fprintf(pFile, "%lu ", result64); 
						return result64;
        case PUSH:      fprintf(pFile, "0 "); s->push(p->opr.op[0]->con64.value); return 0; //fprintf(pFile, "%lu ", p->opr.op[0]->con64.value);
        case POP:       if(!s->empty())
                        {
                            result64 = s->top();
                            s->pop();                         
                        } else {
                            result64 = 0;                      
                        }
                        fprintf(pFile, "%lu ", result64);
                        return result64; //result = s->top(); s->pop(); fprintf(pFile, "%lu ", result); return result;
		case PUT: 		got = m->insert(std::pair<uint64_t,uint64_t>(p->opr.op[0]->con64.value, p->opr.op[1]->con64.value)); 
						//m->insert(std::make_pair(p->opr.op[0]->con64.value, p->opr.op[1]->con64.value));  
					
						if(got.second == false)
						{
							result64 = got.first->second;
						} else {
							result64 = 0;
						}
						fprintf(pFile, "%lu ", result64); 
						return 0; 
		case GET:		it = m->find(p->opr.op[0]->con64.value);
		                if(it != m->end())
		                {
		                    result64 = it->second;
		                } else {
		                    result64 = 0;
		                }
		                fprintf(pFile, "%lu ", result64); 
		                return 0;
		case REMOVE:	it = m->find(p->opr.op[0]->con64.value);
		                if(it != m->end())
		                {
		                    result64 = it->second;
		                    m->erase(it);
		                } else {
		                    result64 = 0;
		                }
		                fprintf(pFile, "%lu ", result64); 
		                return 0;
		case PUSHBACK:	fprintf(pFile, "0 "); dq->push_back(p->opr.op[0]->con64.value); return 0; //fprintf(pFile, "%lu ", p->opr.op[0]->con64.value);
		case POPBACK:	if(!dq->empty())
                        {
                            result64 = dq->back();
                            dq->pop_back();                         
                        } else {
							//result64 = 0;
                            result64 = EMPTY;                      
                        }
                        fprintf(pFile, "%lu ", result64);
                        return result64; //result = s->top(); s->pop(); fprintf(pFile, "%lu ", result); return result;
		case POPFRONT:	if(!dq->empty())
                        {
                            result64 = dq->front();
                            dq->pop_front();                         
                        } else {
							//result64 = 0;
                            result64 = EMPTY;                      
                        }
                        fprintf(pFile, "%lu ", result64);
                        return result64; //result = s->top(); s->pop(); fprintf(pFile, "%lu ", result); return result;
		case PUSHFRONT: fprintf(pFile, "0 "); dq->push_front(p->opr.op[0]->con64.value); return 0; //fprintf(pFile, "%lu ", p->opr.op[0]->con64.value);
		case INSERT:    fprintf(pFile, "0 "); pq_min->push(ex(p->opr.op[0])); return 0;
		case DELETEMIN: if(!pq_min->empty())
                        {
                            result64 = pq_min->top();
                            pq_min->pop();                         
                        } else {
							result64 = 0;
                            //result64 = EMPTY;                      
                        }
                        fprintf(pFile, "%lu ", result64);	
                        return result64;	
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



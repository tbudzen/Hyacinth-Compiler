/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */


#include "stdio.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <memory>
#include <vector>
#include <sstream>
#include <fstream>

#include "codeGenerator.hpp"

std::stringstream ss;
CodeGenerator * codeGen = NULL;
int compilationErrorCount = 0;
Value * v;

int yylex();
int yyparse();
void yyerror(char const *s);

extern FILE *yyin;
extern int yylineno;
extern char * yytext;




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
   by #include "parser.tab.h".  */
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
    T_DECLARE = 258,
    T_BEGIN = 259,
    T_END = 260,
    T_PLUS = 261,
    T_MINUS = 262,
    T_TIMES = 263,
    T_DIV = 264,
    T_MOD = 265,
    T_EQ = 266,
    T_NEQ = 267,
    T_LE = 268,
    T_GE = 269,
    T_LEQ = 270,
    T_GEQ = 271,
    T_ASSIGN = 272,
    T_IF = 273,
    T_THEN = 274,
    T_ELSE = 275,
    T_ENDIF = 276,
    T_WHILE = 277,
    T_DO = 278,
    T_ENDWHILE = 279,
    T_ENDDO = 280,
    T_FOR = 281,
    T_FROM = 282,
    T_TO = 283,
    T_DOWNTO = 284,
    T_ENDFOR = 285,
    T_READ = 286,
    T_WRITE = 287,
    T_COMMA = 288,
    T_SEMICOLON = 289,
    T_COLON = 290,
    T_LEFT_BRACKET = 291,
    T_RIGHT_BRACKET = 292,
    numberValue = 293,
    pidentifier = 294
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union 
sem_rec
 YYSTYPE;
union 
sem_rec

{


    std::string * pidentifier;
    long long numberValue;
    void * value; // Value pointer


};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */



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
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   199

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  47
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  111

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

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
      35,    36,    37,    38,    39
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    67,    67,    74,    66,    82,    81,    93,    98,   103,
     108,   112,   116,   119,   124,   140,   137,   156,   153,   162,
     166,   161,   173,   172,   183,   182,   294,   293,   403,   419,
     427,   433,   448,   475,   502,   532,   620,   684,   700,   717,
     733,   749,   766,   785,   790,   796,   801,   806
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_DECLARE", "T_BEGIN", "T_END",
  "T_PLUS", "T_MINUS", "T_TIMES", "T_DIV", "T_MOD", "T_EQ", "T_NEQ",
  "T_LE", "T_GE", "T_LEQ", "T_GEQ", "T_ASSIGN", "T_IF", "T_THEN", "T_ELSE",
  "T_ENDIF", "T_WHILE", "T_DO", "T_ENDWHILE", "T_ENDDO", "T_FOR", "T_FROM",
  "T_TO", "T_DOWNTO", "T_ENDFOR", "T_READ", "T_WRITE", "T_COMMA",
  "T_SEMICOLON", "T_COLON", "T_LEFT_BRACKET", "T_RIGHT_BRACKET",
  "numberValue", "pidentifier", "$accept", "program", "$@1", "$@2", "$@3",
  "declarations", "commands", "command", "$@4", "$@5", "$@6", "$@7", "$@8",
  "$@9", "$@10", "expression", "condition", "value", "identifier", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
# endif

#define YYPACT_NINF -34

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-34)))

#define YYTABLE_NINF -31

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      10,   -34,   -34,     4,   -33,   144,   -34,   -27,     3,   -21,
     -34,   -34,   -20,   -16,   -21,    -4,    -2,   -34,    17,   -23,
     -34,     1,   -34,    19,   177,   -34,   -21,   144,    23,     9,
      25,   -13,   -34,   -34,    16,    27,   144,    28,   144,   -21,
     -21,   -21,   -21,   -21,   -21,    38,   155,   -21,   -34,   -34,
      30,    31,    29,    37,   189,    34,    51,    40,    26,   -34,
     -34,   -34,   -34,   -34,   -34,   144,   -21,    -1,   -34,   -34,
     -34,   -21,   -21,   -21,   -21,   -21,    44,   -34,    50,   -34,
      54,   144,    61,   -21,   -21,   -34,   -34,   -34,   -34,   -34,
     -34,    53,   144,   -34,    65,   -34,    69,    72,    56,    97,
     -34,   -34,   -34,   -34,   -34,   144,   144,   108,   133,   -34,
     -34
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     2,     5,     0,    11,     0,     1,     7,     0,     0,
      19,    22,     0,     0,     0,    45,     0,    13,     0,     0,
       3,     0,    43,     0,     0,    44,     0,     0,     0,     0,
       0,     0,     6,    12,     0,     0,     0,     9,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    28,    29,
       0,     0,    43,     0,    31,     0,     0,     0,    17,    37,
      38,    39,    40,    41,    42,     0,     0,     0,    47,    46,
      14,     0,     0,     0,     0,     0,     0,     4,     0,    15,
       0,    20,     0,     0,     0,    32,    33,    34,    36,    35,
       8,     0,     0,    18,     0,    23,     0,     0,     0,     0,
      21,    24,    26,    10,    16,     0,     0,     0,     0,    25,
      27
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -34,   -34,   -34,   -34,   -34,   -34,   -26,   -11,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -24,    70,    -5
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,    36,     5,     8,    16,    17,    92,    80,
      26,    94,    27,   105,   106,    53,    23,    24,    25
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      18,    46,    45,    32,     6,    33,     7,    20,    29,    19,
      56,    18,    58,     1,     2,    35,     9,    22,    15,    28,
      10,    11,    18,    15,    12,    50,    51,    83,    84,    13,
      14,    18,    31,    18,    34,    33,    21,    15,    38,    81,
      37,    18,    82,    48,     9,    33,    79,    33,    10,    11,
      47,    18,    12,    18,    52,    15,    77,    13,    14,    49,
      18,    65,    55,   -30,    57,    15,    99,    68,    69,     9,
      33,    70,    76,    10,    11,    93,    18,    12,    78,   107,
     108,    90,    13,    14,    30,    91,    95,    18,    33,   100,
      15,    98,   101,   103,    18,   102,    33,    33,     0,     0,
      18,    18,    18,    18,    54,     0,     0,     0,     0,    59,
      60,    61,    62,    63,    64,     9,     0,    67,   104,    10,
      11,     0,     0,    12,     0,     0,     9,     0,    13,    14,
      10,    11,     0,     0,    12,     0,    15,     0,   109,    13,
      14,    85,    86,    87,    88,    89,     0,    15,     0,     0,
       0,     9,     0,    96,    97,    10,    11,     0,     0,    12,
       0,     0,     9,   110,    13,    14,    10,    11,     0,     0,
      12,     0,    15,     9,     0,    13,    14,    66,    11,     0,
       0,    12,     0,    15,     0,     0,    13,    14,    39,    40,
      41,    42,    43,    44,    15,    71,    72,    73,    74,    75
};

static const yytype_int8 yycheck[] =
{
       5,    27,    26,     5,     0,    16,    39,     4,    13,    36,
      36,    16,    38,     3,     4,    38,    18,    38,    39,    39,
      22,    23,    27,    39,    26,    38,    39,    28,    29,    31,
      32,    36,    36,    38,    17,    46,    33,    39,    19,    65,
      39,    46,    66,    34,    18,    56,    20,    58,    22,    23,
      27,    56,    26,    58,    38,    39,     5,    31,    32,    34,
      65,    23,    35,    34,    36,    39,    92,    37,    37,    18,
      81,    34,    38,    22,    23,    21,    81,    26,    38,   105,
     106,    37,    31,    32,    14,    35,    25,    92,    99,    24,
      39,    38,    23,    37,    99,    23,   107,   108,    -1,    -1,
     105,   106,   107,   108,    34,    -1,    -1,    -1,    -1,    39,
      40,    41,    42,    43,    44,    18,    -1,    47,    21,    22,
      23,    -1,    -1,    26,    -1,    -1,    18,    -1,    31,    32,
      22,    23,    -1,    -1,    26,    -1,    39,    -1,    30,    31,
      32,    71,    72,    73,    74,    75,    -1,    39,    -1,    -1,
      -1,    18,    -1,    83,    84,    22,    23,    -1,    -1,    26,
      -1,    -1,    18,    30,    31,    32,    22,    23,    -1,    -1,
      26,    -1,    39,    18,    -1,    31,    32,    22,    23,    -1,
      -1,    26,    -1,    39,    -1,    -1,    31,    32,    11,    12,
      13,    14,    15,    16,    39,     6,     7,     8,     9,    10
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,    41,    42,    44,     0,    39,    45,    18,
      22,    23,    26,    31,    32,    39,    46,    47,    58,    36,
       4,    33,    38,    56,    57,    58,    50,    52,    39,    58,
      57,    36,     5,    47,    17,    38,    43,    39,    19,    11,
      12,    13,    14,    15,    16,    56,    46,    27,    34,    34,
      38,    39,    38,    55,    57,    35,    46,    36,    46,    57,
      57,    57,    57,    57,    57,    23,    22,    57,    37,    37,
      34,     6,     7,     8,     9,    10,    38,     5,    38,    20,
      49,    46,    56,    28,    29,    57,    57,    57,    57,    57,
      37,    35,    48,    21,    51,    25,    57,    57,    38,    46,
      24,    23,    23,    37,    21,    53,    54,    46,    46,    30,
      30
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    42,    43,    41,    44,    41,    45,    45,    45,
      45,    45,    46,    46,    47,    48,    47,    49,    47,    50,
      51,    47,    52,    47,    53,    47,    54,    47,    47,    47,
      55,    55,    55,    55,    55,    55,    55,    56,    56,    56,
      56,    56,    56,    57,    57,    58,    58,    58
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     7,     0,     4,     1,     6,     3,
       8,     0,     2,     1,     4,     0,     8,     0,     6,     0,
       0,     7,     0,     6,     0,    10,     0,    10,     3,     3,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     4,     4
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

    { 
			//std::cout << "Program with declare section" << std::endl; 
		
			codeGen->compilePreparation(); 
		}

    break;

  case 3:

    {}

    break;

  case 4:

    {	
			codeGen->pushCode(HALT);	
		}

    break;

  case 5:

    {
       		codeGen->compilePreparation();
       	}

    break;

  case 6:

    {	
			codeGen->pushCode(HALT);	
		}

    break;

  case 7:

    {
			v = codeGen->newVariable((yyvsp[0].pidentifier)->c_str());
		}

    break;

  case 8:

    {
			v = codeGen->newArray((yyvsp[-5].pidentifier)->c_str(), (yyvsp[-3].numberValue), (yyvsp[-1].numberValue));
		}

    break;

  case 9:

    {
			v = codeGen->newVariable((yyvsp[0].pidentifier)->c_str());
		}

    break;

  case 10:

    {
			v = codeGen->newArray((yyvsp[-5].pidentifier)->c_str(), (yyvsp[-3].numberValue), (yyvsp[-1].numberValue));
		}

    break;

  case 12:

    {}

    break;

  case 13:

    {}

    break;

  case 14:

    { 				
			if (codeGen->isArrayElement((Value *)(yyvsp[-3].value)))
			{
				codeGen->compileArrayElementWithStore((Value *)(yyvsp[-3].value), ss.str());
			}
			else
			{
				((Value *)(yyvsp[-3].value))->initialized = true;
				codeGen->pushCode(STORE, ((Value *)(yyvsp[-3].value))->startAddress);
			}
		}

    break;

  case 15:

    { 
			// Jump Endif at first before Else commands
			codeGen->pushCode(JUMP, -1);
			codeGen->popAndSetLabel(codeGen->getCurrentCodeAddr() + 1);
			
			codeGen->pushLabel(codeGen->getCurrentCodeAddr()); // After pop
		}

    break;

  case 16:

    {
			codeGen->popAndSetLabel(codeGen->getCurrentCodeAddr() + 1);
		}

    break;

  case 17:

    { 
			codeGen->popAndSetLabel(codeGen->getCurrentCodeAddr() + 1);
		}

    break;

  case 19:

    {
		codeGen->pushLabel(codeGen->getCurrentCodeAddr());
	}

    break;

  case 20:

    { 
			codeGen->popAndSetLabel(codeGen->getCurrentCodeAddr() + 2); // From condition
			codeGen->pushCode(JUMP, codeGen->popLabel() + 1);
		}

    break;

  case 22:

    {
		codeGen->pushLabel(codeGen->getCurrentCodeAddr());
	}

    break;

  case 23:

    { 
			codeGen->popAndSetLabel(codeGen->getCurrentCodeAddr() + 2); // From condition
			codeGen->pushCode(JUMP, codeGen->popLabel() + 1);
		}

    break;

  case 24:

    {			
			/*
				FOR I = Va TO Vb DO Cmds ENDFOR
			
				LOAD Va // $4
				STORE I
				
				LOAD Vb // $6, Must NOT be calculated dynamically
				STORE tempReg
				
			Loop:
				
				LOAD I
				SUB tempReg
				STORE I
				
				JPOS EndFor
				
				... Cmds
				
				LOAD I
				INC
				STORE I
				
				JUMP Loop
				
			EndFor:
				HALT		
			*/
				
			long long regB;
							
			regB = codeGen->allocRegister();		
			
			// LOAD A
					
			codeGen->compileValueToPn((Value*)(yyvsp[-3].value), 0, "Kompilacja FOR FROM TO");
			
			// STORE I
			
			Value * va;
			va = codeGen->getVariable((yyvsp[-5].pidentifier)->c_str(), true);
			va->initialized = true;
			
			codeGen->pushCode(STORE, va->startAddress);
				
			// LOAD B
			
			codeGen->compileValueToPn((Value*)(yyvsp[-1].value), 0, "");
			
			// STORE tmpB
			
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regB));
			
			((Value *)(yyvsp[-1].value))->regForB = regB;
			
		// Loop:	
			
			codeGen->pushLabel(codeGen->getCurrentCodeAddr());
			
			// LOAD I
			
			codeGen->pushCode(LOAD, va->startAddress);
			
			// SUB tmpB
			
			codeGen->pushCode(SUB, codeGen->REG_ADDR(regB));
			
			// JPOS EndFor			
						
			codeGen->pushCode(JPOS, -1, "");
			
			codeGen->pushLabel(codeGen->getCurrentCodeAddr());		
		}

    break;

  case 25:

    {				
			/*
				LOAD I
				INC
				STORE I
				JUMP Loop
			EndFor:
			*/
			
			Value * va;
			va = codeGen->getVariable((yyvsp[-8].pidentifier)->c_str());
			
			codeGen->pushCode(LOAD, va->startAddress);
			codeGen->pushCode(INC);
			codeGen->pushCode(STORE, va->startAddress);
					
			// Backpatch JPOS EndFor
			// Simply top of labels stack	
				
			codeGen->popAndSetLabel(codeGen->getCurrentCodeAddr() + 2);
			
			// JUMP Loop
			
			codeGen->pushCode(JUMP, codeGen->popLabel() + 1);
					
			codeGen->freeRegister(((Value*)(yyvsp[-4].value))->regForB);	
			
			// Remove idx variable - see error8.txt problem
			
			codeGen->removeVariable((yyvsp[-8].pidentifier)->c_str());	
	}

    break;

  case 26:

    { 			
			/*
				FOR I = Va TO Vb DO Cmds ENDFOR
			
				LOAD Va // $4
				STORE I
			
				LOAD Vb // $6, Must NOT be calculated dynamically
				STORE tempReg
				
			Loop:
				
				LOAD I
				SUB tempReg
				STORE I
				
				JNEG EndFor
				
				... Cmds
				
				LOAD I
				DEC
				STORE I
				
				JUMP Loop
				
			EndFor:
				HALT		
			*/
			
			long long regB;
					
			regB = codeGen->allocRegister();		
					
			// LOAD A
					
			codeGen->compileValueToPn((Value*)(yyvsp[-3].value), 0, "Kompilacja FOR FROM DOWNTO");
			
			// STORE I
			
			Value * va;
			
			va = codeGen->getVariable((yyvsp[-5].pidentifier)->c_str(), true);
			va->initialized = true;
			codeGen->pushCode(STORE, va->startAddress, "<--");
			
			// LOAD B
			
			codeGen->compileValueToPn((Value*)(yyvsp[-1].value), 0, "");
			
			// STORE regB
			
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regB));
			
			((Value*)(yyvsp[-1].value))->regForB = regB;
			
			
		// Loop:	
			
			codeGen->pushLabel(codeGen->getCurrentCodeAddr());
			
			// LOAD I
			
			codeGen->pushCode(LOAD, va->startAddress);
			
			// SUB tmpB
			
			codeGen->pushCode(SUB, codeGen->REG_ADDR(regB));
			
			// JNEG EndFor			
						
			codeGen->pushCode(JNEG, -1, "");
				codeGen->pushLabel(codeGen->getCurrentCodeAddr());
							
		}

    break;

  case 27:

    {		
			/*
				LOAD I
				DEC
				STORE I
				JUMP Loop
			EndFor:
			*/
				
			Value * vi;
				
			vi = codeGen->getVariable((yyvsp[-8].pidentifier)->c_str());
			
			codeGen->pushCode(LOAD, vi->startAddress);
			codeGen->pushCode(DEC);
			codeGen->pushCode(STORE, vi->startAddress);
					
			// Backpatch JNEG EndFor
			// Simply top of labels stack	
				
			codeGen->popAndSetLabel(codeGen->getCurrentCodeAddr() + 2);
			
			// JUMP Loop
			
			codeGen->pushCode(JUMP, codeGen->popLabel() + 1);		
			
			codeGen->freeRegister(((Value*)(yyvsp[-4].value))->regForB);	
			
			// Remove idx variable - see error8.txt problem
			
			codeGen->removeVariable((yyvsp[-8].pidentifier)->c_str());				
		}

    break;

  case 28:

    { 			
			codeGen->pushCode(GET, "");
			
			if (codeGen->isArrayElement((Value *)(yyvsp[-1].value)))
			{
				codeGen->compileArrayElementWithStore((Value *)(yyvsp[-1].value), ss.str());
			}
			else
			{
				v = codeGen->getVariable(((Value *)(yyvsp[-1].value))->name.c_str());
				v->initialized = true;
				codeGen->pushCode(STORE, v->startAddress);
			}
		}

    break;

  case 29:

    { 
			codeGen->compileValueToPn((Value *)(yyvsp[-1].value), 0, "");
			codeGen->pushCode(PUT);
		}

    break;

  case 30:

    {
			v = codeGen->getConst((yyvsp[0].numberValue));
			codeGen->pushCode(LOAD, v->startAddress);
		}

    break;

  case 31:

    {
			if (codeGen->isArrayElement((Value *)(yyvsp[0].value)))
			{
				codeGen->compileArrayElementToPn((Value *)(yyvsp[0].value), 0, "");
			}
			else
			{
				//v = codeGen->getVariable(((Value*)$1)->name.c_str());
				//codeGen->pushCode(LOAD, v->startAddress);
				
				codeGen->compileValueToPn(codeGen->getVariable(((Value*)(yyvsp[0].value))->name.c_str()), 0, "");
			}
		}

    break;

  case 32:

    {
			long long REG_A = codeGen->allocRegister();
			if (codeGen->isArrayElement((Value *)(yyvsp[-2].value)))
			{
				codeGen->compileArrayElementToPn((Value *)(yyvsp[-2].value), 0, "Compilation of first array element of PLUS");
			}
			else
			{
				codeGen->pushCode(LOAD, ((Value *)(yyvsp[-2].value))->startAddress, "Compilation of first normal value of PLUS");
			}
			codeGen->pushCode(STORE, codeGen->REG_ADDR(REG_A));
			
			if (codeGen->isArrayElement((Value *)(yyvsp[0].value)))
			{
				codeGen->compileArrayElementToPn((Value *)(yyvsp[0].value), 0, "Compilation of second array element of PLUS");
			}
			else
			{
				codeGen->pushCode(LOAD, ((Value *)(yyvsp[0].value))->startAddress, "Compilation of second normal value of PLUS");
			}
			
			codeGen->pushCode(ADD, codeGen->REG_ADDR(REG_A));
			
			codeGen->freeRegister(REG_A);
		}

    break;

  case 33:

    {
			long long REG_A = codeGen->allocRegister();
			if (codeGen->isArrayElement((Value *)(yyvsp[0].value)))
			{
				codeGen->compileArrayElementToPn((Value *)(yyvsp[0].value), codeGen->REG_ADDR(REG_A), "Compilation of second array element of MINUS");
			}
			else
			{
				codeGen->pushCode(LOAD, ((Value *)(yyvsp[0].value))->startAddress, "Compilation of second normal value of MINUS");
				codeGen->pushCode(STORE, codeGen->REG_ADDR(REG_A));
			}
			
			if (codeGen->isArrayElement((Value *)(yyvsp[-2].value)))
			{
				codeGen->compileArrayElementToPn((Value *)(yyvsp[-2].value), 0, "Compilation of first array element of MINUS");
			}
			else
			{
				codeGen->pushCode(LOAD, ((Value *)(yyvsp[-2].value))->startAddress, "Compilation of first normal value of MINUS");
			}
			
			codeGen->pushCode(SUB, codeGen->REG_ADDR(REG_A));
			
			codeGen->freeRegister(REG_A);
		}

    break;

  case 34:

    {			
			long long regN, regM, regAns;
			
			regN 	= codeGen->allocRegister();
			regM 	= codeGen->allocRegister();
			regAns 	= codeGen->allocRegister();		
			
			// regN = n
		
			codeGen->compileValueToPn((Value *) (yyvsp[-2].value), 0, "regN = n");
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regN));
			
			// regM = m
		
			codeGen->compileValueToPn((Value *) (yyvsp[0].value), 0, "regM = m");
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regM));
	
			// Multiplication
	
			codeGen->compileMul(regN, regM, regAns); // <<<<<<<<<<<<<<<<<<<<<
			codeGen->pushCode(LOAD, codeGen->REG_ADDR(regAns));
			
			// Cleanup
			
			codeGen->freeRegister(regN);
			codeGen->freeRegister(regM);	
			codeGen->freeRegister(regAns);		
		}

    break;

  case 35:

    {
			/*
			
				(dividend -7/ divisor 3) => quotient -2
				-2 * 3 => -6
				so a%b => -1
				
				(7/-3) => -2
				-2 * -3 => 6
				so a%b => 1
				
				(-7/-3) => 2
				2 * -3 => -6
				so a%b => -1
			
			*/
			
			long long 
				regDividend, regDividend0, regDivisor, regDivisor0, regAns, regDivisorMulQuotient;		
		
			regDividend = codeGen->allocRegister();
			regDividend0 = codeGen->allocRegister();
			regDivisor = codeGen->allocRegister();
			regDivisor0 = codeGen->allocRegister();
			regAns = codeGen->allocRegister();
			regDivisorMulQuotient = codeGen->allocRegister();
		
			// regDividend = n

			codeGen->compileValueToPn((Value *) (yyvsp[-2].value), 0, "regDividend = n");
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regDividend));
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regDividend0));		
			
			// regDivisor = m

			codeGen->compileValueToPn((Value *) (yyvsp[0].value), 0, "regDivisor = m");
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regDivisor));
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regDivisor0));
						
			// If regDivisor == 0 return 0;
			
			codeGen->pushCode(JZERO, codeGen->getCurrentCodeAddr() + 3);
			codeGen->pushCode(JUMP, codeGen->getCurrentCodeAddr() + 5);
			
			codeGen->pushCode(SUB, 0);
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regAns));
			codeGen->pushCode(JUMP, -1);
				codeGen->pushLabel(codeGen->getCurrentCodeAddr());
						
			// Division
			
			codeGen->compileDiv(regDividend, regDivisor, regAns);
			//codeGen->pushCode(LOAD, codeGen->REG_ADDR(regDividend0));
			//codeGen->pushCode(PUT);
			//codeGen->pushCode(LOAD, codeGen->REG_ADDR(regDivisor0));
			//codeGen->pushCode(PUT);
			
			// Multiplication
			
			codeGen->compileMul(regDivisor0, regAns, regDivisorMulQuotient);
			//codeGen->pushCode(PUT);
			
			//codeGen->pushCode(LOAD, codeGen->REG_ADDR(regDivisor0));
			//codeGen->pushCode(PUT);
			//codeGen->pushCode(LOAD, codeGen->REG_ADDR(regDivisorMulQuotient));
			//codeGen->pushCode(PUT);
			
			// Subtraction, 
			// Mod is dividend (-33) - divisor (7) * quotient (-5) = 2
			// Mod is dividend (33) - divisor (-7) * quotient (-5) = -2			
			
			codeGen->pushCode(LOAD, codeGen->REG_ADDR(regDividend0));
			codeGen->pushCode(SUB, codeGen->REG_ADDR(regDivisorMulQuotient));
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regAns));
			
				codeGen->popAndSetLabel(codeGen->getCurrentCodeAddr());
			
			// Cleanup
			
			codeGen->freeRegister(regDividend);
			codeGen->freeRegister(regDivisor);
			codeGen->freeRegister(regDividend0);
			codeGen->freeRegister(regDivisor0);
			codeGen->freeRegister(regAns);
			codeGen->freeRegister(regDivisorMulQuotient);							
		}

    break;

  case 36:

    {
			/*
				// Function to divide a by b and 
				// return floor value it 
				int divide(long long dividend, long long divisor) { 
				  
				  // Calculate sign of divisor i.e., 
				  // sign will be negative only iff 
				  // either one of them is negative 
				  // otherwise it will be positive 
				  int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1; 
				  
				  // remove sign of operands 
				  dividend = abs(dividend); 
				  divisor = abs(divisor); 
				  
				  // Initialize the quotient 
				  long long quotient = 0, temp = 0; 
				  
				  // test down from the highest bit and 
				  // accumulate the tentative value for 
				  // valid bit 
				  for (int i = 31; i >= 0; --i) { 
				  
				    if (temp + (divisor << i) <= dividend) { 
				      temp += divisor << i; 
				      quotient |= 1LL << i; 
				    } 
				  } 
				  
				  return sign * quotient; 
				} 
			*/

			long long regDividend, regDivisor, regAns;
			
			regDividend = codeGen->allocRegister();
			regDivisor = codeGen->allocRegister();
			regAns = codeGen->allocRegister();

			// regDividend = n

			codeGen->compileValueToPn((Value *) (yyvsp[-2].value), 0, "regDividend = n");
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regDividend));		
			
			// regDivisor = m

			codeGen->compileValueToPn((Value *) (yyvsp[0].value), 0, "regDivisor = m");
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regDivisor));	
			
			// Division
			
			codeGen->compileDiv(regDividend, regDivisor, regAns);
			
			// Cleanup
			
			codeGen->freeRegister(regDividend);
			codeGen->freeRegister(regDivisor);
			codeGen->freeRegister(regAns);
		}

    break;

  case 37:

    {		
		long long reg = codeGen->allocRegister();
		
		codeGen->compileValueToPn((Value*)(yyvsp[0].value), reg, "CONDITION EQ");		
		codeGen->compileValueToPn((Value*)(yyvsp[-2].value), 0, "");
		
		codeGen->pushCode(SUB, codeGen->REG_ADDR(reg));
		codeGen->pushCode(JZERO, codeGen->getCurrentCodeAddr() + 3); // Ommit next JUMP
			
		codeGen->pushCode(JUMP, -1);
		codeGen->pushLabel(codeGen->getCurrentCodeAddr());
		
		codeGen->freeRegister(reg);
	}

    break;

  case 38:

    {
		long long reg = codeGen->allocRegister();
		
		codeGen->compileValueToPn((Value*)(yyvsp[0].value), reg, "CONDITION NEQ");		
		codeGen->compileValueToPn((Value*)(yyvsp[-2].value), 0, "");
		
		codeGen->pushCode(SUB, codeGen->REG_ADDR(reg));
		codeGen->pushCode(JPOS, codeGen->getCurrentCodeAddr() + 4); // Ommit next JUMP
		codeGen->pushCode(JNEG, codeGen->getCurrentCodeAddr() + 3); // Ommit next JUMP
			
		codeGen->pushCode(JUMP, -1);
		codeGen->pushLabel(codeGen->getCurrentCodeAddr());
		
		codeGen->freeRegister(reg);
	}

    break;

  case 39:

    {
		long long reg = codeGen->allocRegister();
			
		codeGen->compileValueToPn((Value*)(yyvsp[0].value), reg, "CONDITION LE");	
		codeGen->compileValueToPn((Value*)(yyvsp[-2].value), 0, "");
		
		codeGen->pushCode(SUB, codeGen->REG_ADDR(reg));
		codeGen->pushCode(JNEG, codeGen->getCurrentCodeAddr() + 3); // Ommit next JUMP
			
		codeGen->pushCode(JUMP, -1);
		codeGen->pushLabel(codeGen->getCurrentCodeAddr());
		
		codeGen->freeRegister(reg);
	}

    break;

  case 40:

    {
		long long reg = codeGen->allocRegister();
			
		codeGen->compileValueToPn((Value*)(yyvsp[0].value), reg, "CONDITION GE");	
		codeGen->compileValueToPn((Value*)(yyvsp[-2].value), 0, "");
		
		codeGen->pushCode(SUB, codeGen->REG_ADDR(reg));
		codeGen->pushCode(JPOS, codeGen->getCurrentCodeAddr() + 3); // Ommit next JUMP
			
		codeGen->pushCode(JUMP, -1);
		codeGen->pushLabel(codeGen->getCurrentCodeAddr());
		
		codeGen->freeRegister(reg);
	}

    break;

  case 41:

    {
		long long reg = codeGen->allocRegister();
			
		codeGen->compileValueToPn((Value*)(yyvsp[0].value), reg, "CONDITION LEQ");	
		codeGen->compileValueToPn((Value*)(yyvsp[-2].value), 0, "");
		
		codeGen->pushCode(SUB, codeGen->REG_ADDR(reg));
		codeGen->pushCode(JNEG, codeGen->getCurrentCodeAddr() + 4); // Ommit next JUMP
		codeGen->pushCode(JZERO, codeGen->getCurrentCodeAddr() + 3); // Ommit next JUMP
			
		codeGen->pushCode(JUMP, -1);
		codeGen->pushLabel(codeGen->getCurrentCodeAddr());
		
		codeGen->freeRegister(reg);
	}

    break;

  case 42:

    {
		long long reg = codeGen->allocRegister();
			
		codeGen->compileValueToPn((Value*)(yyvsp[0].value), reg, "CONDITION GEQ");	
		codeGen->compileValueToPn((Value*)(yyvsp[-2].value), 0, "");
		
		codeGen->pushCode(SUB, codeGen->REG_ADDR(reg));
		codeGen->pushCode(JPOS, codeGen->getCurrentCodeAddr() + 4); // Ommit next JUMP
		codeGen->pushCode(JZERO, codeGen->getCurrentCodeAddr() + 3); // Ommit next JUMP
			
		codeGen->pushCode(JUMP, -1);
		codeGen->pushLabel(codeGen->getCurrentCodeAddr());
		
		codeGen->freeRegister(reg);
	}

    break;

  case 43:

    {
			(yyval.value) = codeGen->getConst((yyvsp[0].numberValue));
		}

    break;

  case 44:

    {
		}

    break;

  case 45:

    {
			(yyval.value) = codeGen->getVariable((yyvsp[0].pidentifier)->c_str());
		}

    break;

  case 46:

    {
			(yyval.value) = codeGen->getArrayNamedElement((yyvsp[-3].pidentifier)->c_str(), (yyvsp[-1].pidentifier)->c_str());
		}

    break;

  case 47:

    {
			(yyval.value) = codeGen->getArrayIndexedElement((yyvsp[-3].pidentifier)->c_str(), (yyvsp[-1].numberValue));
		}

    break;



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



int main(int argc, char ** argv)
{
	bool error = false;
	char * srcFilename = NULL;
	char * destFilename = NULL;

	//std::cout << "Witamy w kompilatorze Lab_4." << std::endl;

	if (argc == 3)
	{
		srcFilename = argv[1];
		destFilename = argv[2];

		FILE * fileIn;
		fileIn = fopen(srcFilename, "r");
	
		if(fileIn)
		{
	    	yyin = fileIn;

        	std::cout << "Kompilowanie \"" << srcFilename << "\" do \"" << destFilename << "\"..." << std::endl;

			codeGen = new CodeGenerator();

			try
			{
        		yyparse();        		
        	
	  			std::fstream fileOut;
	  			
	  			fileOut.open (destFilename, std::fstream::trunc | std::fstream::out);  
	 			fileOut << codeGen->getCodeText(true, false);
	  			fileOut.close();
	        	
	        	std::cout << "Kompilacja zakończona sukcesem." << std::endl;   
	        	//std::cout << "--------------------------------------------" << std::endl;       	
	        	//std::cout << codeGen->getCodeText(true, true); 
        	}
        	catch (const EVariableAlreadyDeclaredException & e)
        	{
        		error = true;
        		std::cout << "Linia " << yylineno << ": " << e.what() << std::endl;
        	}
        	catch (const EVariableNotDeclaredException & e)
        	{
        		error = true;
        		std::cout << "Linia " << yylineno << ": " << e.what() << std::endl;
        	}
        	catch (const EUnableToAllocateRegisterException & e)
        	{
        		error = true;
        		std::cout << "Linia " << yylineno << ": " << e.what() << std::endl;
        	}      
        	catch (const ECompileNonArrayElementException & e)
        	{
        		error = true;
        		std::cout << "Linia " << yylineno << ": " << e.what() << std::endl;
        	}  	
        	catch (const EInvalidArrayBounds & e)
        	{
        		error = true;
        		std::cout << "Linia " << yylineno << ": " << e.what() << std::endl;
        	}       	
  
        	delete codeGen;
        	
    		if (error) return -1;
        }
        else
        {	
        	std::cout << "Błąd: Nie udało się otworzyć pliku wejściowego." << std::endl;
        	
    		return -1;
        }
	}
	else
	{
		std::cout << "Błąd: Niepoprawna liczba argumentów - wymagane są dwie nazwy plików." << std::endl;
		
    	return -1;
	}

	return 0;
}


void yyerror(char const *s) 
{
		std::cout << s << " - Linia nr " << yylineno << ": " << yytext << std::endl;
        exit(0);
}

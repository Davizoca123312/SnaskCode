/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "snask_parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"        // Inclui as definições da AST
#include "snask_value.h" // Inclui os tipos de valor Snask (para literais)

// Variável externa para a raiz da AST que será construída
ASTNode* program_ast_root = NULL;

// Variável de linha do lexer (flex)
extern int yylineno;

// Função de erro do parser (bison)
void yyerror(const char *s);

// Variável para a entrada do lexer (flex)
extern FILE *yyin;

// Define a união de tipos para YYSTYPE (valores passados entre os símbolos da gramática)
// A união deve conter todos os tipos de dados que serão passados como valores semânticos.
// ASTNode* para nós da árvore, char* para nomes, long long para int, double para float, bool para booleanos.

#line 95 "snask_parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "snask_parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_MAKE = 3,                       /* MAKE  */
  YYSYMBOL_KEEP = 4,                       /* KEEP  */
  YYSYMBOL_SET = 5,                        /* SET  */
  YYSYMBOL_ZAP = 6,                        /* ZAP  */
  YYSYMBOL_SHOO = 7,                       /* SHOO  */
  YYSYMBOL_GRAB = 8,                       /* GRAB  */
  YYSYMBOL_GRABNUM = 9,                    /* GRABNUM  */
  YYSYMBOL_GRABTXT = 10,                   /* GRABTXT  */
  YYSYMBOL_CRAFT = 11,                     /* CRAFT  */
  YYSYMBOL_BACK = 12,                      /* BACK  */
  YYSYMBOL_WHEN = 13,                      /* WHEN  */
  YYSYMBOL_WHENN = 14,                     /* WHENN  */
  YYSYMBOL_WHENEM = 15,                    /* WHENEM  */
  YYSYMBOL_SPIN = 16,                      /* SPIN  */
  YYSYMBOL_LOOPY = 17,                     /* LOOPY  */
  YYSYMBOL_BREAKY = 18,                    /* BREAKY  */
  YYSYMBOL_SKIPIT = 19,                    /* SKIPIT  */
  YYSYMBOL_PACK = 20,                      /* PACK  */
  YYSYMBOL_PACKADD = 21,                   /* PACKADD  */
  YYSYMBOL_PACKGET = 22,                   /* PACKGET  */
  YYSYMBOL_BOX = 23,                       /* BOX  */
  YYSYMBOL_BOXGET = 24,                    /* BOXGET  */
  YYSYMBOL_BOXSET = 25,                    /* BOXSET  */
  YYSYMBOL_TO = 26,                        /* TO  */
  YYSYMBOL_USE = 27,                       /* USE  */
  YYSYMBOL_IDENTIFIER = 28,                /* IDENTIFIER  */
  YYSYMBOL_INT_LITERAL = 29,               /* INT_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 30,             /* FLOAT_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 31,            /* STRING_LITERAL  */
  YYSYMBOL_BOOL_LITERAL = 32,              /* BOOL_LITERAL  */
  YYSYMBOL_NULL_LITERAL = 33,              /* NULL_LITERAL  */
  YYSYMBOL_ADD = 34,                       /* ADD  */
  YYSYMBOL_SUB = 35,                       /* SUB  */
  YYSYMBOL_MUL = 36,                       /* MUL  */
  YYSYMBOL_DIV = 37,                       /* DIV  */
  YYSYMBOL_EQ = 38,                        /* EQ  */
  YYSYMBOL_NEQ = 39,                       /* NEQ  */
  YYSYMBOL_LT = 40,                        /* LT  */
  YYSYMBOL_GT = 41,                        /* GT  */
  YYSYMBOL_LE = 42,                        /* LE  */
  YYSYMBOL_GE = 43,                        /* GE  */
  YYSYMBOL_AND = 44,                       /* AND  */
  YYSYMBOL_OR = 45,                        /* OR  */
  YYSYMBOL_NOT = 46,                       /* NOT  */
  YYSYMBOL_ASSIGN = 47,                    /* ASSIGN  */
  YYSYMBOL_SEMICOLON = 48,                 /* SEMICOLON  */
  YYSYMBOL_LPAREN = 49,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 50,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 51,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 52,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 53,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 54,                  /* RBRACKET  */
  YYSYMBOL_COMMA = 55,                     /* COMMA  */
  YYSYMBOL_DOT = 56,                       /* DOT  */
  YYSYMBOL_COLON = 57,                     /* COLON  */
  YYSYMBOL_YYACCEPT = 58,                  /* $accept  */
  YYSYMBOL_program = 59,                   /* program  */
  YYSYMBOL_statement_list = 60,            /* statement_list  */
  YYSYMBOL_statement = 61,                 /* statement  */
  YYSYMBOL_declaration = 62,               /* declaration  */
  YYSYMBOL_assignment = 63,                /* assignment  */
  YYSYMBOL_if_statement = 64,              /* if_statement  */
  YYSYMBOL_while_statement = 65,           /* while_statement  */
  YYSYMBOL_for_statement = 66,             /* for_statement  */
  YYSYMBOL_return_statement = 67,          /* return_statement  */
  YYSYMBOL_print_statement = 68,           /* print_statement  */
  YYSYMBOL_block = 69,                     /* block  */
  YYSYMBOL_function_declaration = 70,      /* function_declaration  */
  YYSYMBOL_parameter_list = 71,            /* parameter_list  */
  YYSYMBOL_function_call = 72,             /* function_call  */
  YYSYMBOL_arguments = 73,                 /* arguments  */
  YYSYMBOL_expression = 74,                /* expression  */
  YYSYMBOL_unary_expression = 75,          /* unary_expression  */
  YYSYMBOL_binary_expression = 76,         /* binary_expression  */
  YYSYMBOL_primary = 77,                   /* primary  */
  YYSYMBOL_list_literal = 78,              /* list_literal  */
  YYSYMBOL_list_elements = 79              /* list_elements  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
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
#define YYLAST   321

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  148

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   312


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    54,    54,    58,    59,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    84,    85,    89,    94,    95,    96,   100,   104,
     108,   112,   116,   120,   124,   125,   126,   130,   134,   135,
     136,   140,   141,   142,   146,   147,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   179,   183,   184,
     185
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "MAKE", "KEEP", "SET",
  "ZAP", "SHOO", "GRAB", "GRABNUM", "GRABTXT", "CRAFT", "BACK", "WHEN",
  "WHENN", "WHENEM", "SPIN", "LOOPY", "BREAKY", "SKIPIT", "PACK",
  "PACKADD", "PACKGET", "BOX", "BOXGET", "BOXSET", "TO", "USE",
  "IDENTIFIER", "INT_LITERAL", "FLOAT_LITERAL", "STRING_LITERAL",
  "BOOL_LITERAL", "NULL_LITERAL", "ADD", "SUB", "MUL", "DIV", "EQ", "NEQ",
  "LT", "GT", "LE", "GE", "AND", "OR", "NOT", "ASSIGN", "SEMICOLON",
  "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "COMMA",
  "DOT", "COLON", "$accept", "program", "statement_list", "statement",
  "declaration", "assignment", "if_statement", "while_statement",
  "for_statement", "return_statement", "print_statement", "block",
  "function_declaration", "parameter_list", "function_call", "arguments",
  "expression", "unary_expression", "binary_expression", "primary",
  "list_literal", "list_elements", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-87)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -87,    18,   132,   -87,     0,    13,    19,    -6,    20,    24,
      25,    27,    -6,    -3,     8,    14,    16,    17,     7,    34,
      36,   -87,   -87,   -87,   -87,   -87,    -6,    -6,    -6,   -87,
     -87,    45,    46,   -87,   -87,   -87,    52,    53,   -87,   -87,
      54,   235,   -87,   -87,   -87,   -87,    15,    56,    57,   -87,
     265,    58,    65,    68,    69,   265,    -6,    -6,    12,   -87,
     -87,    -6,    88,    -6,   -87,   -87,   150,    79,   -87,   -87,
     -87,   -87,   -87,    -6,    -6,    -6,    -6,    -6,    -6,    -6,
      -6,    -6,    -6,    -6,    -6,   -87,    -6,    -6,    -6,   -87,
     -87,   -87,    93,   167,   184,    74,   265,   -18,    75,   -44,
     265,   -87,   -87,     2,     2,   -87,   -87,   -33,   -33,    -4,
      -4,    -4,    -4,   134,   277,   265,   265,   265,   -87,   -38,
      73,    73,    -6,   -87,    -6,   -87,   -87,    -6,    73,    98,
      30,   -87,   250,   265,   265,   -87,   -87,    73,    78,    -6,
     -87,    -6,   201,   218,    73,    73,   -87,   -87
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      63,    58,    59,    60,    61,    62,     0,     0,     0,     3,
       4,     0,     0,     7,     8,     9,     0,     0,    12,    13,
      65,     0,    41,    42,    43,    66,     0,     0,     0,    65,
      31,     0,     0,     0,     0,    30,     0,     0,     0,    19,
      20,    68,     0,    38,    45,    44,     0,     0,     5,     6,
      10,    11,    14,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    15,     0,     0,     0,    16,
      17,    18,    34,     0,     0,     0,    69,     0,     0,     0,
      39,    64,    32,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    22,    23,    24,    35,     0,
       0,     0,     0,    67,     0,    21,    37,     0,     0,     0,
      25,    28,     0,    70,    40,    33,    36,     0,     0,     0,
      26,     0,     0,     0,     0,     0,    29,    27
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -87,   -87,   100,   -87,    80,   -87,   -87,   -87,   -87,   -87,
     -87,   -86,   -87,   -87,    11,   -87,    -7,   -87,   -87,   -87,
     -87,   -87
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,   119,    49,    99,    41,    42,    43,    44,
      45,    97
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      50,    73,    74,    75,    76,    55,   126,    79,    80,    81,
      82,   127,   128,    40,    18,     4,     5,   129,     3,    64,
      65,    66,    20,    21,    22,    23,    24,    25,    46,    26,
      73,    74,    75,    76,   130,   131,   123,   124,    75,    76,
      27,    47,   135,    28,   137,   138,    56,    48,    51,    93,
      94,   140,    52,    53,    96,    54,   100,    57,   146,   147,
      61,    62,    86,    58,    59,    60,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,    40,   115,
     116,   117,     4,     5,     6,    63,     7,     8,     9,    10,
      11,    12,    13,    68,    69,    14,    15,    16,    17,    18,
      70,    71,    72,    87,    88,    19,    89,    20,    21,    22,
      23,    24,    25,    90,    26,   132,    91,   133,    92,    98,
     134,   118,   122,   125,    29,    27,   136,   141,    28,    67,
      29,   102,   142,     0,   143,     4,     5,     6,    95,     7,
       8,     9,    10,    11,    12,    13,     0,     0,    14,    15,
      16,    17,    18,     0,     0,     0,     0,     0,    19,     0,
      20,    21,    22,    23,    24,    25,     0,    26,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    27,     0,
       0,    28,     0,    29,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,     0,     0,     0,     0,
     101,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,     0,     0,     0,     0,   120,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
       0,     0,     0,     0,   121,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,     0,     0,     0,
       0,   144,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,     0,     0,     0,     0,   145,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,     0,     0,    85,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,     0,     0,   139,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83
};

static const yytype_int16 yycheck[] =
{
       7,    34,    35,    36,    37,    12,    50,    40,    41,    42,
      43,    55,    50,     2,    20,     3,     4,    55,     0,    26,
      27,    28,    28,    29,    30,    31,    32,    33,    28,    35,
      34,    35,    36,    37,   120,   121,    54,    55,    36,    37,
      46,    28,   128,    49,    14,    15,    49,    28,    28,    56,
      57,   137,    28,    28,    61,    28,    63,    49,   144,   145,
      53,    27,    47,    49,    48,    48,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    67,    86,
      87,    88,     3,     4,     5,    49,     7,     8,     9,    10,
      11,    12,    13,    48,    48,    16,    17,    18,    19,    20,
      48,    48,    48,    47,    47,    26,    48,    28,    29,    30,
      31,    32,    33,    48,    35,   122,    48,   124,    49,    31,
     127,    28,    48,    48,    51,    46,    28,    49,    49,    29,
      51,    52,   139,    -1,   141,     3,     4,     5,    58,     7,
       8,     9,    10,    11,    12,    13,    -1,    -1,    16,    17,
      18,    19,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,
      28,    29,    30,    31,    32,    33,    -1,    35,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    46,    -1,
      -1,    49,    -1,    51,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,
      50,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    -1,    -1,    -1,    50,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    -1,    -1,    -1,    50,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      -1,    50,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    -1,    50,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    -1,    48,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    -1,    48,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    59,    60,     0,     3,     4,     5,     7,     8,     9,
      10,    11,    12,    13,    16,    17,    18,    19,    20,    26,
      28,    29,    30,    31,    32,    33,    35,    46,    49,    51,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      72,    74,    75,    76,    77,    78,    28,    28,    28,    72,
      74,    28,    28,    28,    28,    74,    49,    49,    49,    48,
      48,    53,    27,    49,    74,    74,    74,    60,    48,    48,
      48,    48,    48,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    48,    47,    47,    47,    48,
      48,    48,    49,    74,    74,    62,    74,    79,    31,    73,
      74,    50,    52,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    28,    71,
      50,    50,    48,    54,    55,    48,    50,    55,    50,    55,
      69,    69,    74,    74,    74,    69,    28,    14,    15,    48,
      69,    49,    74,    74,    50,    50,    69,    69
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    58,    59,    60,    60,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    62,    62,    63,    64,    64,    64,    65,    66,
      67,    68,    69,    70,    71,    71,    71,    72,    73,    73,
      73,    74,    74,    74,    75,    75,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    78,    79,    79,
      79
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     2,     1,     1,     1,
       2,     2,     1,     1,     2,     2,     3,     3,     3,     2,
       2,     4,     4,     4,     4,     5,     7,    10,     5,     9,
       2,     2,     3,     6,     0,     1,     3,     4,     0,     1,
       3,     1,     1,     1,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     4,     0,     1,
       3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* program: statement_list  */
#line 54 "snask_parser.y"
                        { program_ast_root = (yyvsp[0].ast_node); }
#line 1296 "snask_parser.tab.c"
    break;

  case 3: /* statement_list: %empty  */
#line 58 "snask_parser.y"
                        { (yyval.ast_node) = ast_create_statement_list(yylineno); }
#line 1302 "snask_parser.tab.c"
    break;

  case 4: /* statement_list: statement_list statement  */
#line 59 "snask_parser.y"
                               { ast_statement_list_add((yyvsp[-1].ast_node), (yyvsp[0].ast_node)); (yyval.ast_node) = (yyvsp[-1].ast_node); }
#line 1308 "snask_parser.tab.c"
    break;

  case 5: /* statement: declaration SEMICOLON  */
#line 63 "snask_parser.y"
                                    { (yyval.ast_node) = (yyvsp[-1].ast_node); }
#line 1314 "snask_parser.tab.c"
    break;

  case 6: /* statement: assignment SEMICOLON  */
#line 64 "snask_parser.y"
                                    { (yyval.ast_node) = (yyvsp[-1].ast_node); }
#line 1320 "snask_parser.tab.c"
    break;

  case 7: /* statement: if_statement  */
#line 65 "snask_parser.y"
                                    { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1326 "snask_parser.tab.c"
    break;

  case 8: /* statement: while_statement  */
#line 66 "snask_parser.y"
                                    { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1332 "snask_parser.tab.c"
    break;

  case 9: /* statement: for_statement  */
#line 67 "snask_parser.y"
                                    { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1338 "snask_parser.tab.c"
    break;

  case 10: /* statement: return_statement SEMICOLON  */
#line 68 "snask_parser.y"
                                    { (yyval.ast_node) = (yyvsp[-1].ast_node); }
#line 1344 "snask_parser.tab.c"
    break;

  case 11: /* statement: print_statement SEMICOLON  */
#line 69 "snask_parser.y"
                                    { (yyval.ast_node) = (yyvsp[-1].ast_node); }
#line 1350 "snask_parser.tab.c"
    break;

  case 12: /* statement: block  */
#line 70 "snask_parser.y"
                                    { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1356 "snask_parser.tab.c"
    break;

  case 13: /* statement: function_declaration  */
#line 71 "snask_parser.y"
                                    { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1362 "snask_parser.tab.c"
    break;

  case 14: /* statement: function_call SEMICOLON  */
#line 72 "snask_parser.y"
                                    { (yyval.ast_node) = ast_create_expression_statement((yyvsp[-1].ast_node), yylineno); }
#line 1368 "snask_parser.tab.c"
    break;

  case 15: /* statement: expression SEMICOLON  */
#line 73 "snask_parser.y"
                                    { (yyval.ast_node) = ast_create_expression_statement((yyvsp[-1].ast_node), yylineno); }
#line 1374 "snask_parser.tab.c"
    break;

  case 16: /* statement: GRAB IDENTIFIER SEMICOLON  */
#line 74 "snask_parser.y"
                                    { (yyval.ast_node) = ast_create_grab_statement((yyvsp[-1].id_name), GRAB_TYPE_ANY, yylineno); free((yyvsp[-1].id_name)); }
#line 1380 "snask_parser.tab.c"
    break;

  case 17: /* statement: GRABNUM IDENTIFIER SEMICOLON  */
#line 75 "snask_parser.y"
                                    { (yyval.ast_node) = ast_create_grab_statement((yyvsp[-1].id_name), GRAB_TYPE_NUM, yylineno); free((yyvsp[-1].id_name)); }
#line 1386 "snask_parser.tab.c"
    break;

  case 18: /* statement: GRABTXT IDENTIFIER SEMICOLON  */
#line 76 "snask_parser.y"
                                    { (yyval.ast_node) = ast_create_grab_statement((yyvsp[-1].id_name), GRAB_TYPE_TXT, yylineno); free((yyvsp[-1].id_name)); }
#line 1392 "snask_parser.tab.c"
    break;

  case 19: /* statement: BREAKY SEMICOLON  */
#line 77 "snask_parser.y"
                                    { (yyval.ast_node) = ast_create_break_statement(yylineno); }
#line 1398 "snask_parser.tab.c"
    break;

  case 20: /* statement: SKIPIT SEMICOLON  */
#line 78 "snask_parser.y"
                                    { (yyval.ast_node) = ast_create_skip_statement(yylineno); }
#line 1404 "snask_parser.tab.c"
    break;

  case 21: /* statement: TO USE STRING_LITERAL SEMICOLON  */
#line 79 "snask_parser.y"
                                      { (yyval.ast_node) = ast_create_use_statement((yyvsp[-1].string_val), yylineno); free((yyvsp[-1].string_val)); }
#line 1410 "snask_parser.tab.c"
    break;

  case 22: /* declaration: MAKE IDENTIFIER ASSIGN expression  */
#line 84 "snask_parser.y"
                                      { (yyval.ast_node) = ast_create_var_declaration((yyvsp[-2].id_name), (yyvsp[0].ast_node), yylineno); free((yyvsp[-2].id_name)); }
#line 1416 "snask_parser.tab.c"
    break;

  case 23: /* declaration: KEEP IDENTIFIER ASSIGN expression  */
#line 85 "snask_parser.y"
                                        { (yyval.ast_node) = ast_create_const_declaration((yyvsp[-2].id_name), (yyvsp[0].ast_node), yylineno); free((yyvsp[-2].id_name)); }
#line 1422 "snask_parser.tab.c"
    break;

  case 24: /* assignment: SET IDENTIFIER ASSIGN expression  */
#line 89 "snask_parser.y"
                                     { (yyval.ast_node) = ast_create_assignment((yyvsp[-2].id_name), (yyvsp[0].ast_node), yylineno); free((yyvsp[-2].id_name)); }
#line 1428 "snask_parser.tab.c"
    break;

  case 25: /* if_statement: WHEN LPAREN expression RPAREN block  */
#line 94 "snask_parser.y"
                                                   { (yyval.ast_node) = ast_create_if_statement((yyvsp[-2].ast_node), (yyvsp[0].ast_node), NULL, NULL, yylineno); }
#line 1434 "snask_parser.tab.c"
    break;

  case 26: /* if_statement: WHEN LPAREN expression RPAREN block WHENN block  */
#line 95 "snask_parser.y"
                                                                  { (yyval.ast_node) = ast_create_if_statement((yyvsp[-4].ast_node), (yyvsp[-2].ast_node), (yyvsp[0].ast_node), NULL, yylineno); }
#line 1440 "snask_parser.tab.c"
    break;

  case 27: /* if_statement: WHEN LPAREN expression RPAREN block WHENEM LPAREN expression RPAREN block  */
#line 96 "snask_parser.y"
                                                                                             { (yyval.ast_node) = ast_create_if_statement((yyvsp[-7].ast_node), (yyvsp[-5].ast_node), NULL, ast_create_if_statement((yyvsp[-2].ast_node), (yyvsp[0].ast_node), NULL, NULL, yylineno), yylineno); }
#line 1446 "snask_parser.tab.c"
    break;

  case 28: /* while_statement: SPIN LPAREN expression RPAREN block  */
#line 100 "snask_parser.y"
                                        { (yyval.ast_node) = ast_create_while_statement((yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1452 "snask_parser.tab.c"
    break;

  case 29: /* for_statement: LOOPY LPAREN declaration SEMICOLON expression SEMICOLON expression RPAREN block  */
#line 104 "snask_parser.y"
                                                                                    { (yyval.ast_node) = ast_create_for_statement((yyvsp[-6].ast_node), (yyvsp[-4].ast_node), (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1458 "snask_parser.tab.c"
    break;

  case 30: /* return_statement: BACK expression  */
#line 108 "snask_parser.y"
                    { (yyval.ast_node) = ast_create_return_statement((yyvsp[0].ast_node), yylineno); }
#line 1464 "snask_parser.tab.c"
    break;

  case 31: /* print_statement: SHOO expression  */
#line 112 "snask_parser.y"
                    { (yyval.ast_node) = ast_create_print_statement((yyvsp[0].ast_node), yylineno); }
#line 1470 "snask_parser.tab.c"
    break;

  case 32: /* block: LBRACE statement_list RBRACE  */
#line 116 "snask_parser.y"
                                 { (yyval.ast_node) = ast_create_block((yyvsp[-1].ast_node), yylineno); }
#line 1476 "snask_parser.tab.c"
    break;

  case 33: /* function_declaration: CRAFT IDENTIFIER LPAREN parameter_list RPAREN block  */
#line 120 "snask_parser.y"
                                                        { (yyval.ast_node) = ast_create_function_declaration((yyvsp[-4].id_name), (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); free((yyvsp[-4].id_name)); }
#line 1482 "snask_parser.tab.c"
    break;

  case 34: /* parameter_list: %empty  */
#line 124 "snask_parser.y"
                        { (yyval.ast_node) = ast_create_statement_list(yylineno); }
#line 1488 "snask_parser.tab.c"
    break;

  case 35: /* parameter_list: IDENTIFIER  */
#line 125 "snask_parser.y"
                        { (yyval.ast_node) = ast_create_statement_list(yylineno); ast_statement_list_add((yyval.ast_node), ast_create_identifier((yyvsp[0].id_name), yylineno)); free((yyvsp[0].id_name)); }
#line 1494 "snask_parser.tab.c"
    break;

  case 36: /* parameter_list: parameter_list COMMA IDENTIFIER  */
#line 126 "snask_parser.y"
                                      { ast_statement_list_add((yyvsp[-2].ast_node), ast_create_identifier((yyvsp[0].id_name), yylineno)); (yyval.ast_node) = (yyvsp[-2].ast_node); free((yyvsp[0].id_name)); }
#line 1500 "snask_parser.tab.c"
    break;

  case 37: /* function_call: IDENTIFIER LPAREN arguments RPAREN  */
#line 130 "snask_parser.y"
                                       { (yyval.ast_node) = ast_create_function_call((yyvsp[-3].id_name), yylineno); ast_function_call_add_arguments((yyval.ast_node), (yyvsp[-1].ast_node)); free((yyvsp[-3].id_name)); }
#line 1506 "snask_parser.tab.c"
    break;

  case 38: /* arguments: %empty  */
#line 134 "snask_parser.y"
                        { /* no action needed, arguments list will be empty */ }
#line 1512 "snask_parser.tab.c"
    break;

  case 39: /* arguments: expression  */
#line 135 "snask_parser.y"
                        { (yyval.ast_node) = ast_create_statement_list(yylineno); ast_statement_list_add((yyval.ast_node), (yyvsp[0].ast_node)); }
#line 1518 "snask_parser.tab.c"
    break;

  case 40: /* arguments: arguments COMMA expression  */
#line 136 "snask_parser.y"
                                 { ast_statement_list_add((yyvsp[-2].ast_node), (yyvsp[0].ast_node)); (yyval.ast_node) = (yyvsp[-2].ast_node); }
#line 1524 "snask_parser.tab.c"
    break;

  case 41: /* expression: unary_expression  */
#line 140 "snask_parser.y"
                                { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1530 "snask_parser.tab.c"
    break;

  case 42: /* expression: binary_expression  */
#line 141 "snask_parser.y"
                                { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1536 "snask_parser.tab.c"
    break;

  case 43: /* expression: primary  */
#line 142 "snask_parser.y"
                                { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1542 "snask_parser.tab.c"
    break;

  case 44: /* unary_expression: NOT expression  */
#line 146 "snask_parser.y"
                                { (yyval.ast_node) = ast_create_unary_expr(OP_NOT, (yyvsp[0].ast_node), yylineno); }
#line 1548 "snask_parser.tab.c"
    break;

  case 45: /* unary_expression: SUB expression  */
#line 147 "snask_parser.y"
                                { (yyval.ast_node) = ast_create_unary_expr(OP_NEGATE, (yyvsp[0].ast_node), yylineno); }
#line 1554 "snask_parser.tab.c"
    break;

  case 46: /* binary_expression: expression ADD expression  */
#line 151 "snask_parser.y"
                                { (yyval.ast_node) = ast_create_binary_expr(OP_ADD, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1560 "snask_parser.tab.c"
    break;

  case 47: /* binary_expression: expression SUB expression  */
#line 152 "snask_parser.y"
                                { (yyval.ast_node) = ast_create_binary_expr(OP_SUB, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1566 "snask_parser.tab.c"
    break;

  case 48: /* binary_expression: expression MUL expression  */
#line 153 "snask_parser.y"
                                { (yyval.ast_node) = ast_create_binary_expr(OP_MUL, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1572 "snask_parser.tab.c"
    break;

  case 49: /* binary_expression: expression DIV expression  */
#line 154 "snask_parser.y"
                                { (yyval.ast_node) = ast_create_binary_expr(OP_DIV, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1578 "snask_parser.tab.c"
    break;

  case 50: /* binary_expression: expression EQ expression  */
#line 155 "snask_parser.y"
                                { (yyval.ast_node) = ast_create_binary_expr(OP_EQ, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1584 "snask_parser.tab.c"
    break;

  case 51: /* binary_expression: expression NEQ expression  */
#line 156 "snask_parser.y"
                                { (yyval.ast_node) = ast_create_binary_expr(OP_NEQ, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1590 "snask_parser.tab.c"
    break;

  case 52: /* binary_expression: expression LT expression  */
#line 157 "snask_parser.y"
                                { (yyval.ast_node) = ast_create_binary_expr(OP_LT, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1596 "snask_parser.tab.c"
    break;

  case 53: /* binary_expression: expression GT expression  */
#line 158 "snask_parser.y"
                                { (yyval.ast_node) = ast_create_binary_expr(OP_GT, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1602 "snask_parser.tab.c"
    break;

  case 54: /* binary_expression: expression LE expression  */
#line 159 "snask_parser.y"
                                { (yyval.ast_node) = ast_create_binary_expr(OP_LE, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1608 "snask_parser.tab.c"
    break;

  case 55: /* binary_expression: expression GE expression  */
#line 160 "snask_parser.y"
                                { (yyval.ast_node) = ast_create_binary_expr(OP_GE, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1614 "snask_parser.tab.c"
    break;

  case 56: /* binary_expression: expression AND expression  */
#line 161 "snask_parser.y"
                                { (yyval.ast_node) = ast_create_binary_expr(OP_AND, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1620 "snask_parser.tab.c"
    break;

  case 57: /* binary_expression: expression OR expression  */
#line 162 "snask_parser.y"
                                { (yyval.ast_node) = ast_create_binary_expr(OP_OR, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1626 "snask_parser.tab.c"
    break;

  case 58: /* primary: INT_LITERAL  */
#line 166 "snask_parser.y"
                            { (yyval.ast_node) = ast_create_int_literal((yyvsp[0].int_val), yylineno); }
#line 1632 "snask_parser.tab.c"
    break;

  case 59: /* primary: FLOAT_LITERAL  */
#line 167 "snask_parser.y"
                            { (yyval.ast_node) = ast_create_float_literal((yyvsp[0].float_val), yylineno); }
#line 1638 "snask_parser.tab.c"
    break;

  case 60: /* primary: STRING_LITERAL  */
#line 168 "snask_parser.y"
                            { (yyval.ast_node) = ast_create_string_literal((yyvsp[0].string_val), yylineno); free((yyvsp[0].string_val)); }
#line 1644 "snask_parser.tab.c"
    break;

  case 61: /* primary: BOOL_LITERAL  */
#line 169 "snask_parser.y"
                            { (yyval.ast_node) = ast_create_bool_literal((yyvsp[0].bool_val), yylineno); }
#line 1650 "snask_parser.tab.c"
    break;

  case 62: /* primary: NULL_LITERAL  */
#line 170 "snask_parser.y"
                            { (yyval.ast_node) = ast_create_null_literal(yylineno); }
#line 1656 "snask_parser.tab.c"
    break;

  case 63: /* primary: IDENTIFIER  */
#line 171 "snask_parser.y"
                            { (yyval.ast_node) = ast_create_identifier((yyvsp[0].id_name), yylineno); free((yyvsp[0].id_name)); }
#line 1662 "snask_parser.tab.c"
    break;

  case 64: /* primary: LPAREN expression RPAREN  */
#line 172 "snask_parser.y"
                               { (yyval.ast_node) = (yyvsp[-1].ast_node); }
#line 1668 "snask_parser.tab.c"
    break;

  case 65: /* primary: function_call  */
#line 173 "snask_parser.y"
                            { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1674 "snask_parser.tab.c"
    break;

  case 66: /* primary: list_literal  */
#line 174 "snask_parser.y"
                            { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1680 "snask_parser.tab.c"
    break;

  case 67: /* list_literal: PACK LBRACKET list_elements RBRACKET  */
#line 179 "snask_parser.y"
                                         { (yyval.ast_node) = (yyvsp[-1].ast_node); }
#line 1686 "snask_parser.tab.c"
    break;

  case 68: /* list_elements: %empty  */
#line 183 "snask_parser.y"
                        { (yyval.ast_node) = ast_create_list_literal(yylineno); }
#line 1692 "snask_parser.tab.c"
    break;

  case 69: /* list_elements: expression  */
#line 184 "snask_parser.y"
                        { (yyval.ast_node) = ast_create_list_literal(yylineno); ast_list_literal_add_element((yyval.ast_node), (yyvsp[0].ast_node)); }
#line 1698 "snask_parser.tab.c"
    break;

  case 70: /* list_elements: list_elements COMMA expression  */
#line 185 "snask_parser.y"
                                     { ast_list_literal_add_element((yyvsp[-2].ast_node), (yyvsp[0].ast_node)); (yyval.ast_node) = (yyvsp[-2].ast_node); }
#line 1704 "snask_parser.tab.c"
    break;


#line 1708 "snask_parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 188 "snask_parser.y"


// Definição da união YYSTYPE para o Bison
typedef union {
    ASTNode* ast_node;
    char* id_name;
    long long int_val;
    double float_val;
    char* string_val;
    bool bool_val;
} YYSTYPE;

// Função de erro do parser (Bison)
void yyerror(const char *s) {
    fprintf(stderr, "Erro de parsing na linha %d: %s\n", yylineno, s);
    // exit(EXIT_FAILURE); // Pode causar saída abrupta, dependendo da estratégia de tratamento de erros
}

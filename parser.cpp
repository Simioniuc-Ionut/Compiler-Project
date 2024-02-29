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
#line 1 "proiect.y"

#include <iostream>
#include <vector>
#include "SymbolTable.h"
#include <cstring>
//#include <variant>
#include <string>
#include <stdio.h>
#include <stack>
//#include "class.h"
using namespace std;
extern FILE* yyin;
extern char* yytext;
extern int yylineno;
extern int yylex();
void yyerror(const char * s);

 class SymbolTable listSymbols;
 stack<char *> listParamStack;

#line 92 "parser.cpp"

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

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_WHILE = 5,                      /* WHILE  */
  YYSYMBOL_FOR = 6,                        /* FOR  */
  YYSYMBOL_CLASS = 7,                      /* CLASS  */
  YYSYMBOL_CONSTANT = 8,                   /* CONSTANT  */
  YYSYMBOL_RETURN = 9,                     /* RETURN  */
  YYSYMBOL_EVAL = 10,                      /* EVAL  */
  YYSYMBOL_TYPEOF = 11,                    /* TYPEOF  */
  YYSYMBOL_BEGIN_PROGR = 12,               /* BEGIN_PROGR  */
  YYSYMBOL_END_PROGR = 13,                 /* END_PROGR  */
  YYSYMBOL_ASSIGN = 14,                    /* ASSIGN  */
  YYSYMBOL_LOGIC_AND = 15,                 /* LOGIC_AND  */
  YYSYMBOL_LOGIC_OR = 16,                  /* LOGIC_OR  */
  YYSYMBOL_LESS = 17,                      /* LESS  */
  YYSYMBOL_LESS_EQ = 18,                   /* LESS_EQ  */
  YYSYMBOL_GRT = 19,                       /* GRT  */
  YYSYMBOL_GRT_EQ = 20,                    /* GRT_EQ  */
  YYSYMBOL_EQ = 21,                        /* EQ  */
  YYSYMBOL_NOT_EQ = 22,                    /* NOT_EQ  */
  YYSYMBOL_NOT = 23,                       /* NOT  */
  YYSYMBOL_INT = 24,                       /* INT  */
  YYSYMBOL_FLOAT = 25,                     /* FLOAT  */
  YYSYMBOL_CHAR = 26,                      /* CHAR  */
  YYSYMBOL_STRING = 27,                    /* STRING  */
  YYSYMBOL_BOOL = 28,                      /* BOOL  */
  YYSYMBOL_ID = 29,                        /* ID  */
  YYSYMBOL_CLASS_ID = 30,                  /* CLASS_ID  */
  YYSYMBOL_FUN_ID = 31,                    /* FUN_ID  */
  YYSYMBOL_BOOLEAN = 32,                   /* BOOLEAN  */
  YYSYMBOL_NR_INT = 33,                    /* NR_INT  */
  YYSYMBOL_NR_FLOAT = 34,                  /* NR_FLOAT  */
  YYSYMBOL_35_ = 35,                       /* '+'  */
  YYSYMBOL_36_ = 36,                       /* '-'  */
  YYSYMBOL_37_ = 37,                       /* '*'  */
  YYSYMBOL_38_ = 38,                       /* '/'  */
  YYSYMBOL_39_ = 39,                       /* '%'  */
  YYSYMBOL_40_ = 40,                       /* '{'  */
  YYSYMBOL_41_ = 41,                       /* '}'  */
  YYSYMBOL_42_ = 42,                       /* '['  */
  YYSYMBOL_43_ = 43,                       /* ']'  */
  YYSYMBOL_44_ = 44,                       /* '('  */
  YYSYMBOL_45_ = 45,                       /* ')'  */
  YYSYMBOL_46_ = 46,                       /* ';'  */
  YYSYMBOL_47_ = 47,                       /* '.'  */
  YYSYMBOL_48_ = 48,                       /* ','  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_progr = 50,                     /* progr  */
  YYSYMBOL_declarations_glob_variable = 51, /* declarations_glob_variable  */
  YYSYMBOL_functions_glob_def = 52,        /* functions_glob_def  */
  YYSYMBOL_main_fun = 53,                  /* main_fun  */
  YYSYMBOL_decl = 54,                      /* decl  */
  YYSYMBOL_array_decl = 55,                /* array_decl  */
  YYSYMBOL_array_init = 56,                /* array_init  */
  YYSYMBOL_array_usage = 57,               /* array_usage  */
  YYSYMBOL_dimensiune = 58,                /* dimensiune  */
  YYSYMBOL_variable = 59,                  /* variable  */
  YYSYMBOL_variable_def = 60,              /* variable_def  */
  YYSYMBOL_constant_def = 61,              /* constant_def  */
  YYSYMBOL_tip_variabila = 62,             /* tip_variabila  */
  YYSYMBOL_class_def = 63,                 /* class_def  */
  YYSYMBOL_class_body = 64,                /* class_body  */
  YYSYMBOL_data_members = 65,              /* data_members  */
  YYSYMBOL_memmber_functions = 66,         /* memmber_functions  */
  YYSYMBOL_object_decl = 67,               /* object_decl  */
  YYSYMBOL_object_usage = 68,              /* object_usage  */
  YYSYMBOL_field_or_method_call = 69,      /* field_or_method_call  */
  YYSYMBOL_function_def = 70,              /* function_def  */
  YYSYMBOL_function_def_class = 71,        /* function_def_class  */
  YYSYMBOL_function_body = 72,             /* function_body  */
  YYSYMBOL_apel_functie = 73,              /* apel_functie  */
  YYSYMBOL_lista_valori = 74,              /* lista_valori  */
  YYSYMBOL_list_param = 75,                /* list_param  */
  YYSYMBOL_param = 76,                     /* param  */
  YYSYMBOL_valoare = 77,                   /* valoare  */
  YYSYMBOL_call_list = 78,                 /* call_list  */
  YYSYMBOL_EXPRESII = 79,                  /* EXPRESII  */
  YYSYMBOL_EXPR = 80,                      /* EXPR  */
  YYSYMBOL_EXPR_BOOL = 81,                 /* EXPR_BOOL  */
  YYSYMBOL_EXPR_COMP = 82,                 /* EXPR_COMP  */
  YYSYMBOL_RIGHT_VALUE = 83,               /* RIGHT_VALUE  */
  YYSYMBOL_LEFT_VALUE = 84,                /* LEFT_VALUE  */
  YYSYMBOL_block = 85,                     /* block  */
  YYSYMBOL_statement = 86,                 /* statement  */
  YYSYMBOL_statement_conditions = 87,      /* statement_conditions  */
  YYSYMBOL_eval_statement = 88,            /* eval_statement  */
  YYSYMBOL_typeof_statement = 89           /* typeof_statement  */
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
#define YYFINAL  42
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   377

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  238

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   289


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
       2,     2,     2,     2,     2,     2,     2,    39,     2,     2,
      44,    45,    37,    35,    48,    36,    47,    38,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    46,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    42,     2,    43,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    41,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    67,    67,    68,    69,    70,    71,    72,    73,    74,
      78,    79,    81,    82,    84,    87,    91,    98,   107,   116,
     117,   120,   123,   125,   126,   127,   137,   147,   157,   158,
     159,   160,   161,   166,   179,   182,   185,   186,   188,   189,
     192,   195,   197,   198,   199,   200,   207,   226,   244,   245,
     247,   248,   251,   252,   255,   256,   259,   269,   270,   273,
     274,   275,   276,   279,   282,   285,   286,   287,   290,   291,
     292,   293,   294,   295,   296,   297,   299,   300,   301,   302,
     303,   305,   306,   307,   308,   309,   310,   312,   314,   315,
     316,   321,   322,   326,   327,   328,   329,   330,   331,   332,
     334,   335,   336,   337,   340,   342
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
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE", "WHILE",
  "FOR", "CLASS", "CONSTANT", "RETURN", "EVAL", "TYPEOF", "BEGIN_PROGR",
  "END_PROGR", "ASSIGN", "LOGIC_AND", "LOGIC_OR", "LESS", "LESS_EQ", "GRT",
  "GRT_EQ", "EQ", "NOT_EQ", "NOT", "INT", "FLOAT", "CHAR", "STRING",
  "BOOL", "ID", "CLASS_ID", "FUN_ID", "BOOLEAN", "NR_INT", "NR_FLOAT",
  "'+'", "'-'", "'*'", "'/'", "'%'", "'{'", "'}'", "'['", "']'", "'('",
  "')'", "';'", "'.'", "','", "$accept", "progr",
  "declarations_glob_variable", "functions_glob_def", "main_fun", "decl",
  "array_decl", "array_init", "array_usage", "dimensiune", "variable",
  "variable_def", "constant_def", "tip_variabila", "class_def",
  "class_body", "data_members", "memmber_functions", "object_decl",
  "object_usage", "field_or_method_call", "function_def",
  "function_def_class", "function_body", "apel_functie", "lista_valori",
  "list_param", "param", "valoare", "call_list", "EXPRESII", "EXPR",
  "EXPR_BOOL", "EXPR_COMP", "RIGHT_VALUE", "LEFT_VALUE", "block",
  "statement", "statement_conditions", "eval_statement",
  "typeof_statement", YY_NULLPTR
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

#define YYTABLE_NINF (-90)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     280,   -19,   337,   255,   -87,   -87,   -87,   -87,   -87,    41,
     291,   182,   -87,   -23,   -87,   -87,   -87,   -87,   -87,    48,
     286,    32,    31,    59,    52,    67,    69,    71,    75,    25,
      80,   -87,   -87,    97,   126,   -87,   137,   246,   107,   -87,
     -87,   -87,   -87,   182,   -87,   110,   -87,   128,   -87,   -87,
      49,   113,   130,   291,   182,   -87,   -87,   108,   150,   298,
     298,   337,   316,   316,   141,    74,   132,   316,   -87,   133,
     -87,   -87,   -87,   316,   -29,   337,   138,   182,   -87,   -87,
     136,   142,    82,   316,    25,   -87,   -87,   -87,   298,   -87,
     -87,   -87,   350,   338,     4,   -87,    20,   143,   155,   316,
     -87,   146,   152,   -87,   145,   153,   156,   -87,   -87,   172,
     -87,   -87,   -24,   -87,   -87,   -87,   -87,   160,   190,   184,
      16,   -87,   108,   -87,   -87,   166,   337,   -87,   185,   168,
     -87,   183,    29,   316,   316,   316,   316,   316,   316,   316,
     316,   316,   316,   316,   298,   298,   186,   192,   298,   210,
     183,   -87,   -87,   196,   292,   -87,   -87,   310,   198,   194,
     -87,   204,   337,   205,   -87,   214,   207,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,   -87,   100,   100,   -87,   -87,
     -87,   -87,   235,   255,   255,    -7,   141,   -87,    39,   -87,
     -87,   222,    96,   255,   -87,   216,   220,   -87,   226,   227,
     316,   233,   -87,   242,   -87,   -87,   -31,   -87,   117,   223,
     -87,   337,   274,   -87,   320,   -87,   -87,   -87,    96,   -87,
     243,   -87,    47,   250,   251,   -87,   -87,   257,   255,   260,
     255,   254,   255,   144,   -87,   261,   -87,   -87
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,    28,    29,    30,    31,    32,     0,
       0,     0,     9,     0,    23,    24,    15,    22,    25,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    88,
       0,    97,    90,     0,    95,    94,     0,     0,     0,    96,
      98,    99,     1,     0,     5,     0,     4,     0,    13,    10,
       0,     0,     0,     0,     0,     8,    12,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    14,     0,
      91,     3,    11,     0,     0,     0,     0,     0,     6,     7,
       0,     0,     0,     0,    72,    79,    70,    71,     0,    74,
      75,    73,     0,    63,     0,    78,     0,     0,     0,     0,
      87,     0,     0,    21,     0,    42,     0,    45,    41,     0,
      51,    60,     0,    59,    93,    92,    26,     0,     0,     0,
       0,    54,     0,     2,    36,     0,     0,    37,    35,     0,
      27,    63,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   104,   105,    19,     0,    40,    50,     0,    16,     0,
      56,     0,     0,     0,    33,     0,     0,    38,    69,    80,
      81,    82,    83,    84,    85,    86,    64,    65,    66,    67,
      68,    76,    77,     0,     0,     0,     0,    44,     0,    61,
      62,     0,     0,     0,    55,     0,     0,    39,     0,     0,
       0,     0,    43,     0,    57,    58,     0,    52,     0,     0,
      34,     0,   100,   102,     0,    20,    17,    18,     0,    46,
       0,    48,     0,     0,     0,    53,    49,     0,     0,     0,
       0,     0,     0,     0,   101,     0,    47,   103
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -87,   -87,   271,    23,    40,    22,   -87,   -87,    -3,   115,
     -54,   248,   -87,     5,   -87,   202,   -87,   -87,   163,     3,
     -87,    27,   200,   103,     9,   -87,   123,   173,   120,   197,
     -36,   -86,   -59,   -87,     6,   -87,   -87,    15,   -87,   -87,
     -87
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     9,    10,    11,    12,    31,    14,    15,    89,   104,
      16,    17,    18,    33,    20,    81,    82,   128,   111,    90,
     108,    21,   129,   208,    91,   206,   120,   121,   207,   112,
      92,    93,    94,    95,   101,    36,    37,   209,    39,    40,
      41
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      32,    96,   131,    80,   117,    19,    34,    23,   144,   145,
     217,    22,    35,   150,   118,    19,    47,   218,    38,   144,
     145,   156,    13,    49,   157,    19,   100,   100,   127,   132,
     113,   100,    45,    43,    32,   144,   145,   116,    48,   200,
      34,    42,    13,    54,   144,   145,    35,   130,    47,   146,
      44,    46,    69,   176,   177,   178,   179,   180,    19,    47,
      55,   161,   107,    73,   162,   147,    98,    64,    80,   102,
      48,    57,    65,   114,   169,    45,    77,    50,    56,    51,
     119,    48,    47,    71,   202,   181,   182,   157,    58,   185,
       2,    74,   227,    78,    79,   162,    59,   170,   171,   172,
     173,   174,   175,   105,    48,   106,     4,     5,     6,     7,
       8,    60,   126,    61,   214,    62,     2,   123,   113,    63,
      24,   190,    25,    26,    66,     2,    50,    27,    28,   204,
     205,   165,     4,     5,     6,     7,     8,   141,   142,   143,
     -89,     4,     5,     6,     7,     8,    29,    24,    30,    25,
      26,    67,     2,    70,    27,    28,    72,    75,   219,    51,
      76,    84,   109,    30,    83,    86,    87,   119,     4,     5,
       6,     7,     8,    29,   103,    30,    99,   110,   122,   115,
      32,    32,   124,   125,   149,   236,    34,    34,   153,   148,
      32,   151,    35,    35,     3,    64,    34,   152,   198,   199,
     154,   155,    35,   158,   159,    32,     4,     5,     6,     7,
       8,    34,   164,   160,   167,   126,   119,    35,   139,   140,
     141,   142,   143,   220,    73,    32,   183,    32,   168,    32,
      32,    34,   184,    34,   192,    34,    34,    35,   186,    35,
     191,    35,    35,   231,   193,   196,   195,   235,   220,    24,
     144,    25,    26,   197,     2,   203,    27,    28,    24,    68,
      25,    26,   210,     2,   211,    27,    28,   212,   213,   221,
       4,     5,     6,     7,     8,    29,   215,    30,   223,     4,
       5,     6,     7,     8,    29,   216,    30,     1,     2,   226,
     228,    53,     3,    52,     2,   234,   229,   230,     3,     2,
     232,   201,   237,     3,     4,     5,     6,     7,     8,    97,
       4,     5,     6,     7,     8,     4,     5,     6,     7,     8,
     189,    84,   109,    30,   163,    86,    87,    84,   166,    30,
      85,    86,    87,   233,   222,   194,    99,   187,   225,    84,
     109,    30,    88,    86,    87,    84,     0,    30,     0,    86,
      87,   188,     0,     0,    99,   139,   140,   141,   142,   143,
      99,     4,     5,     6,     7,     8,   224,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143
};

static const yytype_int16 yycheck[] =
{
       3,    60,    88,    57,    33,     0,     3,     2,    15,    16,
      41,    30,     3,    99,    43,    10,    11,    48,     3,    15,
      16,    45,     0,    46,    48,    20,    62,    63,    82,    88,
      66,    67,    10,    10,    37,    15,    16,    73,    11,    46,
      37,     0,    20,    20,    15,    16,    37,    83,    43,    45,
      10,    11,    37,   139,   140,   141,   142,   143,    53,    54,
      20,    45,    65,    14,    48,    45,    61,    42,   122,    63,
      43,    40,    47,    67,    45,    53,    53,    29,    46,    31,
      75,    54,    77,    43,    45,   144,   145,    48,    29,   148,
       8,    42,    45,    53,    54,    48,    44,   133,   134,   135,
     136,   137,   138,    29,    77,    31,    24,    25,    26,    27,
      28,    44,    30,    44,   200,    44,     8,    77,   154,    44,
       3,   157,     5,     6,    44,     8,    29,    10,    11,    33,
      34,   126,    24,    25,    26,    27,    28,    37,    38,    39,
      14,    24,    25,    26,    27,    28,    29,     3,    31,     5,
       6,    14,     8,    46,    10,    11,    46,    44,    41,    31,
      30,    29,    30,    31,    14,    33,    34,   162,    24,    25,
      26,    27,    28,    29,    33,    31,    44,    45,    40,    46,
     183,   184,    46,    41,    29,    41,   183,   184,    43,    46,
     193,    45,   183,   184,    12,    42,   193,    45,   183,   184,
      44,    29,   193,    43,    14,   208,    24,    25,    26,    27,
      28,   208,    46,    29,    46,    30,   211,   208,    35,    36,
      37,    38,    39,   208,    14,   228,    40,   230,    45,   232,
     233,   228,    40,   230,    40,   232,   233,   228,    42,   230,
      42,   232,   233,   228,    40,    31,    41,   232,   233,     3,
      15,     5,     6,    46,     8,    33,    10,    11,     3,    13,
       5,     6,    46,     8,    44,    10,    11,    41,    41,    46,
      24,    25,    26,    27,    28,    29,    43,    31,     4,    24,
      25,    26,    27,    28,    29,    43,    31,     7,     8,    46,
      40,    20,    12,     7,     8,    41,    45,    40,    12,     8,
      40,   186,    41,    12,    24,    25,    26,    27,    28,    61,
      24,    25,    26,    27,    28,    24,    25,    26,    27,    28,
     157,    29,    30,    31,   122,    33,    34,    29,   128,    31,
      32,    33,    34,   230,   211,   162,    44,    45,   218,    29,
      30,    31,    44,    33,    34,    29,    -1,    31,    -1,    33,
      34,   154,    -1,    -1,    44,    35,    36,    37,    38,    39,
      44,    24,    25,    26,    27,    28,    46,    17,    18,    19,
      20,    21,    22,    35,    36,    37,    38,    39
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     8,    12,    24,    25,    26,    27,    28,    50,
      51,    52,    53,    54,    55,    56,    59,    60,    61,    62,
      63,    70,    30,    62,     3,     5,     6,    10,    11,    29,
      31,    54,    57,    62,    68,    73,    84,    85,    86,    87,
      88,    89,     0,    52,    53,    54,    53,    62,    70,    46,
      29,    31,     7,    51,    52,    53,    46,    40,    29,    44,
      44,    44,    44,    44,    42,    47,    44,    14,    13,    86,
      46,    53,    46,    14,    42,    44,    30,    52,    53,    53,
      59,    64,    65,    14,    29,    32,    33,    34,    44,    57,
      68,    73,    79,    80,    81,    82,    81,    60,    62,    44,
      79,    83,    83,    33,    58,    29,    31,    57,    69,    30,
      45,    67,    78,    79,    83,    46,    79,    33,    43,    62,
      75,    76,    40,    53,    46,    41,    30,    59,    66,    71,
      79,    80,    81,    17,    18,    19,    20,    21,    22,    35,
      36,    37,    38,    39,    15,    16,    45,    45,    46,    29,
      80,    45,    45,    43,    44,    29,    45,    48,    43,    14,
      29,    45,    48,    64,    46,    62,    71,    46,    45,    45,
      79,    79,    79,    79,    79,    79,    80,    80,    80,    80,
      80,    81,    81,    40,    40,    81,    42,    45,    78,    67,
      79,    42,    40,    40,    76,    41,    31,    46,    86,    86,
      46,    58,    45,    33,    33,    34,    74,    77,    72,    86,
      46,    44,    41,    41,    80,    43,    43,    41,    48,    41,
      86,    46,    75,     4,    46,    77,    46,    45,    40,    45,
      40,    86,    40,    72,    41,    86,    41,    41
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    50,    50,    50,    50,    50,    50,    50,
      51,    51,    52,    52,    53,    54,    55,    55,    56,    57,
      57,    58,    59,    59,    59,    59,    60,    61,    62,    62,
      62,    62,    62,    63,    63,    64,    65,    65,    66,    66,
      67,    68,    69,    69,    69,    69,    70,    71,    72,    72,
      73,    73,    74,    74,    75,    75,    76,    77,    77,    78,
      78,    78,    78,    79,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    81,    81,    81,    81,
      81,    82,    82,    82,    82,    82,    82,    83,    84,    84,
      84,    85,    85,    86,    86,    86,    86,    86,    86,    86,
      87,    87,    87,    87,    88,    89
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     3,     2,     2,     3,     3,     2,     1,
       2,     3,     2,     2,     3,     1,     5,     8,     8,     4,
       7,     1,     1,     1,     1,     1,     4,     5,     1,     1,
       1,     1,     1,     6,     7,     2,     2,     2,     2,     3,
       2,     3,     1,     4,     3,     1,     8,     9,     2,     3,
       4,     3,     1,     3,     1,     3,     2,     1,     1,     1,
       1,     3,     3,     1,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     2,     3,     3,     1,     1,     1,     1,     1,     1,
       7,    11,     7,    12,     4,     4
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
  case 2: /* progr: class_def declarations_glob_variable functions_glob_def main_fun  */
#line 67 "proiect.y"
                                                                        {printf("The programme is correct!\n");}
#line 1353 "parser.cpp"
    break;

  case 3: /* progr: declarations_glob_variable functions_glob_def main_fun  */
#line 68 "proiect.y"
                                                              {printf("The programme is correct!\n");}
#line 1359 "parser.cpp"
    break;

  case 4: /* progr: functions_glob_def main_fun  */
#line 69 "proiect.y"
                                   {printf("The programme is correct!\n");}
#line 1365 "parser.cpp"
    break;

  case 5: /* progr: declarations_glob_variable main_fun  */
#line 70 "proiect.y"
                                           {printf("The programme is correct!\n");}
#line 1371 "parser.cpp"
    break;

  case 6: /* progr: class_def declarations_glob_variable main_fun  */
#line 71 "proiect.y"
                                                     {printf("The programme is correct!\n");}
#line 1377 "parser.cpp"
    break;

  case 7: /* progr: class_def functions_glob_def main_fun  */
#line 72 "proiect.y"
                                             {printf("The programme is correct!\n");}
#line 1383 "parser.cpp"
    break;

  case 8: /* progr: class_def main_fun  */
#line 73 "proiect.y"
                          {printf("The programme is correct!\n");}
#line 1389 "parser.cpp"
    break;

  case 9: /* progr: main_fun  */
#line 74 "proiect.y"
                {printf("The programme is correct!\n");}
#line 1395 "parser.cpp"
    break;

  case 16: /* array_decl: tip_variabila ID '[' NR_INT ']'  */
#line 91 "proiect.y"
                                             {
                        if(!listSymbols.existsVar((yyvsp[-3].String))) {
                          listSymbols.addArray((yyvsp[-4].tip_data),(yyvsp[-3].String),(yyvsp[-1].Int));
                     }else{
                              printf("Error at def var\n");
                         }
                     }
#line 1407 "parser.cpp"
    break;

  case 17: /* array_decl: tip_variabila ID '[' NR_INT ']' '[' NR_INT ']'  */
#line 98 "proiect.y"
                                                            {
                    if(!listSymbols.existsVar((yyvsp[-6].String))) {
                          listSymbols.addArray((yyvsp[-7].tip_data),(yyvsp[-6].String),(yyvsp[-4].Int),(yyvsp[-1].Int));
                     }else{
                              printf("Error at def var\n");
                         }
                     }
#line 1419 "parser.cpp"
    break;

  case 18: /* array_init: tip_variabila ID '[' ']' ASSIGN '{' lista_valori '}'  */
#line 107 "proiect.y"
                                                                  { 
          /* Logică inițializare */ 
         /* if(!listSymbols.existsVar($2)) {
                          listSymbols.addArray($1,$2,$4);
                     }else{
                              printf("Error at def var\n");
                         }*/
          }
#line 1432 "parser.cpp"
    break;

  case 26: /* variable_def: tip_variabila ID ASSIGN EXPRESII  */
#line 137 "proiect.y"
                                                {
                    if(!listSymbols.existsVar((yyvsp[-2].String))) {
                          listSymbols.addVar((yyvsp[-3].tip_data),(yyvsp[-2].String),(yyvsp[0].String));
                     }else{
                              printf("Error at def var\n");
                         }
                        printf("Definitia variabilei: %s de tipul %s cu valoarea initiala\n", (yyvsp[-2].String), (yyvsp[-3].tip_data));
                        // Aici, expr ar trebui să fie evaluată și valoarea să fie stocată/atribuită variabilei
                    }
#line 1446 "parser.cpp"
    break;

  case 27: /* constant_def: CONSTANT tip_variabila ID ASSIGN EXPRESII  */
#line 147 "proiect.y"
                                                         {
                    if(!listSymbols.existsVar((yyvsp[-2].String))){ //daca nu exista deja variabila de acelasi tip cu acelasi nume                           
                              listSymbols.addVar((yyvsp[-3].tip_data),(yyvsp[-2].String),(yyvsp[0].String));
                         }else{
                              printf("Error at decl var\n");
                         }
                    //trebuie adaugat ca si o constanta,direct cu valoarea ei ,nr
               }
#line 1459 "parser.cpp"
    break;

  case 28: /* tip_variabila: INT  */
#line 157 "proiect.y"
                    {(yyval.tip_data)=(yyvsp[0].tip_data); free((yyvsp[0].tip_data));}
#line 1465 "parser.cpp"
    break;

  case 29: /* tip_variabila: FLOAT  */
#line 158 "proiect.y"
                      {(yyval.tip_data)=(yyvsp[0].tip_data);}
#line 1471 "parser.cpp"
    break;

  case 30: /* tip_variabila: CHAR  */
#line 159 "proiect.y"
                      {(yyval.tip_data)=(yyvsp[0].tip_data);}
#line 1477 "parser.cpp"
    break;

  case 31: /* tip_variabila: STRING  */
#line 160 "proiect.y"
                        {(yyval.tip_data)=(yyvsp[0].tip_data);}
#line 1483 "parser.cpp"
    break;

  case 32: /* tip_variabila: BOOL  */
#line 161 "proiect.y"
                      {(yyval.tip_data)=(yyvsp[0].tip_data);}
#line 1489 "parser.cpp"
    break;

  case 33: /* class_def: CLASS CLASS_ID '{' class_body '}' ';'  */
#line 166 "proiect.y"
                                                   { 
              
              /* userDefinedClasses newClass;
               newClass.className= $1;

               newClass.members = getTemporaryMembers(); // Funcție ipotetică
               newClass.FUNCTIONS = getTemporaryFunctions(); // Funcție ipotetică

               userDefinedClasses[newClass.className] = newClass;
                */
                // Aici, $2 este numele clasei
                // Presupunem că class_body a umplut o structură cu membrii clasei
               }
#line 1507 "parser.cpp"
    break;

  case 40: /* object_decl: CLASS_ID ID  */
#line 192 "proiect.y"
                          {/*cod pentru declararea unui obiect al clasei*/}
#line 1513 "parser.cpp"
    break;

  case 41: /* object_usage: ID '.' field_or_method_call  */
#line 195 "proiect.y"
                                           { /*// Cod pentru utilizarea unui câmp sau apelarea unei metode a obiectului*/}
#line 1519 "parser.cpp"
    break;

  case 42: /* field_or_method_call: ID  */
#line 197 "proiect.y"
                          { /* Accesare câmp */ }
#line 1525 "parser.cpp"
    break;

  case 43: /* field_or_method_call: FUN_ID '(' call_list ')'  */
#line 198 "proiect.y"
                                                { }
#line 1531 "parser.cpp"
    break;

  case 44: /* field_or_method_call: FUN_ID '(' ')'  */
#line 199 "proiect.y"
                                      { /* Apel metoda fără argumente */ }
#line 1537 "parser.cpp"
    break;

  case 46: /* function_def: tip_variabila FUN_ID '(' list_param ')' '{' function_body '}'  */
#line 207 "proiect.y"
                                                                             {
                vector<char *> paramTypes;
                  // Presupunând că $4 este lista de parametri obținută din list_param
                   // for (char* param : $4) {
                   //     paramTypes.push_back(param);
                   // }
                  
                    char* param;
                    while(!listParamStack.empty())
                   {
                    param=listParamStack.top();
                  listParamStack.pop();
                  paramTypes.push_back(param);
                   }
                 if(!listSymbols.existsFunc((yyvsp[-7].tip_data),(yyvsp[-6].String),paramTypes,"")){
                         listSymbols.addFuncGlob((yyvsp[-7].tip_data),(yyvsp[-6].String),paramTypes);
                     }
               }
#line 1560 "parser.cpp"
    break;

  case 47: /* function_def_class: CLASS_ID tip_variabila FUN_ID '(' list_param ')' '{' function_body '}'  */
#line 226 "proiect.y"
                                                                                           {
                    vector<char*> paramTypes;
                    char* param;
                    while(!listParamStack.empty())
                   {
                    param=listParamStack.top();
                  listParamStack.pop();
                  paramTypes.push_back(param);
                   }
                  // Presupunând că $4 este lista de parametri obținută din list_param
                   // for (auto& param : $5) {
                    //    paramTypes.push_back(param);
                    //}
                     if(!listSymbols.existsFunc((yyvsp[-7].tip_data),(yyvsp[-6].String),paramTypes,(yyvsp[-8].String))){
                         listSymbols.addFuncClass((yyvsp[-7].tip_data),(yyvsp[-6].String),paramTypes,(yyvsp[-8].String));
                     }
               }
#line 1582 "parser.cpp"
    break;

  case 54: /* list_param: param  */
#line 255 "proiect.y"
                   { listParamStack.push((yyvsp[0].String));}
#line 1588 "parser.cpp"
    break;

  case 56: /* param: tip_variabila ID  */
#line 259 "proiect.y"
                         {
          
          char* val1 = (yyvsp[-1].tip_data);
          const char* val2 = (yyvsp[0].String);
          strcat(val1," ");
          strcat(val1,val2);
          (yyval.String) = val1;
          
          }
#line 1602 "parser.cpp"
    break;

  case 64: /* EXPR: EXPR '+' EXPR  */
#line 282 "proiect.y"
                                    {

          }
#line 1610 "parser.cpp"
    break;

  case 65: /* EXPR: EXPR '-' EXPR  */
#line 285 "proiect.y"
                          {}
#line 1616 "parser.cpp"
    break;

  case 67: /* EXPR: EXPR '/' EXPR  */
#line 287 "proiect.y"
                          { 
                //eroare de impartire la 0 printf("Error,devide by 0\n");
          }
#line 1624 "parser.cpp"
    break;

  case 68: /* EXPR: EXPR '%' EXPR  */
#line 290 "proiect.y"
                          {}
#line 1630 "parser.cpp"
    break;

  case 69: /* EXPR: '(' EXPR ')'  */
#line 291 "proiect.y"
                         {(yyval.String) = (yyvsp[-1].String);}
#line 1636 "parser.cpp"
    break;

  case 70: /* EXPR: NR_INT  */
#line 292 "proiect.y"
                   {  }
#line 1642 "parser.cpp"
    break;

  case 71: /* EXPR: NR_FLOAT  */
#line 293 "proiect.y"
                     {}
#line 1648 "parser.cpp"
    break;

  case 72: /* EXPR: ID  */
#line 294 "proiect.y"
               {(yyval.String) = (yyvsp[0].String);}
#line 1654 "parser.cpp"
    break;

  case 80: /* EXPR_BOOL: '(' EXPR_BOOL ')'  */
#line 303 "proiect.y"
                               {(yyval.String) = (yyvsp[-1].String);}
#line 1660 "parser.cpp"
    break;


#line 1664 "parser.cpp"

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

#line 344 "proiect.y"


void yyerror(const char * s){
printf("error: %s at line:%d\n",s,yylineno);
}

int main(int argc, char** argv){
     yyin=fopen(argv[1],"r");
     yyparse();
     cout << "Variables:" <<endl;
    // ids.printVars();
    
}

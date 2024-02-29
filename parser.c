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
#include <sstream>
#include <vector>
#include "SymbolTable.h"
#include <cstring>
//#include <variant>
#include <string>
#include <stdio.h>
#include <stack>
#include <queue>
#include <cmath>
#include <type_traits>
using namespace std;

extern FILE* yyin;
extern char* yytext;
extern int line_no;
extern int ch_no;
extern int yylex();
void yyerror(const char * eroare);

std::string boolToString(bool value) {
    std::ostringstream oss;
    oss << (value ? "true" : "false");
    return oss.str();
}

 string type_expresie_curenta;
 string type_left_value;

// Structura pentru nodul arborelui de sintaxă abstractă
struct ASTnode {
    string op;  // Operatorul
    int intvalue;
    float floatvalue;
    bool boolvalue;
    struct Expr* value;  // Valuarea (pentru frunzele arborelui)
    ASTnode *left;  // Subarborele stâng
    ASTnode *right;  // Subarborele drept
};
int precedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    else if (op == "*" || op == "/" || op == "%") return 2;
    else if (op == "<" || op == ">" || op == "<=" || op == ">=" || op == "==" || op == "!=") return 3;
    else if (op == "=") return 4;
    else if (op == "&&") return 5;
    else if (op == "||") return 6;
    else return 0; // În caz de operator necunoscut, returnăm 0
}
// Funcție care convertește o expresie infixată într-o expresie postfixată
string infixToPostfix(const string& infix) {
    string postfix;
    stack<string> operators;

    // Parcurgem fiecare caracter din expresia infixată
    for (size_t i = 0; i < infix.size(); ++i) {
        char c = infix[i];
        if (isdigit(c) || c == '.') {
            // Dacă întâlnim o cifră sau un punct, formăm întregul număr sau partea fracționară a numărului
            string number;
            bool hasDecimal = false; // Indicator pentru a verifica dacă am întâlnit deja un punct în numărul curent
            while (i < infix.size() && (isdigit(infix[i]) || infix[i] == '.')) {
                if (infix[i] == '.') {
                    // Dacă întâlnim un punct, verificăm dacă avem deja un alt punct în numărul curent
                    if (hasDecimal) {
                        // Dacă da, aruncăm o excepție sau gestionăm eroarea în alt mod
                        // În acest exemplu, vom afișa un mesaj de eroare și vom ignora punctul adăugat
                        cerr << "Eroare: Numărul conține mai mult de un punct decimal.\n";
                        break;
                    }
                    hasDecimal = true; // Marchăm că am întâlnit un punct
                }
                number.push_back(infix[i]); // Adăugăm cifra sau punctul la numărul curent
                ++i; // Trecem la următorul caracter
            }
            --i; // Ne întoarcem la ultima cifră sau punctul din număr
            postfix += number + ' '; // Adăugăm numărul la expresia postfixată, urmat de un spațiu
        } else if (c == '(') {
            operators.push("(");
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != "(") {
                postfix += operators.top() + ' ';
                operators.pop();
            }
            operators.pop(); // Scoatem și paranteza deschisă din stivă
        } else if (c == '&' || c == '|' || c == '=' || c == '!' || c == '<' || c == '>') {
            // În cazul în care întâlnim un operator compus sau simplu
            string op(1, c); // Convertim caracterul în șir de caractere
            if (i + 1 < infix.size() && (c == '&' || c == '|' || c == '=' || c == '<' || c == '>' || c == '!')) {
                char nextChar = infix[i + 1];
                if ((c == '&' && nextChar == '&') ||
                    (c == '|' && nextChar == '|') ||
                    (c == '=' && nextChar == '=') ||
                    (c == '!' && nextChar == '=') ||
                    (c == '<' && nextChar == '=') ||
                    (c == '>' && nextChar == '=')) {
                    op.push_back(nextChar);
                    ++i; // Trecem peste caracterul următor
                }
            }
            while (!operators.empty() && precedence(operators.top()) >= precedence(op)) {
                postfix += operators.top() + ' ';
                operators.pop();
            }
            operators.push(op); // Adăugăm operatorul curent la stivă
        } else if (c == ' ') {
            // Trecem peste spații
            continue;
        } else {
            // În cazul în care întâlnim un operator simplu
            std::string op(1, c); // Convertim caracterul în șir de caractere
            while (!operators.empty() && precedence(operators.top()) >= precedence(op)) {
                postfix += operators.top() + ' ';
                operators.pop();
            }
            operators.push(op);
        }
    }

    while (!operators.empty()) {
        postfix += operators.top() + ' ';
        operators.pop();
    }

    return postfix;
}


ASTnode* buildAST(const std::string& postfix) {
    std::stack<ASTnode*> nodes;
    std::istringstream iss(postfix);
    std::string token;
    
    while (iss >> token) {
        if (isdigit(token[0])) {
            // Dacă tokenul este un număr, determinăm tipul și creăm un nod frunză corespunzător
            if (token.find('.') != std::string::npos) {
                // Dacă tokenul conține un punct, este un număr float
                float value = std::stof(token);
                ASTnode* node = new ASTnode();
                node->floatvalue = value;
                nodes.push(node);
            } else {
                // Altfel, este un număr întreg
                int value = std::stoi(token);
                ASTnode* node = new ASTnode();
            
                node->intvalue = value;
                //cout<<" "<<node->intvalue<<" : ";
                nodes.push(node);
            }
        } else if (token == "1" || token == "0") {
            // Dacă tokenul este "true" sau "false", este o valoare booleană
            bool value = (token == "1");
            ASTnode* node = new ASTnode();
            node->boolvalue = value;
            //cout<<"<<<<< "<<node->boolvalue<<endl;
            nodes.push(node);
        } else if (token == "&&" || token == "||" || token == "<=" || token == ">=" || token == "==" || token == "!=") {
            // Dacă tokenul este un operator compus, creăm un nod operator și îi adăugăm subarborii corespunzători din stivă

            if (nodes.size() >= 2) {
                ASTnode* right = nodes.top(); nodes.pop();
                ASTnode* left = nodes.top(); nodes.pop();
                ASTnode* node = new ASTnode();
                node->op = token;
                node->left = left;
                node->right = right;
                nodes.push(node);
            } else {
                std::cerr << "Eroare: Stiva nu are suficiente noduri pentru a forma un operator compus.\n";
                // Poți trata această eroare în modul dorit, cum ar fi aruncarea unei excepții sau gestionarea altfel
            }
        } else {
            // Dacă tokenul este un operator simplu, creăm un nod operator și îi adăugăm subarborii corespunzători din stivă
            if (nodes.size() >= 2) {
                ASTnode* right = nodes.top(); nodes.pop();
                ASTnode* left = nodes.top(); nodes.pop();
                ASTnode* node = new ASTnode();
                node->op = token;
                node->left = left;
                node->right = right;
                nodes.push(node);
            } else {
                std::cerr << "Eroare: Stiva nu are suficiente noduri pentru a forma un operator.\n";
                // Poți trata această eroare în modul dorit, cum ar fi aruncarea unei excepții sau gestionarea altfel
            }
        }
    }

    // La final, în vârful stivei va fi arborele AST complet
    return nodes.top();
}

// Funcția pentru a evalua arborele de sintaxă abstractă și a returna rezultatul

template<typename T>
T evalExpr(ASTnode *root) {
    if (root == nullptr) return T();  // Returnăm o valoare implicită pentru nodurile goale

    // Dacă nodul este o frunză (nu are subarbori)
    if (root->left == nullptr && root->right == nullptr) {
        if constexpr (std::is_same_v<T, int>) {
            return root->intvalue;
        } else if constexpr (std::is_same_v<T, float>) {
            return root->floatvalue;
        } else if constexpr (std::is_same_v<T, bool>) {
            return root->intvalue; //folosec bool ca int, 1 true ,0 false
        }
    }

    // Altfel, evaluăm subarborii și combinăm rezultatele în funcție de operator
   // Declaram variabilele left_value si right_value folosind decltype
     
     T left_value  = evalExpr<T>(root->left);
     T right_value = evalExpr<T>(root->right);

    cout<<typeid(left_value).name()<<"-----"<<left_value<<" "<<right_value<<"----"<<endl;

        if (root->op == "+") return left_value + right_value;
        else if (root->op == "-") return left_value - right_value;
        else if (root->op == "*") return left_value * right_value;
        else if (root->op == "/") return left_value / right_value;
        else if (root->op == "%") {
            if constexpr (std::is_integral_v<T>) {
                return left_value % right_value;
            } else {
                // Tratare eroare pentru împărțire modulo pe tipuri care nu sunt întregi
                return std::fmod(left_value, right_value);
            }
        }
        else if (root->op == "<"){cout<<left_value<<" --- "<<right_value<<endl; return left_value < right_value;}
        else if (root->op == ">") return left_value > right_value;
        else if (root->op == "<=") return left_value <= right_value;
        else if (root->op == ">=") return left_value >= right_value;
        else if (root->op == "==") return  left_value == right_value;
        else if (root->op == "!=") return left_value != right_value;
        // Adăugați alte operații de comparație după necesitate
        // Adăugați alte operații aritmetice după necesitate
        else if (root->op == "&&") return left_value && right_value;
        else if (root->op == "||") return left_value || right_value;
        // Adăugați alte operații logice după necesitate   

    return T();  // În caz de operator necunoscut sau tip incompatibil, returnăm o valoare implicită
}

 class SymbolTable listSymbols;
 stack<const char *> scopeStack;
 queue<char *> listTypeParamQueue;
 vector<int> listavalori;

 const char* currentClass;
 vector<Expr*> globalParamList;
 int count_noduri=0;
 int error_flag=0;
 ASTnode* Radacina;
 string infixExpr;
 

#line 332 "parser.c"

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

#include "parser.h"
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
  YYSYMBOL_PLUS = 24,                      /* PLUS  */
  YYSYMBOL_MINUS = 25,                     /* MINUS  */
  YYSYMBOL_MUL = 26,                       /* MUL  */
  YYSYMBOL_DIV = 27,                       /* DIV  */
  YYSYMBOL_MOD = 28,                       /* MOD  */
  YYSYMBOL_INT = 29,                       /* INT  */
  YYSYMBOL_FLOAT = 30,                     /* FLOAT  */
  YYSYMBOL_CHAR = 31,                      /* CHAR  */
  YYSYMBOL_STRING = 32,                    /* STRING  */
  YYSYMBOL_BOOL = 33,                      /* BOOL  */
  YYSYMBOL_ID = 34,                        /* ID  */
  YYSYMBOL_CLASS_ID = 35,                  /* CLASS_ID  */
  YYSYMBOL_FUN_ID = 36,                    /* FUN_ID  */
  YYSYMBOL_BOOLEAN = 37,                   /* BOOLEAN  */
  YYSYMBOL_NR_INT = 38,                    /* NR_INT  */
  YYSYMBOL_NR_FLOAT = 39,                  /* NR_FLOAT  */
  YYSYMBOL_40_ = 40,                       /* '+'  */
  YYSYMBOL_41_ = 41,                       /* '-'  */
  YYSYMBOL_42_ = 42,                       /* '*'  */
  YYSYMBOL_43_ = 43,                       /* '/'  */
  YYSYMBOL_44_ = 44,                       /* '%'  */
  YYSYMBOL_45_ = 45,                       /* '('  */
  YYSYMBOL_46_ = 46,                       /* ')'  */
  YYSYMBOL_47_ = 47,                       /* '{'  */
  YYSYMBOL_48_ = 48,                       /* '}'  */
  YYSYMBOL_49_ = 49,                       /* '['  */
  YYSYMBOL_50_ = 50,                       /* ']'  */
  YYSYMBOL_51_ = 51,                       /* ';'  */
  YYSYMBOL_52_ = 52,                       /* '.'  */
  YYSYMBOL_53_ = 53,                       /* ','  */
  YYSYMBOL_YYACCEPT = 54,                  /* $accept  */
  YYSYMBOL_progr = 55,                     /* progr  */
  YYSYMBOL_declarations_glob_variable = 56, /* declarations_glob_variable  */
  YYSYMBOL_functions_glob_def = 57,        /* functions_glob_def  */
  YYSYMBOL_class_list = 58,                /* class_list  */
  YYSYMBOL_main_fun = 59,                  /* main_fun  */
  YYSYMBOL_begin_progr = 60,               /* begin_progr  */
  YYSYMBOL_end_progr = 61,                 /* end_progr  */
  YYSYMBOL_decl = 62,                      /* decl  */
  YYSYMBOL_variable = 63,                  /* variable  */
  YYSYMBOL_array_decl = 64,                /* array_decl  */
  YYSYMBOL_array_init = 65,                /* array_init  */
  YYSYMBOL_array_usage = 66,               /* array_usage  */
  YYSYMBOL_dimensiune = 67,                /* dimensiune  */
  YYSYMBOL_variable_decl = 68,             /* variable_decl  */
  YYSYMBOL_variable_def = 69,              /* variable_def  */
  YYSYMBOL_constant_def = 70,              /* constant_def  */
  YYSYMBOL_tip_variabila = 71,             /* tip_variabila  */
  YYSYMBOL_class_def = 72,                 /* class_def  */
  YYSYMBOL_class_header = 73,              /* class_header  */
  YYSYMBOL_class_body = 74,                /* class_body  */
  YYSYMBOL_data_members = 75,              /* data_members  */
  YYSYMBOL_memmber_functions = 76,         /* memmber_functions  */
  YYSYMBOL_object_decl = 77,               /* object_decl  */
  YYSYMBOL_object_usage = 78,              /* object_usage  */
  YYSYMBOL_obj_id = 79,                    /* obj_id  */
  YYSYMBOL_field_or_method_call = 80,      /* field_or_method_call  */
  YYSYMBOL_function_def = 81,              /* function_def  */
  YYSYMBOL_function_header = 82,           /* function_header  */
  YYSYMBOL_function_def_class = 83,        /* function_def_class  */
  YYSYMBOL_function_class_header = 84,     /* function_class_header  */
  YYSYMBOL_function_body = 85,             /* function_body  */
  YYSYMBOL_apel_functie = 86,              /* apel_functie  */
  YYSYMBOL_list_param = 87,                /* list_param  */
  YYSYMBOL_param = 88,                     /* param  */
  YYSYMBOL_lista_valori = 89,              /* lista_valori  */
  YYSYMBOL_valoare = 90,                   /* valoare  */
  YYSYMBOL_call_list = 91,                 /* call_list  */
  YYSYMBOL_list = 92,                      /* list  */
  YYSYMBOL_EXPRESII = 93,                  /* EXPRESII  */
  YYSYMBOL_EXPRESIE_ARIT = 94,             /* EXPRESIE_ARIT  */
  YYSYMBOL_EXPR = 95,                      /* EXPR  */
  YYSYMBOL_VARIABLE = 96,                  /* VARIABLE  */
  YYSYMBOL_PARANTEZA_DESCHISA = 97,        /* PARANTEZA_DESCHISA  */
  YYSYMBOL_PARANTEZA_INCHISA = 98,         /* PARANTEZA_INCHISA  */
  YYSYMBOL_OP = 99,                        /* OP  */
  YYSYMBOL_EXPRESIE_BOOL = 100,            /* EXPRESIE_BOOL  */
  YYSYMBOL_EXPR_BOOL = 101,                /* EXPR_BOOL  */
  YYSYMBOL_EXPR_COMP = 102,                /* EXPR_COMP  */
  YYSYMBOL_OP_COMP = 103,                  /* OP_COMP  */
  YYSYMBOL_OP_LOGIC = 104,                 /* OP_LOGIC  */
  YYSYMBOL_RIGHT_VALUE = 105,              /* RIGHT_VALUE  */
  YYSYMBOL_LEFT_VALUE = 106,               /* LEFT_VALUE  */
  YYSYMBOL_block = 107,                    /* block  */
  YYSYMBOL_statement = 108,                /* statement  */
  YYSYMBOL_statement_conditions = 109,     /* statement_conditions  */
  YYSYMBOL_CONDITION = 110,                /* CONDITION  */
  YYSYMBOL_eval_statement = 111,           /* eval_statement  */
  YYSYMBOL_typeof_statement = 112          /* typeof_statement  */
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
#define YYFINAL  32
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   385

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  59
/* YYNRULES -- Number of rules.  */
#define YYNRULES  125
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  243

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


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
       2,     2,     2,     2,     2,     2,     2,    44,     2,     2,
      45,    46,    42,    40,    53,    41,    52,    43,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    51,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    49,     2,    50,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    47,     2,    48,     2,     2,     2,     2,
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
static const yytype_int16 yyrline[] =
{
       0,   317,   317,   318,   319,   320,   321,   322,   323,   324,
     327,   328,   330,   331,   333,   334,   336,   337,   340,   342,
     344,   345,   347,   348,   349,   350,   351,   353,   374,   395,
     420,   429,   439,   442,   467,   499,   531,   532,   533,   534,
     535,   541,   544,   558,   561,   562,   564,   565,   568,   575,
     579,   594,   603,   610,   613,   615,   633,   634,   660,   662,
     723,   724,   727,   728,   729,   730,   733,   734,   737,   742,
     748,   752,   754,   761,   766,   801,   804,   823,   824,   828,
     842,   857,   858,   872,   927,   929,   931,   932,   933,   934,
     935,   938,   939,   953,   966,   969,   975,   982,   983,   985,
    1038,  1039,  1040,  1041,  1042,  1043,  1046,  1047,  1049,  1131,
    1163,  1164,  1167,  1182,  1192,  1193,  1194,  1195,  1196,  1199,
    1200,  1201,  1202,  1204,  1206,  1208
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
  "GRT_EQ", "EQ", "NOT_EQ", "NOT", "PLUS", "MINUS", "MUL", "DIV", "MOD",
  "INT", "FLOAT", "CHAR", "STRING", "BOOL", "ID", "CLASS_ID", "FUN_ID",
  "BOOLEAN", "NR_INT", "NR_FLOAT", "'+'", "'-'", "'*'", "'/'", "'%'",
  "'('", "')'", "'{'", "'}'", "'['", "']'", "';'", "'.'", "','", "$accept",
  "progr", "declarations_glob_variable", "functions_glob_def",
  "class_list", "main_fun", "begin_progr", "end_progr", "decl", "variable",
  "array_decl", "array_init", "array_usage", "dimensiune", "variable_decl",
  "variable_def", "constant_def", "tip_variabila", "class_def",
  "class_header", "class_body", "data_members", "memmber_functions",
  "object_decl", "object_usage", "obj_id", "field_or_method_call",
  "function_def", "function_header", "function_def_class",
  "function_class_header", "function_body", "apel_functie", "list_param",
  "param", "lista_valori", "valoare", "call_list", "list", "EXPRESII",
  "EXPRESIE_ARIT", "EXPR", "VARIABLE", "PARANTEZA_DESCHISA",
  "PARANTEZA_INCHISA", "OP", "EXPRESIE_BOOL", "EXPR_BOOL", "EXPR_COMP",
  "OP_COMP", "OP_LOGIC", "RIGHT_VALUE", "LEFT_VALUE", "block", "statement",
  "statement_conditions", "CONDITION", "eval_statement",
  "typeof_statement", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-142)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-96)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     281,   -24,   288,  -142,  -142,  -142,  -142,  -142,  -142,   -12,
      36,   106,   234,   281,  -142,   239,    -2,  -142,  -142,  -142,
    -142,  -142,  -142,    -1,  -142,   199,  -142,     4,   251,     5,
      37,  -142,  -142,   234,  -142,    34,  -142,    54,    76,   106,
     234,  -142,  -142,    49,    87,    88,    89,    95,  -142,   111,
     102,  -142,  -142,   124,  -142,     3,  -142,   151,   239,   119,
    -142,  -142,  -142,  -142,    10,   129,   126,   131,   113,  -142,
     137,   251,  -142,   172,  -142,  -142,  -142,   234,  -142,  -142,
     188,   188,   288,   188,   188,  -142,   123,   140,  -142,  -142,
    -142,   188,  -142,   147,  -142,   188,    -8,   268,  -142,   163,
     288,   166,   184,   169,   251,  -142,   188,  -142,  -142,  -142,
    -142,  -142,  -142,   287,   298,  -142,   188,  -142,  -142,   177,
     197,   200,   214,  -142,   287,    52,  -142,    52,   209,   212,
    -142,  -142,  -142,    35,  -142,   222,  -142,  -142,  -142,   227,
     264,  -142,  -142,   245,  -142,    56,  -142,  -142,   254,  -142,
     241,  -142,   246,  -142,  -142,  -142,  -142,  -142,  -142,  -142,
     257,  -142,  -142,  -142,  -142,  -142,   257,    43,   269,   280,
     282,   188,   314,  -142,  -142,   188,   188,  -142,  -142,  -142,
     123,  -142,   283,   285,   284,   286,   289,   268,   292,  -142,
    -142,  -142,   257,  -142,  -142,  -142,  -142,   251,   251,   279,
      60,  -142,    71,  -142,  -142,   290,   294,    41,   300,  -142,
    -142,   268,   269,   120,   161,   257,   222,   291,  -142,  -142,
      29,  -142,    59,   336,  -142,   293,   295,  -142,  -142,    41,
     296,   299,   301,  -142,  -142,  -142,   251,   302,   170,   251,
    -142,   205,  -142
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,    18,    36,    37,    38,    39,    40,     0,
       0,     0,     0,     0,     9,     0,     0,    20,    24,    25,
      23,    22,    26,     0,    14,     0,    21,     0,     0,     0,
       0,    48,     1,     0,     5,     0,     4,     0,     0,     0,
       0,     8,    15,     0,     0,     0,     0,     0,    19,   109,
       0,    17,   116,     0,   114,     0,   113,     0,     0,     0,
     115,   117,   118,    10,    33,     0,     0,     0,     0,    12,
       0,    58,    42,     0,     3,    11,    13,     0,     6,     7,
       0,     0,     0,     0,     0,    50,     0,    51,    53,    49,
      52,     0,    16,     0,   110,     0,     0,     0,    44,     0,
       0,     0,    43,     0,     0,    54,     0,     2,    83,    96,
      79,    80,    84,     0,    77,    81,     0,   123,    98,     0,
       0,     0,     0,   108,    75,    81,    76,    91,     0,     0,
      74,    72,    73,     0,    70,     0,   112,   111,    34,     0,
       0,    64,    65,     0,    63,     0,    60,    41,     0,    45,
       0,    46,     0,    35,   100,   101,   102,   103,   104,   105,
       0,    86,    87,    88,    89,    90,     0,     0,     0,     0,
       0,     0,     0,   106,   107,     0,     0,   124,   125,    59,
       0,    32,     0,    27,     0,    62,     0,     0,     0,    47,
      56,    99,     0,    78,    85,    82,    97,     0,     0,     0,
      81,    94,    81,    92,    71,    30,     0,     0,     0,    55,
      61,     0,     0,     0,     0,     0,     0,     0,    68,    69,
       0,    66,     0,   119,   121,     0,     0,    28,    29,     0,
       0,     0,     0,    31,    67,    57,     0,     0,     0,     0,
     120,     0,   122
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -142,  -142,   329,    45,  -142,    33,  -142,   297,    18,   -18,
     -95,  -142,  -142,   132,  -142,   270,   -92,     1,   337,  -142,
    -142,  -142,  -142,   -91,  -142,  -142,  -142,    14,  -142,   249,
    -142,   250,   303,   142,   173,  -142,   127,  -142,   179,  -142,
     -63,   146,   -68,  -141,   189,  -142,  -106,   -72,  -142,  -142,
     235,     9,  -142,   -15,   -54,  -142,   304,  -142,  -142
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    10,    11,    12,    13,    14,    15,    51,    52,    17,
      18,    19,    88,   182,    20,    21,    22,    53,    24,    25,
      67,    68,   102,    26,    54,    55,    89,    27,    28,   103,
     104,    70,    56,   145,   146,   220,   221,   133,   134,   123,
     113,   114,   115,   116,   195,   166,   126,   127,   118,   160,
     175,   128,    57,    71,    59,    60,   119,    61,    62
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      58,    23,   141,    30,    93,   142,   144,    66,   117,   117,
     168,    29,    23,    37,    23,   125,   125,    93,    16,   192,
     124,   124,    31,   125,    95,   192,    38,   125,   124,    35,
     139,    16,   124,    64,    37,    65,    32,    87,   125,    50,
      23,    37,   140,   124,    34,    36,    41,    38,   125,    63,
     101,   192,    72,   167,    38,    69,    33,    35,    40,    96,
     154,   155,   156,   157,   158,   159,    74,   173,   174,   201,
     203,    73,    78,    79,   192,   173,   174,   228,    37,   218,
     219,   179,   229,   122,    77,    75,   173,   174,   180,   194,
      65,    38,   141,   129,    80,   142,   144,   191,   143,   199,
     136,   148,   186,   193,   138,   230,   -93,   200,   202,   187,
     107,   -93,   187,   -93,     2,   153,   141,   -95,     3,   142,
     144,     2,   -95,    43,   -95,    44,    45,    76,     2,   212,
      46,    47,    81,    82,    83,     4,     5,     6,     7,     8,
      84,     9,     4,     5,     6,     7,     8,    86,   100,     4,
       5,     6,     7,     8,    49,     9,    50,   130,    64,    93,
      93,   131,   132,    85,    43,    91,    44,    45,   223,     2,
      94,    46,    47,    43,    97,    44,    45,    98,     2,    99,
      46,    47,   213,   214,    93,   105,   106,    93,   143,   135,
       4,     5,     6,     7,     8,    49,     9,    50,   137,     4,
       5,     6,     7,     8,    49,     9,    50,     2,    43,   224,
      44,    45,   143,     2,   147,    46,    47,   149,   240,   100,
     151,   238,   108,   169,   241,   109,   110,   111,     4,     5,
       6,     7,     8,   112,     4,     5,     6,     7,     8,    49,
       9,    50,    43,   170,    44,    45,     3,     2,   172,    46,
      47,   171,    48,   242,    43,   177,    44,    45,   178,     2,
     181,    46,    47,     4,     5,     6,     7,     8,     4,     5,
       6,     7,     8,    49,     9,    50,     2,   183,   184,   185,
       4,     5,     6,     7,     8,    49,     9,    50,     1,     2,
     188,   108,   189,     3,   190,   110,   111,     4,     5,     6,
       7,     8,   112,     9,   154,   155,   156,   157,   158,   159,
       4,     5,     6,     7,     8,   194,     9,     4,     5,     6,
       7,     8,   161,   162,   163,   164,   165,   197,    95,   198,
     215,   207,   217,   205,   206,   208,   209,   211,   139,   216,
     231,   227,    39,   235,   232,   233,   236,   237,   226,   239,
      42,   150,   121,   222,   152,    92,   234,   196,    90,   204,
     210,   225,   176,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   120
};

static const yytype_int16 yycheck[] =
{
      15,     0,    97,     2,    58,    97,    97,    25,    80,    81,
     116,    35,    11,    12,    13,    83,    84,    71,     0,   160,
      83,    84,    34,    91,    14,   166,    12,    95,    91,    11,
      38,    13,    95,    34,    33,    36,     0,    34,   106,    36,
      39,    40,    50,   106,    11,    12,    13,    33,   116,    51,
      68,   192,    47,   116,    40,    51,    11,    39,    13,    49,
      17,    18,    19,    20,    21,    22,    33,    15,    16,   175,
     176,    34,    39,    40,   215,    15,    16,    48,    77,    38,
      39,    46,    53,    82,    39,    51,    15,    16,    53,    46,
      36,    77,   187,    84,    45,   187,   187,   160,    97,   171,
      91,   100,    46,   166,    95,    46,    46,   175,   176,    53,
      77,    51,    53,    53,     8,   106,   211,    46,    12,   211,
     211,     8,    51,     3,    53,     5,     6,    51,     8,   192,
      10,    11,    45,    45,    45,    29,    30,    31,    32,    33,
      45,    35,    29,    30,    31,    32,    33,    45,    35,    29,
      30,    31,    32,    33,    34,    35,    36,    34,    34,   213,
     214,    38,    39,    52,     3,    14,     5,     6,    48,     8,
      51,    10,    11,     3,    45,     5,     6,    51,     8,    48,
      10,    11,   197,   198,   238,    48,    14,   241,   187,    49,
      29,    30,    31,    32,    33,    34,    35,    36,    51,    29,
      30,    31,    32,    33,    34,    35,    36,     8,     3,    48,
       5,     6,   211,     8,    51,    10,    11,    51,    48,    35,
      51,   236,    34,    46,   239,    37,    38,    39,    29,    30,
      31,    32,    33,    45,    29,    30,    31,    32,    33,    34,
      35,    36,     3,    46,     5,     6,    12,     8,    34,    10,
      11,    51,    13,    48,     3,    46,     5,     6,    46,     8,
      38,    10,    11,    29,    30,    31,    32,    33,    29,    30,
      31,    32,    33,    34,    35,    36,     8,    50,    14,    34,
      29,    30,    31,    32,    33,    34,    35,    36,     7,     8,
      36,    34,    51,    12,    48,    38,    39,    29,    30,    31,
      32,    33,    45,    35,    17,    18,    19,    20,    21,    22,
      29,    30,    31,    32,    33,    46,    35,    29,    30,    31,
      32,    33,    24,    25,    26,    27,    28,    47,    14,    47,
      51,    47,    38,    50,    49,    49,    47,    45,    38,    49,
       4,    50,    13,    47,    51,    50,    47,    46,   216,    47,
      13,   102,    82,   211,   104,    58,   229,   168,    55,   180,
     187,   215,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     8,    12,    29,    30,    31,    32,    33,    35,
      55,    56,    57,    58,    59,    60,    62,    63,    64,    65,
      68,    69,    70,    71,    72,    73,    77,    81,    82,    35,
      71,    34,     0,    57,    59,    62,    59,    71,    81,    56,
      57,    59,    72,     3,     5,     6,    10,    11,    13,    34,
      36,    61,    62,    71,    78,    79,    86,   106,   107,   108,
     109,   111,   112,    51,    34,    36,    63,    74,    75,    51,
      85,   107,    47,    34,    59,    51,    51,    57,    59,    59,
      45,    45,    45,    45,    45,    52,    45,    34,    66,    80,
      86,    14,    61,   108,    51,    14,    49,    45,    51,    48,
      35,    63,    76,    83,    84,    48,    14,    59,    34,    37,
      38,    39,    45,    94,    95,    96,    97,   101,   102,   110,
     110,    69,    71,    93,    94,    96,   100,   101,   105,   105,
      34,    38,    39,    91,    92,    49,   105,    51,   105,    38,
      50,    64,    70,    71,    77,    87,    88,    51,    71,    51,
      83,    51,    85,   105,    17,    18,    19,    20,    21,    22,
     103,    24,    25,    26,    27,    28,    99,    94,   100,    46,
      46,    51,    34,    15,    16,   104,   104,    46,    46,    46,
      53,    38,    67,    50,    14,    34,    46,    53,    36,    51,
      48,    94,    97,    94,    46,    98,    98,    47,    47,   101,
      96,   100,    96,   100,    92,    50,    49,    47,    49,    47,
      88,    45,    94,   107,   107,    51,    49,    38,    38,    39,
      89,    90,    87,    48,    48,    95,    67,    50,    48,    53,
      46,     4,    51,    50,    90,    47,    47,    46,   107,    47,
      48,   107,    48
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    54,    55,    55,    55,    55,    55,    55,    55,    55,
      56,    56,    57,    57,    58,    58,    59,    59,    60,    61,
      62,    62,    63,    63,    63,    63,    63,    64,    64,    65,
      66,    66,    67,    68,    69,    70,    71,    71,    71,    71,
      71,    72,    73,    74,    75,    75,    76,    76,    77,    78,
      79,    80,    80,    80,    81,    82,    83,    84,    85,    86,
      87,    87,    88,    88,    88,    88,    89,    89,    90,    90,
      91,    91,    92,    92,    92,    93,    93,    94,    94,    95,
      95,    95,    95,    96,    97,    98,    99,    99,    99,    99,
      99,   100,   100,   100,   100,   100,   101,   101,   101,   102,
     103,   103,   103,   103,   103,   103,   104,   104,   105,   106,
     107,   107,   108,   108,   108,   108,   108,   108,   108,   109,
     109,   109,   109,   110,   111,   112
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     3,     2,     2,     3,     3,     2,     1,
       2,     3,     2,     3,     1,     2,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     5,     8,     8,
       4,     7,     1,     2,     4,     5,     1,     1,     1,     1,
       1,     4,     3,     2,     2,     3,     2,     3,     2,     2,
       2,     1,     1,     1,     3,     6,     3,     7,     1,     4,
       1,     3,     2,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     1,     3,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     3,     3,     1,     1,     1,     1,     1,     1,     7,
      11,     7,    12,     1,     4,     4
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
  case 2: /* progr: class_list declarations_glob_variable functions_glob_def main_fun  */
#line 317 "proiect.y"
                                                                         {printf("The programme is sintactic correct!\n");}
#line 1634 "parser.c"
    break;

  case 3: /* progr: declarations_glob_variable functions_glob_def main_fun  */
#line 318 "proiect.y"
                                                              {printf("The programme is sintactic correct!\n");}
#line 1640 "parser.c"
    break;

  case 4: /* progr: functions_glob_def main_fun  */
#line 319 "proiect.y"
                                   {printf("The programme is sintactic correct!\n");}
#line 1646 "parser.c"
    break;

  case 5: /* progr: declarations_glob_variable main_fun  */
#line 320 "proiect.y"
                                           {printf("The programme is sintactic correct!\n");}
#line 1652 "parser.c"
    break;

  case 6: /* progr: class_list declarations_glob_variable main_fun  */
#line 321 "proiect.y"
                                                      {printf("The programme is sintactic correct!\n");}
#line 1658 "parser.c"
    break;

  case 7: /* progr: class_list functions_glob_def main_fun  */
#line 322 "proiect.y"
                                              {printf("The programme is sintactic correct!\n");}
#line 1664 "parser.c"
    break;

  case 8: /* progr: class_list main_fun  */
#line 323 "proiect.y"
                           {printf("The programme is sintactic correct!\n");}
#line 1670 "parser.c"
    break;

  case 9: /* progr: main_fun  */
#line 324 "proiect.y"
                {printf("The programme is sintactic correct!\n");}
#line 1676 "parser.c"
    break;

  case 16: /* main_fun: begin_progr block end_progr  */
#line 336 "proiect.y"
                                       { }
#line 1682 "parser.c"
    break;

  case 18: /* begin_progr: BEGIN_PROGR  */
#line 340 "proiect.y"
                            {cout<<"------------Begin Progr------------"<<endl; scopeStack.push("main");}
#line 1688 "parser.c"
    break;

  case 19: /* end_progr: END_PROGR  */
#line 342 "proiect.y"
                    {cout<<"------------End Progr------------"<<endl; {if(!scopeStack.empty()){scopeStack.pop();}else{printf("Eror stack class\n");} }}
#line 1694 "parser.c"
    break;

  case 27: /* array_decl: tip_variabila ID '[' NR_INT ']'  */
#line 353 "proiect.y"
                                             {
                        
                         const char* scope ="";
                         if(!scopeStack.empty()){ //ma aflu in scope ul global
                          
                           scope=scopeStack.top(); //clasa/tipul func

                                if(!listSymbols.existsVar((yyvsp[-3].String),scope)){
                              listSymbols.addArray((yyvsp[-4].tip_data),(yyvsp[-3].String),(yyvsp[-1].Int),scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }else {
                              if(!listSymbols.existsVar((yyvsp[-3].String),scope)){
                              listSymbols.addArray((yyvsp[-4].tip_data),(yyvsp[-3].String),(yyvsp[-1].Int),scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }
                    
                     }
#line 1720 "parser.c"
    break;

  case 28: /* array_decl: tip_variabila ID '[' NR_INT ']' '[' NR_INT ']'  */
#line 374 "proiect.y"
                                                            {
                   const char* scope ="";
                         if(!scopeStack.empty()){ //ma aflu in scope ul clasa
                          
                             scope=scopeStack.top(); //clasa

                                if(!listSymbols.existsVar((yyvsp[-6].String),scope)){
                              listSymbols.addArray((yyvsp[-7].tip_data),(yyvsp[-6].String),(yyvsp[-4].Int),(yyvsp[-1].Int),scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }else {
                              if(!listSymbols.existsVar((yyvsp[-6].String),scope)){
                              listSymbols.addArray((yyvsp[-7].tip_data),(yyvsp[-6].String),(yyvsp[-4].Int),(yyvsp[-1].Int),scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }
                     }
#line 1744 "parser.c"
    break;

  case 29: /* array_init: tip_variabila ID '[' ']' ASSIGN '{' lista_valori '}'  */
#line 395 "proiect.y"
                                                                  { 
          /* Logică inițializare */
              const char* scope ="";

                         if(!scopeStack.empty()){ //ma aflu in scope ul  global
                          
                           scope=scopeStack.top(); //clasa
                         
                                if(!listSymbols.existsVar((yyvsp[-6].String),scope)){
                              listSymbols.initArray(listavalori,(yyvsp[-7].tip_data),(yyvsp[-6].String),listavalori.size(),scope);
               
                                }
                              else{
                                   printf("Error at decl array 1\n"); }
                         }else {
                              if(!listSymbols.existsVar((yyvsp[-6].String),scope)){
                               listSymbols.initArray(listavalori,(yyvsp[-7].tip_data),(yyvsp[-6].String),listavalori.size(),scope);
                                }
                              else{
                                   printf("Error at decl array 2\n"); }
                         }
               listavalori.clear();   // Elimină toate elementele din vector
               listavalori.shrink_to_fit();  // Reduc capacitatea vectorului
          }
#line 1773 "parser.c"
    break;

  case 33: /* variable_decl: tip_variabila ID  */
#line 442 "proiect.y"
                                {
                   
                         
                         if(!scopeStack.empty()){ //ma aflu in scope ul  global
                          
                            const char* scope=scopeStack.top(); //clasa/functia/main
                              
                                if(!listSymbols.existsVar((yyvsp[0].String),scope)){
                              listSymbols.addVar((yyvsp[-1].tip_data),(yyvsp[0].String),scope);
                                }
                              else{
                                   printf("Error at decl var\n%s %s",(yyvsp[-1].tip_data),(yyvsp[0].String)); }
                         }else {
                           const char*   scope ="";
                              if(!listSymbols.existsVar((yyvsp[0].String),scope)){
                              listSymbols.addVar((yyvsp[-1].tip_data),(yyvsp[0].String),scope);
                                }
                              else{
                                   printf("Error at decl var\n%s %s",(yyvsp[-1].tip_data),(yyvsp[0].String)); }
                         }

                         //verific daca nu cumva este data membru;
                       //free($2);
                    }
#line 1802 "parser.c"
    break;

  case 34: /* variable_def: tip_variabila ID ASSIGN RIGHT_VALUE  */
#line 467 "proiect.y"
                                                   {   

                         //verific tipurile
                    //cout<<$1<<" [] "<<$4->type;
                    if(strcmp((yyvsp[-3].tip_data),(yyvsp[0].expr)->type)!=0){
                         yyerror("Error diferite types in variable");
                        
                    }else{

                         //adaug in symboltable
                         if(!scopeStack.empty()){ //nu ma aflu in scope ul  global
                          
                           const char*  scope=scopeStack.top(); //clasa
               
                                if(!listSymbols.existsVar((yyvsp[-2].String),scope)){
                              listSymbols.addVar((yyvsp[-3].tip_data),(yyvsp[-2].String),(yyvsp[0].expr)->value,scope);
                                }
                              else{
                                   yyerror("Error at decl var"); }
                         }else {//ma aflu in scope ul  global
                                const char* scope ="";
                              if(!listSymbols.existsVar((yyvsp[-2].String),scope)){
                              listSymbols.addVar((yyvsp[-3].tip_data),(yyvsp[-2].String),(yyvsp[0].expr)->value,scope);
                                }
                              else{
                                   yyerror("Error at decl var"); }
                         }
                        //printf("Definitia variabilei: %s de tipul %s cu valoarea initiala\n", $2, $1);
                        // Aici, expr ar trebui să fie evaluată și valoarea să fie stocată/atribuită variabilei
                    }
               }
#line 1838 "parser.c"
    break;

  case 35: /* constant_def: CONSTANT tip_variabila ID ASSIGN RIGHT_VALUE  */
#line 499 "proiect.y"
                                                            {
               
               if(strcmp((yyvsp[-3].tip_data),(yyvsp[0].expr)->type)!=0){
                    yyerror("Eror diferite types");
                   
               }else{

                         
                                                // Presupunem că $5 este un Expr*
                         if(!scopeStack.empty()){ //ma aflu in scope ul  global
                          
                           const char* scope=scopeStack.top(); //clasa

                                if(!listSymbols.existsVar((yyvsp[-3].tip_data),scope)){
                              listSymbols.addVar(true,(yyvsp[-3].tip_data),(yyvsp[-2].String),(yyvsp[0].expr)->value,scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }else {
                               const char* scope ="";
                              if(!listSymbols.existsVar((yyvsp[-3].tip_data),scope)){
                              listSymbols.addVar(true,(yyvsp[-3].tip_data),(yyvsp[-2].String),(yyvsp[0].expr)->value,scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }
                    
                    //trebuie adaugat ca si o constanta,direct cu valoarea ei ,nr
               }
               }
#line 1873 "parser.c"
    break;

  case 36: /* tip_variabila: INT  */
#line 531 "proiect.y"
                      {(yyval.tip_data)=(yyvsp[0].tip_data); type_left_value=(yyvsp[0].tip_data);}
#line 1879 "parser.c"
    break;

  case 37: /* tip_variabila: FLOAT  */
#line 532 "proiect.y"
                      {(yyval.tip_data)=(yyvsp[0].tip_data); type_left_value=(yyvsp[0].tip_data);}
#line 1885 "parser.c"
    break;

  case 38: /* tip_variabila: CHAR  */
#line 533 "proiect.y"
                      {(yyval.tip_data)=(yyvsp[0].tip_data); type_left_value=(yyvsp[0].tip_data);}
#line 1891 "parser.c"
    break;

  case 39: /* tip_variabila: STRING  */
#line 534 "proiect.y"
                      {(yyval.tip_data)=(yyvsp[0].tip_data); type_left_value=(yyvsp[0].tip_data);}
#line 1897 "parser.c"
    break;

  case 40: /* tip_variabila: BOOL  */
#line 535 "proiect.y"
                      {(yyval.tip_data)=(yyvsp[0].tip_data); type_left_value=(yyvsp[0].tip_data);}
#line 1903 "parser.c"
    break;

  case 41: /* class_def: class_header class_body '}' ';'  */
#line 541 "proiect.y"
                                            { if(!scopeStack.empty()){scopeStack.pop();}else{printf("Eror stack class\n");} cout<<"de 1"<<endl;}
#line 1909 "parser.c"
    break;

  case 42: /* class_header: CLASS CLASS_ID '{'  */
#line 544 "proiect.y"
                                   { 
             
               scopeStack.push((yyvsp[-1].String));

             if(!listSymbols.existsClass((yyvsp[-1].String))){
                  listSymbols.addClass((yyvsp[-1].String));
             }else{
               printf("Eror,already class exists\n");
             }

             }
#line 1925 "parser.c"
    break;

  case 48: /* object_decl: CLASS_ID ID  */
#line 568 "proiect.y"
                          {/*cod pentru declararea unui obiect al clasei*/
                     if(listSymbols.addObjInClass((yyvsp[-1].String),(yyvsp[0].String))){
                       
                    }else { cout<<"Eror decl obj"<<(yyvsp[0].String)<<endl;}
               
               }
#line 1936 "parser.c"
    break;

  case 49: /* object_usage: obj_id field_or_method_call  */
#line 575 "proiect.y"
                                            {
               currentClass = nullptr; // Setează pointerul la nullptr după eliberarea memoriei
                  /*// Cod pentru utilizarea unui câmp sau apelarea unei metode a obiectului*/}
#line 1944 "parser.c"
    break;

  case 50: /* obj_id: ID '.'  */
#line 579 "proiect.y"
              {
               //const char* className=scopeStack.top();          
               //daca apelz obiectul in main,clasa curenta va fi deja scoasa din scope
                 currentClass =listSymbols.gettypeObj((yyvsp[-1].String)).c_str();
               
                if(strcmp(currentClass,"")!=0){
                    //exist obiectul
                         (yyval.NameClas) = currentClass;
                         cout<<(yyval.NameClas)<<endl; // Alocăm și setăm numele clasei
                    }else{
                         cout<<"Eror class is not decl"; (yyval.NameClas) = nullptr;}

                }
#line 1962 "parser.c"
    break;

  case 51: /* field_or_method_call: ID  */
#line 594 "proiect.y"
                          { /* Accesare câmp */
                     //const char* className = $<NameClas>-1;// Obțineți numele clasei transmis
                     const char* fieldName = (yyvsp[0].String);  
                     cout<<currentClass<<" tipul obj: "<<(yyvsp[0].String)<<endl;
                    if(listSymbols.existsVar((yyvsp[0].String),currentClass)){
                              //l am accesat
                    }else { cout<<"Nu exista acest camp in clasa "<<currentClass<<endl;}
                         }
#line 1975 "parser.c"
    break;

  case 52: /* field_or_method_call: apel_functie  */
#line 603 "proiect.y"
                                   {for(Expr* expr : globalParamList){
                          delete expr; 
                          expr=nullptr; 
                        }
                        cout<<"S-a dealocat globalParamList"<<endl;}
#line 1985 "parser.c"
    break;

  case 53: /* field_or_method_call: array_usage  */
#line 610 "proiect.y"
                                   {}
#line 1991 "parser.c"
    break;

  case 54: /* function_def: function_header function_body '}'  */
#line 613 "proiect.y"
                                                 { if(!scopeStack.empty()){scopeStack.pop();}else{printf("Eror stack class\n");} }
#line 1997 "parser.c"
    break;

  case 55: /* function_header: tip_variabila FUN_ID '(' list_param ')' '{'  */
#line 615 "proiect.y"
                                                              {
                    scopeStack.push((yyvsp[-4].String));
                    //const char* scopeFun=scopeStack.top();
                    const char* scope="";
                  vector<const char *> paramTypes;
                  // Presupunând că $4 este lista de parametri obținută din list_param                     
                    while(!listTypeParamQueue.empty())
                   {
                   const char*  param=listTypeParamQueue.front();
                   listTypeParamQueue.pop();
                   paramTypes.push_back(param);
                   }
                  
                   if(!listSymbols.existsFunc((yyvsp[-5].tip_data),(yyvsp[-4].String),paramTypes,scope)){
                    listSymbols.addFunc((yyvsp[-5].tip_data),(yyvsp[-4].String),paramTypes,scope);
                   }else { cout<<"Eror at func decl: "<<(yyvsp[-5].tip_data)<<" "<<(yyvsp[-4].String)<<endl ;}
               }
#line 2019 "parser.c"
    break;

  case 56: /* function_def_class: function_class_header function_body '}'  */
#line 633 "proiect.y"
                                                             {}
#line 2025 "parser.c"
    break;

  case 57: /* function_class_header: CLASS_ID tip_variabila FUN_ID '(' list_param ')' '{'  */
#line 634 "proiect.y"
                                                                            {
                    
                    
                    //partea de lista a parametrilor
                    vector<const char*> paramTypes;  
                    while(!listTypeParamQueue.empty())
                    {
                    const char* param=listTypeParamQueue.front();
                    listTypeParamQueue.pop();
                    paramTypes.push_back(param);
                    }
                    const char* classId ="";

                     if(!scopeStack.empty()) //am clase in stiva
                    {
                      classId=scopeStack.top();
                      cout<<classId<<" "<<endl;
                      if(!listSymbols.existsFunc((yyvsp[-5].tip_data),(yyvsp[-4].String),paramTypes,classId)){
                        listSymbols.addFunc((yyvsp[-5].tip_data),(yyvsp[-4].String),paramTypes,classId);
                      }
                      else{
                         cout<<"Eror at func decl: "<<(yyvsp[-6].String)<<" "<<(yyvsp[-5].tip_data)<<" "<<(yyvsp[-4].String)<<endl ;
                      }
                    }else {cout<<"error la stiva";}       
               }
#line 2055 "parser.c"
    break;

  case 58: /* function_body: block  */
#line 660 "proiect.y"
                      {}
#line 2061 "parser.c"
    break;

  case 59: /* apel_functie: FUN_ID '(' call_list ')'  */
#line 662 "proiect.y"
                                        { 

                    vector<const char*> paramTypes;
                    cout<<"GLobal param types  "<<endl;
                    
                    for(Expr* expr : globalParamList){
                         cout<<expr->type<<" "<<expr->intvalue<<" "<<expr->floatvalue<<"|";
                         paramTypes.push_back(expr->type);
                         // Dacă este necesar, aici puteți și elibera memoria alocată pentru expr
                    }
                    if(currentClass==nullptr || *currentClass == '\0')
                    {
                    // cout<<"HELLO"<<endl;
                    const char * scope="";
                    
                    string typeFunc = listSymbols.getTypeFunc(scope,(yyvsp[-3].String),paramTypes,scope);  /*scope="" inseamna ca e global*/
                        cout<<typeFunc<<endl;
                        if(typeFunc == ""){
                              yyerror("Eror cant call inexistent fun");
                              (yyval.String)=nullptr;
                        }else{
                         cout<<"Can call fun "<<(yyvsp[-3].String)<<endl;
                         const char* returnType = typeFunc.c_str();
                         (yyval.String)=(char*)returnType;
                        }
                    //$$ trebuie sa prineasca return type ul,pt a puea asigna functia;
                    }else { //apel de metoda
                     //cout<<"HELLO1"<<endl;
                         const char * scope="";
                           string typeFunc = listSymbols.getTypeFunc(scope,(yyvsp[-3].String),paramTypes,currentClass);  /*scope="" inseamna ca e global*/
                        if(typeFunc == ""){
                              yyerror("Eror cant call inexistent fun");
                              (yyval.String)=nullptr;
                        }else{
                         cout<<"Can call fun "<<(yyvsp[-3].String)<<" tipul metodei: "<<currentClass<<endl;
                         const char* returnType = typeFunc.c_str();
                         (yyval.String)=(char*)returnType;
                        }

                    }
                      //if(globalParamList.size()>0)
                         
                     globalParamList.clear(); 
               }
#line 2110 "parser.c"
    break;

  case 60: /* list_param: param  */
#line 723 "proiect.y"
                   { listTypeParamQueue.push((yyvsp[0].String)); printf("|%s|\n",(yyvsp[0].String));}
#line 2116 "parser.c"
    break;

  case 61: /* list_param: list_param ',' param  */
#line 724 "proiect.y"
                                   {listTypeParamQueue.push((yyvsp[0].String)); printf("|%s|\n",(yyvsp[0].String));}
#line 2122 "parser.c"
    break;

  case 62: /* param: tip_variabila ID  */
#line 727 "proiect.y"
                         {(yyval.String) = (yyvsp[-1].tip_data); }
#line 2128 "parser.c"
    break;

  case 66: /* lista_valori: valoare  */
#line 733 "proiect.y"
                       {}
#line 2134 "parser.c"
    break;

  case 67: /* lista_valori: lista_valori ',' valoare  */
#line 734 "proiect.y"
                                 {}
#line 2140 "parser.c"
    break;

  case 68: /* valoare: NR_INT  */
#line 737 "proiect.y"
                 {/*std::string expresie = std::to_string($1); // 
                    const char* plvar_stringm = expresie.c_str();
                    $$=(char*)var_string;*/
                    listavalori.push_back((yyvsp[0].Int));
                    }
#line 2150 "parser.c"
    break;

  case 69: /* valoare: NR_FLOAT  */
#line 742 "proiect.y"
                    {/* std::string expresie = std::to_string($1); // 
                    const char* var_string = expresie.c_str();
                    $$=(char*)var_string;*/
                    }
#line 2159 "parser.c"
    break;

  case 70: /* call_list: list  */
#line 748 "proiect.y"
                 { globalParamList.push_back((yyvsp[0].expr));
                   cout<<"LIST: "<<(yyvsp[0].expr)->type<<" "<<(yyvsp[0].expr)->floatvalue<<" "<<(yyvsp[0].expr)->intvalue<<endl;
                   
                  }
#line 2168 "parser.c"
    break;

  case 71: /* call_list: call_list ',' list  */
#line 752 "proiect.y"
                               {globalParamList.push_back((yyvsp[0].expr)); cout<<"LIST: "<<(yyvsp[0].expr)->type<<" "<<(yyvsp[0].expr)->floatvalue<<" "<<(yyvsp[-2].expr)->intvalue<<endl; }
#line 2174 "parser.c"
    break;

  case 72: /* list: NR_INT  */
#line 755 "proiect.y"
          {
                Expr* newExpr = new Expr();
                newExpr->type="int";
                newExpr->intvalue = (yyvsp[0].Int);
                (yyval.expr) = newExpr; 
          }
#line 2185 "parser.c"
    break;

  case 73: /* list: NR_FLOAT  */
#line 761 "proiect.y"
                    {Expr* newExpr = new Expr();
                newExpr->type="float";
                newExpr->floatvalue = (yyvsp[0].Float);
                (yyval.expr) = newExpr; 
          }
#line 2195 "parser.c"
    break;

  case 74: /* list: ID  */
#line 766 "proiect.y"
               { 
               
               const char* varType;
               const char* scope;
               if(scopeStack.empty()){ //ma aflu in scope Global
                     scope= "";
                     varType = listSymbols.getTypeOfVariable((yyvsp[0].String),scope);
               }else{
                     scope=scopeStack.top();
                     varType = listSymbols.getTypeOfVariable((yyvsp[0].String),scope);
               }

               cout<<varType<<" "<<(yyvsp[0].String)<<endl;
               if(varType!=nullptr){
                    //var a fost gasita
               Expr* newExpr = new Expr();
               newExpr->type=varType;
               (yyval.expr) = newExpr;
                    }else{
                         yyerror("Eror var not exist");
                         Expr* newExpr = new Expr();
                         (yyval.expr) = newExpr;
                    }
               

          }
#line 2226 "parser.c"
    break;

  case 75: /* EXPRESII: EXPRESIE_ARIT  */
#line 801 "proiect.y"
                         { 
               (yyval.expr)=(yyvsp[0].expr);
                    }
#line 2234 "parser.c"
    break;

  case 76: /* EXPRESII: EXPRESIE_BOOL  */
#line 804 "proiect.y"
                        {
          if(count_noduri<=1)
          {
               Expr* newExpr = new Expr();
               newExpr->boolvalue=(yyvsp[0].Bool);
               newExpr->value=to_string((yyvsp[0].Bool)).c_str();
               newExpr->type="bool";
               
              // cout<<"bool rez from EXPRESII: "<<newExpr->boolvalue<<endl;
               (yyval.expr)=newExpr;
          }    
          else {
               //cout<<"bb"<<endl;
               Expr* newExpr = new Expr();
                 newExpr->type="bool";
                  (yyval.expr)=newExpr;
          }
         }
#line 2257 "parser.c"
    break;

  case 77: /* EXPRESIE_ARIT: EXPR  */
#line 823 "proiect.y"
                     {(yyval.expr)=(yyvsp[0].expr);}
#line 2263 "parser.c"
    break;

  case 78: /* EXPRESIE_ARIT: EXPR OP EXPRESIE_ARIT  */
#line 824 "proiect.y"
                                 {}
#line 2269 "parser.c"
    break;

  case 79: /* EXPR: NR_INT  */
#line 828 "proiect.y"
             { std::string expresie = to_string((yyvsp[0].Int)); // Convertiți numărul în șir de caractere
                    infixExpr += expresie;
                    count_noduri++;
                    if(!type_expresie_curenta.empty() && type_expresie_curenta!="int"){
                         yyerror("Error right value differites types");
                    }
                  type_expresie_curenta="int";

                  Expr* newExpr = new Expr();
                  newExpr->value=expresie.c_str();
                  newExpr->type="int";
                  newExpr->intvalue=(yyvsp[0].Int);
                  (yyval.expr)=newExpr;
         }
#line 2288 "parser.c"
    break;

  case 80: /* EXPR: NR_FLOAT  */
#line 842 "proiect.y"
                {std::string expresie = to_string((yyvsp[0].Float)); // Convertiți numărul în șir de caractere
                    infixExpr += expresie;
                    count_noduri++;
                    
                    if(!type_expresie_curenta.empty() && type_expresie_curenta!="float"){
                         yyerror("Error right value differites types");
                    }
                    type_expresie_curenta="float";

                     Expr* newExpr = new Expr();
                     newExpr->value=expresie.c_str();
                     newExpr->type="float";
                     newExpr->floatvalue=(yyvsp[0].Float);
                     (yyval.expr)=newExpr;
                    }
#line 2308 "parser.c"
    break;

  case 81: /* EXPR: VARIABLE  */
#line 857 "proiect.y"
                {(yyval.expr)=(yyvsp[0].expr);}
#line 2314 "parser.c"
    break;

  case 82: /* EXPR: PARANTEZA_DESCHISA EXPRESIE_ARIT PARANTEZA_INCHISA  */
#line 858 "proiect.y"
                                                          {(yyval.expr)=(yyvsp[-1].expr); }
#line 2320 "parser.c"
    break;

  case 83: /* VARIABLE: ID  */
#line 872 "proiect.y"
              {
               const char* varType;
               const char* scope;
               if(scopeStack.empty()){ //ma aflu in scope Global
                     scope= "";
                     varType = listSymbols.getTypeOfVariable((yyvsp[0].String),scope);
               }else{
                     scope=scopeStack.top();
                     varType = listSymbols.getTypeOfVariable((yyvsp[0].String),scope);
               }
          cout<<"var: "<<varType<<" "<<(yyvsp[0].String)<<" scope: "<<scope<<" ----- "<<endl;
          Expr* newExpr = new Expr();

               if(varType!=nullptr){
                       //var a fost gasita
                         if(!type_expresie_curenta.empty() && type_expresie_curenta!=varType){
                         yyerror("Error right value differites types");
                         (yyval.expr)=newExpr;
                         break;
                         }
                         type_expresie_curenta=varType;
                         
                         
                         string valoarea_in_string=listSymbols.getValueOfVariable(varType,(yyvsp[0].String),scope);
                       
                         newExpr->value=valoarea_in_string.c_str();
                         newExpr->type=varType;
                         cout<<"Type var : "<<newExpr->type<<"  value: "<<newExpr->value<<endl; 
                         if(type_expresie_curenta=="float"){
                              newExpr->floatvalue=strtof(newExpr->value,nullptr);
                              cout<<"float type "<<endl;
                         }else if(type_expresie_curenta == "int"){                            
                              newExpr->intvalue=atoi(newExpr->value);
                              cout<<"int type "<<newExpr->intvalue<<endl;
                         }else if(type_expresie_curenta == "bool"){
                              if(strcmp(newExpr->value,"1")==0){                               
                                   newExpr->boolvalue=true;
                                   
                              }else{
                                   newExpr->boolvalue=false;
                              }
                                 
                              cout<<"final value din EXPR "<<newExpr->boolvalue<<endl;
                         }
                         
                          infixExpr += valoarea_in_string;
                          count_noduri++;
                         (yyval.expr)=newExpr;

               }else{
                    yyerror("Error var dosent def");
                    (yyval.expr)=newExpr;
               }
            
          }
#line 2380 "parser.c"
    break;

  case 84: /* PARANTEZA_DESCHISA: '('  */
#line 927 "proiect.y"
                         { infixExpr += '(';}
#line 2386 "parser.c"
    break;

  case 85: /* PARANTEZA_INCHISA: ')'  */
#line 929 "proiect.y"
                         { infixExpr += ')';}
#line 2392 "parser.c"
    break;

  case 86: /* OP: PLUS  */
#line 931 "proiect.y"
           {(yyval.Char)='+';  infixExpr += '+';}
#line 2398 "parser.c"
    break;

  case 87: /* OP: MINUS  */
#line 932 "proiect.y"
           {(yyval.Char)='-';  infixExpr += '-';}
#line 2404 "parser.c"
    break;

  case 88: /* OP: MUL  */
#line 933 "proiect.y"
           {(yyval.Char)='*';  infixExpr += '*';}
#line 2410 "parser.c"
    break;

  case 89: /* OP: DIV  */
#line 934 "proiect.y"
           {(yyval.Char)='/';  infixExpr += '/';}
#line 2416 "parser.c"
    break;

  case 90: /* OP: MOD  */
#line 935 "proiect.y"
           {(yyval.Char)='%';  infixExpr += '%';}
#line 2422 "parser.c"
    break;

  case 91: /* EXPRESIE_BOOL: EXPR_BOOL  */
#line 938 "proiect.y"
                         {(yyval.Bool)=(yyvsp[0].Bool);}
#line 2428 "parser.c"
    break;

  case 92: /* EXPRESIE_BOOL: EXPR_BOOL OP_LOGIC EXPRESIE_BOOL  */
#line 939 "proiect.y"
                                                 {
              
              /* if(strcmp($2,"&&")==0){
                    bool rez = ($1 && $3);
                    $$=rez;
               }else if(strcmp($2,"||")==0){
                     bool rez = ($1 || $3);
                    $$=rez;
               }else {
                    yyerror("Error EXPR_BOOL");
                    $$=false;
               }
               */
              }
#line 2447 "parser.c"
    break;

  case 93: /* EXPRESIE_BOOL: VARIABLE OP_LOGIC VARIABLE  */
#line 953 "proiect.y"
                                           {
             
               /*if(strcmp($2,"&&")==0){
                    bool rez = ($1->boolvalue && $3->boolvalue);
                    $$=rez;
               }else if(strcmp($2,"||")==0){
                    bool rez = ($1->boolvalue || $3->boolvalue);
                    $$=rez;
               }else {
                    yyerror("Error EXPR_BOOL");
                    $$=false;
               }*/
              }
#line 2465 "parser.c"
    break;

  case 94: /* EXPRESIE_BOOL: VARIABLE OP_LOGIC EXPRESIE_BOOL  */
#line 966 "proiect.y"
                                               {

              }
#line 2473 "parser.c"
    break;

  case 95: /* EXPRESIE_BOOL: EXPR_BOOL OP_LOGIC VARIABLE  */
#line 969 "proiect.y"
                                           {}
#line 2479 "parser.c"
    break;

  case 96: /* EXPR_BOOL: BOOLEAN  */
#line 976 "proiect.y"
          {
               //type_expresie_curenta="bool";
               infixExpr+=to_string((yyvsp[0].Bool));
               count_noduri++;
               (yyval.Bool)=(yyvsp[0].Bool);  
          }
#line 2490 "parser.c"
    break;

  case 97: /* EXPR_BOOL: PARANTEZA_DESCHISA EXPRESIE_BOOL PARANTEZA_INCHISA  */
#line 982 "proiect.y"
                                                               { /*$$=$2;*/}
#line 2496 "parser.c"
    break;

  case 98: /* EXPR_BOOL: EXPR_COMP  */
#line 983 "proiect.y"
                      {}
#line 2502 "parser.c"
    break;

  case 99: /* EXPR_COMP: EXPRESIE_ARIT OP_COMP EXPRESIE_ARIT  */
#line 986 "proiect.y"
          { 
               //cout<<" dddd "<<endl;
           /*bool value;
            if(strcmp($1->type,$3->type)==0)
            {  
               string expr_type=$1->type;
               if(strcmp($2,"<")==0){
                    if(expr_type=="int"){
                        value = $1->intvalue < $3->intvalue;
                    }else if(expr_type =="float"){
                        value = $1->floatvalue < $3->floatvalue;
                    }

               }else if(strcmp($2,"<=")==0){
                    if(expr_type=="int"){
                        value = $1->intvalue <= $3->intvalue;
                    }else if(expr_type =="float"){
                        value = $1->floatvalue <= $3->floatvalue;
                    }     
               }else if(strcmp($2,">")==0){
                    if(expr_type=="int"){
                        value = $1->intvalue > $3->intvalue;
                    }else if(expr_type =="float"){
                        value = $1->floatvalue > $3->floatvalue;
                    }     
               }else if(strcmp($2,">=")==0){
                    if(expr_type=="int"){
                        value = $1->intvalue >= $3->intvalue;
                    }else if(expr_type =="float"){
                        value = $1->floatvalue >= $3->floatvalue;
                    }     
               }else if(strcmp($2,"=")==0){
                    if(expr_type=="int"){
                        value = $1->intvalue = $3->intvalue;
                    }else if(expr_type =="float"){
                        value = $1->floatvalue = $3->floatvalue;
                    }     
               }else if(strcmp($2,"!=")==0){
                     if(expr_type=="int"){
                        value = $1->intvalue != $3->intvalue;
                    }else if(expr_type =="float"){
                        value = $1->floatvalue != $3->floatvalue;
                    }   
               }
            }else{
               yyerror("Error comp diferites typees");
                     value=false;
            }
            cout<<"-- comp --"<<value<<endl;
            $$=value;*/
          }
#line 2558 "parser.c"
    break;

  case 100: /* OP_COMP: LESS  */
#line 1038 "proiect.y"
                    { (yyval.oper) = "<";  infixExpr += "<"; }
#line 2564 "parser.c"
    break;

  case 101: /* OP_COMP: LESS_EQ  */
#line 1039 "proiect.y"
                    { (yyval.oper) = "<="; infixExpr += "<="; }
#line 2570 "parser.c"
    break;

  case 102: /* OP_COMP: GRT  */
#line 1040 "proiect.y"
                    { (yyval.oper) = ">";  infixExpr += ">"; }
#line 2576 "parser.c"
    break;

  case 103: /* OP_COMP: GRT_EQ  */
#line 1041 "proiect.y"
                    { (yyval.oper) = ">="; infixExpr += ">="; }
#line 2582 "parser.c"
    break;

  case 104: /* OP_COMP: EQ  */
#line 1042 "proiect.y"
                    { (yyval.oper) = "=";  infixExpr += "="; }
#line 2588 "parser.c"
    break;

  case 105: /* OP_COMP: NOT_EQ  */
#line 1043 "proiect.y"
                    { (yyval.oper) = "!="; infixExpr += "!="; }
#line 2594 "parser.c"
    break;

  case 106: /* OP_LOGIC: LOGIC_AND  */
#line 1046 "proiect.y"
                      { (yyval.oper) = "&&"; infixExpr+="&&";}
#line 2600 "parser.c"
    break;

  case 107: /* OP_LOGIC: LOGIC_OR  */
#line 1047 "proiect.y"
                      { (yyval.oper) = "||"; infixExpr+="||";}
#line 2606 "parser.c"
    break;

  case 108: /* RIGHT_VALUE: EXPRESII  */
#line 1050 "proiect.y"
            {
     if (error_flag == 0) {
          if (count_noduri >= 2) {
          
            cout << "Expr infix: " << infixExpr << endl;
            string postfix = infixToPostfix(infixExpr);
            cout << "Postfix : " << postfix << endl;
            Radacina = buildAST(postfix);
            cout << "Radacina : " << Radacina->op << endl;

            if (type_expresie_curenta == "float" || type_expresie_curenta == "int" || type_left_value == "bool") {
                cout << "Evaluare " << type_expresie_curenta << endl;
                // Evitați utilizarea auto
                // auto result;
                Expr* resultExpr;

                if (type_left_value == "int") {
                    // Utilizați tipul de date corespunzător
                    int result = evalExpr<int>(Radacina);
                    resultExpr = new Expr();
                    resultExpr->intvalue = result;
                    resultExpr->value = std::to_string(result).c_str();
                    resultExpr->type = "int";
                } else if (type_left_value == "float") {
                    float result = evalExpr<float>(Radacina);
                    resultExpr = new Expr();
                    resultExpr->floatvalue = result;
                    resultExpr->value = std::to_string(result).c_str();
                    resultExpr->type = "float";
                } else if (type_left_value == "bool" && (type_expresie_curenta =="int" || type_left_value == "float")){
                    int result = evalExpr<int>(Radacina);
                    resultExpr = new Expr();
                    resultExpr->boolvalue = (bool)result;
                    resultExpr->value = std::to_string(result).c_str();
                    resultExpr->type = "bool";
                }else if (type_left_value =="bool"){ 
                    bool result = evalExpr<bool>(Radacina);
                    resultExpr = new Expr();
                    resultExpr->boolvalue = (bool)result;
                    resultExpr->value = std::to_string(result).c_str();
                    resultExpr->type = "bool";
                }else {
                    yyerror("Error left type value");
                    Expr* newExpr = new Expr();
                    (yyval.expr) = newExpr;
                    break;
                }

                if (resultExpr->type == "int") {
                    cout << "Evaluare Rezultat (int): " << resultExpr->intvalue << endl;
                } else if (resultExpr->type == "float") {
                    cout << "Evaluare Rezultat (float): " << resultExpr->floatvalue << endl;
                } else if (resultExpr->type == "bool") {
                    cout << "Evaluare Rezultat (bool): " << resultExpr->boolvalue << endl;
                }

                (yyval.expr) = resultExpr;
            }else {
            cout<<"<<<<1"<<endl;
            yyerror("Error diferents type1"); 
            Expr* newExpr = new Expr();
            (yyval.expr) = newExpr; }
          }else{
               cout<<"<<<<2"<<endl;
            (yyval.expr)=(yyvsp[0].expr);
          }
        
     } else {
          cout<<"<<<<3"<<endl;
         yyerror("Error diferents type2");     
         Expr* newExpr = new Expr();
         (yyval.expr) = newExpr;
     }

        type_expresie_curenta.clear();
        infixExpr.clear();
        count_noduri = 0;
          

            }
#line 2691 "parser.c"
    break;

  case 109: /* LEFT_VALUE: ID  */
#line 1131 "proiect.y"
                {
               const char* varType;
               const char* scope;
               if(scopeStack.empty()){ //ma aflu in scope Global
                     scope= "";
                     varType = listSymbols.getTypeOfVariable((yyvsp[0].String),scope);
               }else{
                     scope=scopeStack.top();
                     varType = listSymbols.getTypeOfVariable((yyvsp[0].String),scope);
               }

               type_left_value=varType;
               cout<<"type left: "<<type_left_value<<" "<<(yyvsp[0].String);
               if(varType!=nullptr && error_flag == 0){
                    //var a fost gasita
                    //type_left_value = varType;

                    cout<<"Type var : "<<varType<<endl;
                    Expr* newExpr = new Expr();
                    newExpr->type=varType;
                    newExpr->name=(yyvsp[0].String);
                    (yyval.expr)=newExpr;

               }else{
                    yyerror("Eror var dosent def");
               }
          }
#line 2723 "parser.c"
    break;

  case 110: /* block: statement ';'  */
#line 1163 "proiect.y"
                     {printf("statement\n");}
#line 2729 "parser.c"
    break;

  case 112: /* statement: LEFT_VALUE ASSIGN RIGHT_VALUE  */
#line 1167 "proiect.y"
                                        { //ma asigur ca au acelasi tip,si abia dupa ii adaug valoarea.
             if(error_flag!=1)//nu am eroare
             {

               struct Expr* leftExpr = (yyvsp[-2].expr);
               struct Expr* rightExpr = (yyvsp[0].expr);
               if (strcmp(leftExpr->type, rightExpr->type) != 0) {
                   yyerror("Type mismatch in assignment.");
               } else {
                   // Continuați procesarea instrucțiunii de atribuire
                   
                    listSymbols.addValue((yyvsp[-2].expr)->type,(yyvsp[-2].expr)->name,(yyvsp[0].expr)->value);
               }
             }
          }
#line 2749 "parser.c"
    break;

  case 113: /* statement: apel_functie  */
#line 1182 "proiect.y"
                        { 
          if ((yyvsp[0].String) == nullptr){cout<<"Eror"<<endl;}
          for(Expr* expr : globalParamList){
                          delete expr; 
                          expr=nullptr;
                          
                        }
                        cout<<"S-a deal GPL STMT"<<endl;
          }
#line 2763 "parser.c"
    break;

  case 119: /* statement_conditions: IF '(' CONDITION ')' '{' block '}'  */
#line 1199 "proiect.y"
                                                         {}
#line 2769 "parser.c"
    break;

  case 121: /* statement_conditions: WHILE '(' CONDITION ')' '{' block '}'  */
#line 1201 "proiect.y"
                                                      { }
#line 2775 "parser.c"
    break;

  case 122: /* statement_conditions: FOR '(' variable_def ';' EXPR_BOOL ';' EXPR ';' ')' '{' block '}'  */
#line 1202 "proiect.y"
                                                                                  { }
#line 2781 "parser.c"
    break;

  case 123: /* CONDITION: EXPR_BOOL  */
#line 1204 "proiect.y"
                      { cout<<"Condition statement: "  <<(yyvsp[0].Bool)<<endl;}
#line 2787 "parser.c"
    break;


#line 2791 "parser.c"

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

#line 1210 "proiect.y"


void yyerror(const char * eroare){
     error_flag=1;
printf("\neroare la linia %d : %d : %s \n", line_no+1, ch_no, eroare);
}

int main(int argc, char** argv){
     yyin=fopen(argv[1],"r");
     yyparse();
     
     listSymbols.printSymbolTable("out.txt");
    
}

%{
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
 %}

%union {
     char* name;
     char* tip_data;

     int Int;
     float Float;
     bool Bool;
     char* String;
     const char* oper;
     const char* NameClas;
     char Char;
     struct Expr* expr;
     struct ASTnode* node;
}

%token IF ELSE WHILE FOR 
%token CLASS 
%token CONSTANT RETURN
%token EVAL TYPEOF BEGIN_PROGR END_PROGR ASSIGN
%token LOGIC_AND LOGIC_OR LESS LESS_EQ GRT GRT_EQ EQ NOT_EQ NOT 
%token PLUS MINUS MUL DIV MOD

%token<tip_data>  INT FLOAT CHAR STRING BOOL
%token<String> ID CLASS_ID FUN_ID
%token<Bool> BOOLEAN
%token<Int>NR_INT
%token<Float>NR_FLOAT



%left LOGIC_OR
%left LOGIC_AND
%right NOT
%left LESS GRT LESS_EQ GRT_EQ EQ NOT_EQ
%left '+' '-'
%left '*' '/' '%'

%left '(' ')'
%left '{' '}'
%left '[' ']'

%start progr
%type <tip_data> tip_variabila 

%type <String>object_decl class_header list_param param apel_functie   valoare
%type <String>variable array_decl array_init constant_def variable_decl variable_def
%type <NameClas>obj_id 
%type <expr>call_list list EXPRESII RIGHT_VALUE LEFT_VALUE EXPR EXPRESIE_ARIT VARIABLE 
%type <Bool> EXPR_COMP EXPR_BOOL EXPRESIE_BOOL
%type <Char> OP 
%type <oper> OP_COMP OP_LOGIC
%type <String> array_usage object_usage
%%

// %type <Bool> EXPR_BOOL 
// %type <tip_data> EXPR 
progr: class_list declarations_glob_variable functions_glob_def main_fun {printf("The programme is sintactic correct!\n");}
     | declarations_glob_variable functions_glob_def main_fun {printf("The programme is sintactic correct!\n");}
     | functions_glob_def main_fun {printf("The programme is sintactic correct!\n");}
     | declarations_glob_variable main_fun {printf("The programme is sintactic correct!\n");}
     | class_list declarations_glob_variable main_fun {printf("The programme is sintactic correct!\n");}
     | class_list functions_glob_def main_fun {printf("The programme is sintactic correct!\n");}
     | class_list main_fun {printf("The programme is sintactic correct!\n");}
     | main_fun {printf("The programme is sintactic correct!\n");}
 
//declaation
declarations_glob_variable :  decl ';'          
	        |  declarations_glob_variable decl ';'   
             ;    
functions_glob_def : function_def ';' 
                   | functions_glob_def function_def ';'
                   ;
class_list: class_def 
           | class_list class_def  
           ;                   
main_fun : begin_progr block end_progr { }
          | begin_progr end_progr
         ;

begin_progr :   BEGIN_PROGR {cout<<"------------Begin Progr------------"<<endl; scopeStack.push("main");}
    ; 
end_progr :END_PROGR{cout<<"------------End Progr------------"<<endl; {if(!scopeStack.empty()){scopeStack.pop();}else{printf("Eror stack class\n");} }}
               ;     
decl      : variable  
          | object_decl
          ;
variable : variable_def
  | variable_decl
  | array_decl
  | array_init
  | constant_def
  ;
array_decl : tip_variabila ID '[' NR_INT ']' {
                        
                         const char* scope ="";
                         if(!scopeStack.empty()){ //ma aflu in scope ul global
                          
                           scope=scopeStack.top(); //clasa/tipul func

                                if(!listSymbols.existsVar($2,scope)){
                              listSymbols.addArray($1,$2,$4,scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }else {
                              if(!listSymbols.existsVar($2,scope)){
                              listSymbols.addArray($1,$2,$4,scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }
                    
                     } //unidimensional      
           | tip_variabila ID '[' NR_INT ']' '[' NR_INT ']' {
                   const char* scope ="";
                         if(!scopeStack.empty()){ //ma aflu in scope ul clasa
                          
                             scope=scopeStack.top(); //clasa

                                if(!listSymbols.existsVar($2,scope)){
                              listSymbols.addArray($1,$2,$4,$7,scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }else {
                              if(!listSymbols.existsVar($2,scope)){
                              listSymbols.addArray($1,$2,$4,$7,scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }
                     } //bidimensional
           ;

array_init :  tip_variabila ID '['']' ASSIGN '{' lista_valori '}' { 
          /* Logică inițializare */
              const char* scope ="";

                         if(!scopeStack.empty()){ //ma aflu in scope ul  global
                          
                           scope=scopeStack.top(); //clasa
                         
                                if(!listSymbols.existsVar($2,scope)){
                              listSymbols.initArray(listavalori,$1,$2,listavalori.size(),scope);
               
                                }
                              else{
                                   printf("Error at decl array 1\n"); }
                         }else {
                              if(!listSymbols.existsVar($2,scope)){
                               listSymbols.initArray(listavalori,$1,$2,listavalori.size(),scope);
                                }
                              else{
                                   printf("Error at decl array 2\n"); }
                         }
               listavalori.clear();   // Elimină toate elementele din vector
               listavalori.shrink_to_fit();  // Reduc capacitatea vectorului
          } 
           ;
array_usage : ID '[' dimensiune ']' 
               /*const char* varType = listSymbols.getTypeOfVariable($1);
               if(varType!=nullptr){
                    //var a fost gasita
                    cout<<"Type var : "<<varType<<endl;
                    $$->type=varType;
               }else{
                    cout<<"Eror var dosent def";
               }}*/
            | ID '[' dimensiune ']' '[' dimensiune ']' /*const char* varType = listSymbols.getTypeOfVariable($1);
               if(varType!=nullptr){
                    //var a fost gasita
                    cout<<"Type var : "<<varType<<endl;
                    $$->type=varType;
               }else{
                    cout<<"Eror var dosent def";
               }}*/
            ;

dimensiune : NR_INT
           ;

variable_decl :tip_variabila ID {
                   
                         
                         if(!scopeStack.empty()){ //ma aflu in scope ul  global
                          
                            const char* scope=scopeStack.top(); //clasa/functia/main
                              
                                if(!listSymbols.existsVar($2,scope)){
                              listSymbols.addVar($1,$2,scope);
                                }
                              else{
                                   printf("Error at decl var\n%s %s",$1,$2); }
                         }else {
                           const char*   scope ="";
                              if(!listSymbols.existsVar($2,scope)){
                              listSymbols.addVar($1,$2,scope);
                                }
                              else{
                                   printf("Error at decl var\n%s %s",$1,$2); }
                         }

                         //verific daca nu cumva este data membru;
                       //free($2);
                    }
              ; 
variable_def: tip_variabila ID ASSIGN RIGHT_VALUE  {   

                         //verific tipurile
                    //cout<<$1<<" [] "<<$4->type;
                    if(strcmp($1,$4->type)!=0){
                         yyerror("Error diferite types in variable");
                        
                    }else{

                         //adaug in symboltable
                         if(!scopeStack.empty()){ //nu ma aflu in scope ul  global
                          
                           const char*  scope=scopeStack.top(); //clasa
               
                                if(!listSymbols.existsVar($2,scope)){
                              listSymbols.addVar($1,$2,$4->value,scope);
                                }
                              else{
                                   yyerror("Error at decl var"); }
                         }else {//ma aflu in scope ul  global
                                const char* scope ="";
                              if(!listSymbols.existsVar($2,scope)){
                              listSymbols.addVar($1,$2,$4->value,scope);
                                }
                              else{
                                   yyerror("Error at decl var"); }
                         }
                        //printf("Definitia variabilei: %s de tipul %s cu valoarea initiala\n", $2, $1);
                        // Aici, expr ar trebui să fie evaluată și valoarea să fie stocată/atribuită variabilei
                    }
               }    
             ;
constant_def : CONSTANT tip_variabila ID ASSIGN RIGHT_VALUE {
               
               if(strcmp($2,$5->type)!=0){
                    yyerror("Eror diferite types");
                   
               }else{

                         
                                                // Presupunem că $5 este un Expr*
                         if(!scopeStack.empty()){ //ma aflu in scope ul  global
                          
                           const char* scope=scopeStack.top(); //clasa

                                if(!listSymbols.existsVar($2,scope)){
                              listSymbols.addVar(true,$2,$3,$5->value,scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }else {
                               const char* scope ="";
                              if(!listSymbols.existsVar($2,scope)){
                              listSymbols.addVar(true,$2,$3,$5->value,scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }
                    
                    //trebuie adaugat ca si o constanta,direct cu valoarea ei ,nr
               }
               }
              ;

tip_variabila : INT   {$$=$1; type_left_value=$1;}
              | FLOAT {$$=$1; type_left_value=$1;}
              | CHAR  {$$=$1; type_left_value=$1;}
              | STRING{$$=$1; type_left_value=$1;}
              | BOOL  {$$=$1; type_left_value=$1;}
              ;


//partea de clase:

class_def : class_header class_body '}' ';' { if(!scopeStack.empty()){scopeStack.pop();}else{printf("Eror stack class\n");} cout<<"de 1"<<endl;}
          //| class_def  class_header class_body '}' ';'{ if(!scopeStack.empty()){scopeStack.pop();}else{printf("Eror stack class\n");} }
          ;
class_header : CLASS CLASS_ID '{'  { 
             
               scopeStack.push($2);

             if(!listSymbols.existsClass($2)){
                  listSymbols.addClass($2);
             }else{
               printf("Eror,already class exists\n");
             }

             }
             
           ;
//class_id : {if(!scopeStack.empty()){ $$ = (char*)scopeStack.top();}else {printf("Eroar at stack class\n");}}
class_body :   data_members memmber_functions 
           ;

data_members : variable ';'
             | data_members variable ';'
             ;
memmber_functions : function_def_class ';' 
                  | memmber_functions function_def_class ';' 
                  ;

object_decl : CLASS_ID ID {/*cod pentru declararea unui obiect al clasei*/
                     if(listSymbols.addObjInClass($1,$2)){
                       
                    }else { cout<<"Eror decl obj"<<$2<<endl;}
               
               }
            ;
object_usage :  obj_id field_or_method_call {
               currentClass = nullptr; }
             ;
obj_id: ID '.'{
               //const char* className=scopeStack.top();          
               //daca apelz obiectul in main,clasa curenta va fi deja scoasa din scope
                 currentClass =listSymbols.gettypeObj($1).c_str();
               
                if(strcmp(currentClass,"")!=0){
                    //exist obiectul
                         $$ = currentClass;
                         cout<<$$<<endl; // Alocăm și setăm numele clasei
                    }else{
                         cout<<"Eror class is not decl"; $$ = nullptr;}

                }

          ;
field_or_method_call : ID { /* Accesare câmp */
                     //const char* className = $<NameClas>-1;// Obțineți numele clasei transmis
                     const char* fieldName = $1;  
                     cout<<currentClass<<" tipul obj: "<<$1<<endl;
                    if(listSymbols.existsVar($1,currentClass)){
                              //l am accesat
                    }else { cout<<"Nu exista acest camp in clasa "<<currentClass<<endl;}
                         }
                    // | FUN_ID '(' call_list ')' { }
                     | apel_functie{for(Expr* expr : globalParamList){
                          delete expr; 
                          expr=nullptr; 
                        }
                        cout<<"S-a dealocat globalParamList"<<endl;}
                      // Verificați dacă obiectul $1 are acces la metoda $3 a clasei sale și dacă metoda este apelată corect./* Apel metoda cu argumente */ }
                      // | FUN_ID '(' ')' { /* Apel metoda fără argumente */ }
                     | array_usage {}
                     ;

function_def : function_header function_body '}' { if(!scopeStack.empty()){scopeStack.pop();}else{printf("Eror stack class\n");} }
               ;
function_header : tip_variabila FUN_ID '(' list_param ')' '{' {
                    scopeStack.push($2);
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
                  
                   if(!listSymbols.existsFunc($1,$2,paramTypes,scope)){
                    listSymbols.addFunc($1,$2,paramTypes,scope);
                   }else { cout<<"Eror at func decl: "<<$1<<" "<<$2<<endl ;}
               } 
              ;
function_def_class : function_class_header function_body '}' {}
function_class_header :CLASS_ID tip_variabila FUN_ID '(' list_param ')' '{' {
                    
                    
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
                      if(!listSymbols.existsFunc($2,$3,paramTypes,classId)){
                        listSymbols.addFunc($2,$3,paramTypes,classId);
                      }
                      else{
                         cout<<"Eror at func decl: "<<$1<<" "<<$2<<" "<<$3<<endl ;
                      }
                    }else {cout<<"error la stiva";}       
               }
              ;
function_body : block {}
              ;
apel_functie : FUN_ID '(' call_list ')' { 

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
                    
                    string typeFunc = listSymbols.getTypeFunc(scope,$1,paramTypes,scope);  /*scope="" inseamna ca e global*/
                        cout<<typeFunc<<endl;
                        if(typeFunc == ""){
                              yyerror("Eror cant call inexistent fun");
                              $$=nullptr;
                        }else{
                         cout<<"Can call fun "<<$1<<endl;
                         const char* returnType = typeFunc.c_str();
                         $$=(char*)returnType;
                        }
                    //$$ trebuie sa prineasca return type ul,pt a puea asigna functia;
                    }else { //apel de metoda
                     //cout<<"HELLO1"<<endl;
                         const char * scope="";
                           string typeFunc = listSymbols.getTypeFunc(scope,$1,paramTypes,currentClass);  /*scope="" inseamna ca e global*/
                        if(typeFunc == ""){
                              yyerror("Eror cant call inexistent fun");
                              $$=nullptr;
                        }else{
                         cout<<"Can call fun "<<$1<<" tipul metodei: "<<currentClass<<endl;
                         const char* returnType = typeFunc.c_str();
                         $$=(char*)returnType;
                        }

                    }
                      //if(globalParamList.size()>0)                        
                     globalParamList.clear(); 
               }
             ;

list_param : param { listTypeParamQueue.push($1); printf("|%s|\n",$1);}
           | list_param ','  param {listTypeParamQueue.push($3); printf("|%s|\n",$3);}
           ;
            
param : tip_variabila ID {$$ = $1; }
      | object_decl
      | array_decl
      | constant_def
      ; 

lista_valori : valoare {}
       | lista_valori ',' valoare{}
       ;

valoare : NR_INT {
                    listavalori.push_back($1);
                    }
        | NR_FLOAT  {
                    }
        ;

call_list : list { globalParamList.push_back($1);
                   cout<<"LIST: "<<$1->type<<" "<<$1->floatvalue<<" "<<$1->intvalue<<endl;
                   
                  }
          | call_list ',' list {globalParamList.push_back($3); cout<<"LIST: "<<$3->type<<" "<<$3->floatvalue<<" "<<$1->intvalue<<endl; }
          ;
list      :NR_INT 
          {
                Expr* newExpr = new Expr();
                newExpr->type="int";
                newExpr->intvalue = $1;
                $$ = newExpr; 
          }
          | NR_FLOAT{Expr* newExpr = new Expr();
                newExpr->type="float";
                newExpr->floatvalue = $1;
                $$ = newExpr; 
          }
          | ID { 
               
               const char* varType;
               const char* scope;
               if(scopeStack.empty()){ //ma aflu in scope Global
                     scope= "";
                     varType = listSymbols.getTypeOfVariable($1,scope);
               }else{
                     scope=scopeStack.top();
                     varType = listSymbols.getTypeOfVariable($1,scope);
               }

               cout<<varType<<" "<<$1<<endl;
               if(varType!=nullptr){
                    //var a fost gasita
               Expr* newExpr = new Expr();
               newExpr->type=varType;
               $$ = newExpr;
                    }else{
                         yyerror("Eror var not exist");
                         Expr* newExpr = new Expr();
                         $$ = newExpr;
                    }
               

          }
          ;

/*call_list : EXPRESII 
          | object_decl
          | call_list ',' object_decl
          | call_list ',' EXPRESII
          ;
*/

EXPRESII : EXPRESIE_ARIT { 
               $$=$1;
                    }
         | EXPRESIE_BOOL{
          if(count_noduri<=1)
          {
               Expr* newExpr = new Expr();
               newExpr->boolvalue=$1;
               newExpr->value=to_string($1).c_str();
               newExpr->type="bool";
               
              // cout<<"bool rez from EXPRESII: "<<newExpr->boolvalue<<endl;
               $$=newExpr;
          }    
          else {
               //cout<<"bb"<<endl;
               Expr* newExpr = new Expr();
                 newExpr->type="bool";
                  $$=newExpr;
          }
         }
         ;
EXPRESIE_ARIT : EXPR {$$=$1;}
         | EXPR OP EXPRESIE_ARIT {}
         ;

EXPR : 
      NR_INT { std::string expresie = to_string($1); // Convertiți numărul în șir de caractere
                    infixExpr += expresie;
                    count_noduri++;
                    if(!type_expresie_curenta.empty() && type_expresie_curenta!="int"){
                         yyerror("Error right value differites types");
                    }
                  type_expresie_curenta="int";

                  Expr* newExpr = new Expr();
                  newExpr->value=expresie.c_str();
                  newExpr->type="int";
                  newExpr->intvalue=$1;
                  $$=newExpr;
         }
     | NR_FLOAT {std::string expresie = to_string($1); // Convertiți numărul în șir de caractere
                    infixExpr += expresie;
                    count_noduri++;
                    
                    if(!type_expresie_curenta.empty() && type_expresie_curenta!="float"){
                         yyerror("Error right value differites types");
                    }
                    type_expresie_curenta="float";

                     Expr* newExpr = new Expr();
                     newExpr->value=expresie.c_str();
                     newExpr->type="float";
                     newExpr->floatvalue=$1;
                     $$=newExpr;
                    }
     | VARIABLE {$$=$1;}
     | PARANTEZA_DESCHISA EXPRESIE_ARIT PARANTEZA_INCHISA {$$=$2; }  
          //| array_usage {}
         // | object_usage
          ;
VARIABLE : ID {
               const char* varType;
               const char* scope;
               if(scopeStack.empty()){ //ma aflu in scope Global
                     scope= "";
                     varType = listSymbols.getTypeOfVariable($1,scope);
               }else{
                     scope=scopeStack.top();
                     varType = listSymbols.getTypeOfVariable($1,scope);
               }
          cout<<"var: "<<varType<<" "<<$1<<" scope: "<<scope<<" ----- "<<endl;
          Expr* newExpr = new Expr();

               if(varType!=nullptr){
                       //var a fost gasita
                         if(!type_expresie_curenta.empty() && type_expresie_curenta!=varType){
                         yyerror("Error right value differites types");
                         $$=newExpr;
                         break;
                         }
                         type_expresie_curenta=varType;
                         
                         
                         string valoarea_in_string=listSymbols.getValueOfVariable(varType,$1,scope);
                       
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
                         $$=newExpr;

               }else{
                    yyerror("Error var dosent def");
                    $$=newExpr;
               }
            
          }
PARANTEZA_DESCHISA : '(' { infixExpr += '(';}
                   ;
PARANTEZA_INCHISA : ')'  { infixExpr += ')';}
                   ;
OP : PLUS  {$$='+';  infixExpr += '+';}
   | MINUS {$$='-';  infixExpr += '-';}
   | MUL   {$$='*';  infixExpr += '*';}
   | DIV   {$$='/';  infixExpr += '/';}
   | MOD   {$$='%';  infixExpr += '%';}
   ;

EXPRESIE_BOOL : EXPR_BOOL{$$=$1;}
              | EXPR_BOOL OP_LOGIC  EXPRESIE_BOOL{
              }
              | VARIABLE OP_LOGIC VARIABLE {
              }
              | VARIABLE OP_LOGIC EXPRESIE_BOOL{

              }
              | EXPR_BOOL OP_LOGIC VARIABLE{}

              ;
EXPR_BOOL : BOOLEAN 
          {
               //type_expresie_curenta="bool";
               infixExpr+=to_string($1);
               count_noduri++;
               $$=$1;  
          }       
          | PARANTEZA_DESCHISA EXPRESIE_BOOL PARANTEZA_INCHISA { /*$$=$2;*/}   
          | EXPR_COMP {}
          ;
EXPR_COMP : EXPRESIE_ARIT OP_COMP EXPRESIE_ARIT 
          { 
               
          }
          ;
OP_COMP :  LESS     { $$ = "<";  infixExpr += "<"; }
        |  LESS_EQ  { $$ = "<="; infixExpr += "<="; }
        |  GRT      { $$ = ">";  infixExpr += ">"; }
        |  GRT_EQ   { $$ = ">="; infixExpr += ">="; }
        |  EQ       { $$ = "=";  infixExpr += "="; }
        |  NOT_EQ   { $$ = "!="; infixExpr += "!="; }
        ;

OP_LOGIC : LOGIC_AND  { $$ = "&&"; infixExpr+="&&";}
         | LOGIC_OR   { $$ = "||"; infixExpr+="||";}
         ;
RIGHT_VALUE : EXPRESII //atribui tipul si valoarea lui right value
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
                    $$ = newExpr;
                    break;
                }

                if (resultExpr->type == "int") {
                    cout << "Evaluare Rezultat (int): " << resultExpr->intvalue << endl;
                } else if (resultExpr->type == "float") {
                    cout << "Evaluare Rezultat (float): " << resultExpr->floatvalue << endl;
                } else if (resultExpr->type == "bool") {
                    cout << "Evaluare Rezultat (bool): " << resultExpr->boolvalue << endl;
                }

                $$ = resultExpr;
            }else {
            cout<<"<<<<1"<<endl;
            yyerror("Error diferents type1"); 
            Expr* newExpr = new Expr();
            $$ = newExpr; }
          }else{
               cout<<"<<<<2"<<endl;
            $$=$1;
          }
        
     } else {
          cout<<"<<<<3"<<endl;
         yyerror("Error diferents type2");     
         Expr* newExpr = new Expr();
         $$ = newExpr;
     }

        type_expresie_curenta.clear();
        infixExpr.clear();
        count_noduri = 0;
          

            }
            ;
LEFT_VALUE : ID {
               const char* varType;
               const char* scope;
               if(scopeStack.empty()){ //ma aflu in scope Global
                     scope= "";
                     varType = listSymbols.getTypeOfVariable($1,scope);
               }else{
                     scope=scopeStack.top();
                     varType = listSymbols.getTypeOfVariable($1,scope);
               }

               type_left_value=varType;
               cout<<"type left: "<<type_left_value<<" "<<$1;
               if(varType!=nullptr && error_flag == 0){
                    //var a fost gasita
                    //type_left_value = varType;

                    cout<<"Type var : "<<varType<<endl;
                    Expr* newExpr = new Expr();
                    newExpr->type=varType;
                    newExpr->name=$1;
                    $$=newExpr;

               }else{
                    yyerror("Eror var dosent def");
               }
          }
          // | object_usage
          // | array_usage
           ;
//Statements
   
block: statement ';' {printf("statement\n");}
     | block statement ';'
     ;

statement: LEFT_VALUE ASSIGN RIGHT_VALUE{ //ma asigur ca au acelasi tip,si abia dupa ii adaug valoarea.
             if(error_flag!=1)//nu am eroare
             {

               struct Expr* leftExpr = $1;
               struct Expr* rightExpr = $3;
               if (strcmp(leftExpr->type, rightExpr->type) != 0) {
                   yyerror("Type mismatch in assignment.");
               } else {
                   // Continuați procesarea instrucțiunii de atribuire
                   
                    listSymbols.addValue($1->type,$1->name,$3->value);
               }
             }
          } 
         | apel_functie { 
          if ($1 == nullptr){cout<<"Eror"<<endl;}
          for(Expr* expr : globalParamList){
                          delete expr; 
                          expr=nullptr;
                          
                        }
                        cout<<"S-a deal GPL STMT"<<endl;
          }//pot apela o functie
         
         | object_usage //pot sa apelez un obict de clasa
         | statement_conditions
         | decl 
         | eval_statement
         | typeof_statement
         ;

statement_conditions : IF '(' CONDITION ')' '{' block '}'{}
             | IF '(' CONDITION ')' '{' block '}' ELSE '{' block '}' 
             | WHILE '(' CONDITION ')' '{' block '}'  { }
             | FOR '(' variable_def ';' EXPR_BOOL ';'  EXPR ';' ')' '{' block '}' { }
             ;
CONDITION : EXPR_BOOL { cout<<"Condition statement: "  <<$1<<endl;}
          ;
eval_statement : EVAL '(' RIGHT_VALUE ')'
               ;
typeof_statement : TYPEOF '(' RIGHT_VALUE ')'
                 ;
%%

void yyerror(const char * eroare){
     error_flag=1;
printf("\neroare la linia %d : %d : %s \n", line_no+1, ch_no, eroare);
}

int main(int argc, char** argv){
     yyin=fopen(argv[1],"r");
     yyparse();
     
     listSymbols.printSymbolTable("out.txt");
    
}

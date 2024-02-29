#include <iostream>
#include <vector>
#include <map>
#include <string>
#include<cstring>
#include <fstream>
#include <variant>
#include <cstdlib>
#include <stack>
#include <queue>
using namespace std;

struct VarInfo {
    string type;      // Tipul variabilei (ex: int, float, bool, etc.)
    string name;      // Numele variabilei
    string value;     // Valoarea variabilei sub formă de șir de caractere
    //string scope;     // Numele funcției sau clasei în care variabila este definită
    int dimensions[2]={0,0};// Dimensiuni pentru array-uri, cu -1 în cazul variabilelor simple
    string className; //or function name
    bool isConstant;
    vector<int> value_from_array;
};
struct FuncInfo {
    string name;
    string returnType;
    vector<const char *> paramTypes; // Tipurile parametrilor
    // Alte informații necesare
    string className; //sau globale


};
struct ClassId {
    string className;
    vector<const char*> objects;
};
class SymbolTable {
    vector<VarInfo> vars;
    vector<FuncInfo> funcs; // Informații despre funcții
    vector<ClassId> Clas;
   // map<string,ClassInfo> clases;
    public:

    bool existsVar(const char* name,const char* className);
    void addVar(const char* type, const char*name , const char* className);
    void addVar(const char* type, const char*name,const char* value,const char* className);
    void addVar(bool isConstant ,const char* type, const char*name,const char* value,const char* className);   
    void addArray(const char* type, const char*name,int capacity1,const char* className);
    void addArray(const char* type, const char*name,int capacity1,int capacity2,const char* className);
    void addValue(const char* type, const char*name,const char* value);
    void initArray(const vector<int> values,const char* type, const char*name,int capacity1,const char* className);
    const char* getTypeOfVariable(const char* varName,const char* scope);   
    string getValueOfVariable(const char* type,const char* varName,const char* scope);
    //fun
    void addFunc(const char* returnType, const char* name, const vector<const char *>& paramTypes,const char* className);
    bool existsFunc(const char* returnType, const char* name, const vector<const char *>& paramTypes,const char* className);
    string getTypeFunc(const char* returnType, const char* name, const vector<const char *>& paramTypes,const char* className);
    //class
    void addClass(const char* className);
    bool existsClass(const char* className);
    bool addObjInClass(const char* className,const char* numeObiect);
    string gettypeObj(const char* numeObiect);   

    void printSymbolTable(const string& filename);
    ~SymbolTable();
};

//AST
struct Expr{
    const char* type;
    const char* name;
    const char* value;
    
    int intvalue;
    float floatvalue;
    bool boolvalue;
    char charvalue;
    char *strvalue;

};

/*

enum Type
{
    OPERATOR,
    NUMBER,
    IDENTIFIER,
    OTHER
};

struct root_data
{
    char op;
    struct Expr *expr_ptr;
    int number;
    char *other;
};



class ASTnode
{
    int exprtype;
    struct root_data *root;
    ASTnode *left;
    ASTnode *right;

    ASTnode *BuildAST(struct root_data *root, ASTnode *left, ASTnode *right, int type)
    {
        ASTnode *newnode = new ASTnode;
        newnode->root = root;
        newnode->exprtype = type;
        newnode->left = left;
        newnode->right = right;
        return newnode;
    }
    int Eval(ASTnode *node)
    {
        if (node->exprtype == Type::NUMBER)
            return node->root->number;
        else if (node->exprtype == Type::IDENTIFIER)
            return node->root->expr_ptr->intvalue;
        else if (node->exprtype == Type::OPERATOR)
        {
            if (node->root->op == '+')
                return Eval(node->left) + Eval(node->right);
            else if (node->root->op == '-')
                return Eval(node->left) - Eval(node->right);
            else if (node->root->op == '*')
                return Eval(node->left) * Eval(node->right);
            else if (node->root->op == '/')
                return Eval(node->left) / Eval(node->right);
            else if (node->root->op == '%')
                return Eval(node->left) % Eval(node->right);
        }
        else if (node->exprtype == Type::OTHER)
            return 0;
    }
    stack<ASTnode*> stiva_noduri;
    void delete_ast(ASTnode *root)
    {
        if (root != NULL)
        {
            if (root->root->other != NULL)
            {
                free(root->root->other);
            } // exprptr nu este dealocat, e pointer la variabila din tabelul de simboluri
            free(root->root);
            delete_ast(root->left);
            delete_ast(root->right);
            delete root;
        }
    }
    void delete_stack()
    {
        while(!stiva_noduri.empty())
        {
            delete_ast(stiva_noduri.top());
            stiva_noduri.pop();
        }
    }
    void build_ast_stack(char oper)
    {
        struct root_data* data=(struct root_data*)calloc(1,sizeof(struct root_data));
        data->op=oper;

        if(stiva_noduri.size()>=2)
        {
            ASTnode* right=stiva_noduri.top();
            stiva_noduri.pop();

            ASTnode* left=stiva_noduri.top();
            stiva_noduri.pop();
            //construieste un nod dou folosind cele doua noduri extrase si operatorul
            ASTnode* root=BuildAST(data,left,right,Type::OPERATOR);
            stiva_noduri.push(root);
        }
        else {
            cout<<"Eror, not enough nodes on the stack for operator "<<oper<<endl;
        }
    }
};*/

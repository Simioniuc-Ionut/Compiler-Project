#include "SymbolTable.h"
using namespace std;

bool SymbolTable::existsVar(const char *name, const char *scope)
{

    for (const VarInfo &var : vars)
    {
        if (var.name == name && var.className == scope)
        {
            return true;
        }
    }
    return false;
}
void SymbolTable::addVar(const char *type, const char *name, const char *scope){
    VarInfo var;
    var.type = string(type);
    var.name = string(name);
    var.className = scope;
    var.isConstant = false;
    vars.push_back(var);
}
void SymbolTable::addVar(const char *type, const char *name, const char *value, const char *scope){
    VarInfo var;
    var.type = string(type);
    var.name = string(name);
    var.value = string(value);
    var.className = scope;
    var.isConstant = false;
    vars.push_back(var);
}
void SymbolTable::addVar(bool isConstant, const char *type, const char *name, const char *value, const char *scope){
    VarInfo var;
    var.type = string(type);
    var.name = string(name);
    var.value = string(value);
    var.className = scope;
    var.isConstant = true;
    vars.push_back(var);
}
void SymbolTable::addArray(const char *type, const char *name, int capacity1, const char *scope)
{
    VarInfo var;
    var.type = string(type);
    var.name = string(name);
    var.dimensions[0] = capacity1;
    var.className = scope;
    var.isConstant = false;
    vars.push_back(var);
}
void SymbolTable::addArray(const char *type, const char *name, int capacity1, int capacity2, const char *scope)
{
    VarInfo var;
    var.type = string(type);
    var.name = string(name);
    var.dimensions[0] = capacity1;
    var.dimensions[1] = capacity2;
    var.className = scope;
    var.isConstant = false;
    vars.push_back(var);
}
void SymbolTable::initArray(const vector<int> values, const char *type, const char *name, int capacity1, const char *className)
{
    VarInfo var;
    var.type = string(type);
    var.name = string(name);
    var.dimensions[0] = capacity1;
    var.className = className;
    var.isConstant = false;
    var.value_from_array.insert(var.value_from_array.end(), values.begin(), values.end());
    vars.push_back(var);
}
void SymbolTable::addValue(const char*type,const char* name,const char* value){
    for (VarInfo &var : vars)
    {
        if (var.name == name && var.type == type)
        {
           var.value=value;
            break;
        }
    }
}
const char *SymbolTable::getTypeOfVariable(const char *varName , const char* scope)
{
    for (const VarInfo &var : vars)
    {
        if (strcmp(var.name.c_str(), varName) == 0 && strcmp(var.className.c_str(),scope) == 0)
        {
            return var.type.c_str();
        }
    }
    return nullptr; // Returnează nullptr dacă variabila nu este găsită
};
string SymbolTable::getValueOfVariable(const char* type,const char* varName,const char* scope){
     for (const VarInfo &var : vars)
    {
        if (strcmp(var.type.c_str(), type) == 0 && strcmp(var.name.c_str(), varName) == 0 && strcmp(var.className.c_str(),scope) == 0)
        {
            return var.value;
        }
    }
    return "0";
}
    
// func
bool SymbolTable::existsFunc(const char *returnType, const char *name, const vector<const char *> &paramTypes, const char *className)
{
    for (const FuncInfo &func : funcs)
    {
        if (strcmp(func.name.c_str(), name) == 0 && strcmp(func.className.c_str(), className) == 0)
        {
            if (func.paramTypes.size() == paramTypes.size())
            {
                bool sameParams = true;
                for (size_t i = 0; i < paramTypes.size(); ++i)
                {
                    if (strcmp(func.paramTypes[i], paramTypes[i]) != 0)
                    {
                        sameParams = false;
                        break;
                    }
                }
                if (sameParams)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
bool SymbolTable::existsClass(const char *className)
{

    for (const ClassId &clas : Clas)
    {
        if (strcmp(clas.className.c_str(), className) == 0)
        {
            return true;
        }
    }
    return false;
}
void SymbolTable::addFunc(const char *returnType, const char *name, const vector<const char *> &paramTypes, const char *className)
{
    FuncInfo fun;
    fun.name = string(name);
    fun.paramTypes = paramTypes;
    fun.returnType = string(returnType);
    fun.className = className;
    funcs.push_back(fun);
}
// class
void SymbolTable::addClass(const char *className)
{
    ClassId clas;
    clas.className = className;
    Clas.push_back(clas);
}
bool SymbolTable::addObjInClass(const char *className, const char *objectName)
{
    for (auto &classId : Clas)
    {
        if (strcmp(classId.className.c_str(), className) == 0)
        {
            for (const auto &objectid : classId.objects)
            { // Parcurge fiecare obiect în acea clasă
                if (strcmp(objectid, objectName) == 0)
                {
                    return false; // Obiectul există deja în clasă
                }
            }
            // Dacă obiectul nu există, adăugați-l
            classId.objects.push_back(objectName);
            return true; // Obiectul a fost adăugat cu succes
        }
    }
    return false; // Clasa nu a fost găsită
};
string SymbolTable::gettypeObj(const char *numeObiect)
{
    for (const ClassId &clasid : Clas)
    {
        for (const auto &objectid : clasid.objects)
        { // Parcurge fiecare obiect în acea clasă
            if (strcmp(objectid, numeObiect) == 0)
            {
                string className = clasid.className;
                return className;
            }
        }
    }
    return "";
};
string SymbolTable::getTypeFunc(const char *returnType, const char *name, const vector<const char *> &paramTypes, const char *className)
{
    for (const FuncInfo &func : funcs)
    {
        if (strcmp(func.name.c_str(), name) == 0 && strcmp(func.className.c_str(), className) == 0)
        {
            if (func.paramTypes.size() == paramTypes.size())
            {
                bool sameParams = true;
                for (size_t i = 0; i < paramTypes.size(); ++i)
                {
                    if (strcmp(func.paramTypes[i], paramTypes[i]) != 0)
                    {
                        sameParams = false;
                        break;
                    }
                }
                if (sameParams)
                {
                    return func.returnType;
                }
            }
            else
            {
                cout << "RETURN2" << endl;
                return "";
            }
        }
    }
    return "";
};

void SymbolTable::printSymbolTable(const string &filename)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error at opening file for writing" << endl;
        return;
    }
    for (const VarInfo &v : vars)
    {
        if (v.className != "")
        { // data member
            if (v.dimensions[0] != 0 && v.dimensions[1] == 0)
            { // avem un array
                file << "Is defined in : " << v.className << " Type: " << v.type << " name: " << v.name << "[" << v.dimensions[0] << "] :=";
                for (auto &ind : v.value_from_array)
                {
                    file << ind << " ";
                    cout << ind << " ";
                }
                file << endl;
            }
            else if (v.dimensions[0] != 0 && v.dimensions[1] != 0)
            { // matrice
                file << "Is defined in : " << v.className << " Type: " << v.type << " name: " << v.name << "[" << v.dimensions[0] << "]"
                     << "[" << v.dimensions[1] << "]"
                     << " value:" << v.value << endl;
            }
            else if (v.isConstant == true)
            {
                // constante
                file << "Is defined in : " << v.className << " Type: CONST " << v.type << " name:" << v.name << " value:" << v.value << endl;
            }
            else
            { // variabile
                file << "Is defined in : " << v.className << " Type: " << v.type << " name: " << v.name << " value:" << v.value << endl;
            }
        }
        else
            { // global
                if (v.dimensions[0] != 0 && v.dimensions[1] == 0)
                { // avem un array
                    file << "In Global Type: " << v.type << " name: " << v.name << "[" << v.dimensions[0] << "] :=";
                    for (auto &ind : v.value_from_array)
                    {
                        file << ind << " ";
                        cout << ind << " ";
                    }
                    file << endl;
                }
                else if (v.dimensions[0] != 0 && v.dimensions[1] != 0)
                { // matrice
                    file << "In Global Type: " << v.type << " name: " << v.name << "[" << v.dimensions[0] << "]"
                         << "[" << v.dimensions[1] << "]"
                         << " value:" << v.value << endl;
                }
                else if (v.isConstant == true)
                {
                    // constante
                    file << "In Global Type: CONST " << v.type << " name: " << v.name << " value: " << v.value << endl;
                }
                else
                { // variabile
                    file << "In Global Type: " << v.type << " name: " << v.name << " value: " << v.value << endl;
                }
            }
        
    }

    for (const FuncInfo &f : funcs)
    {
        if (f.className != "")
        { // funtii membru
            file << "Type Member Function: " << f.className << "  ReturnType: " << f.returnType << " Fun_name:" << f.name << endl;
            file << "Parameter Types: ";
            for (auto &index : f.paramTypes)
                file << index << " ";
        }
        else
        {
            file << endl
                 << " ReturnType: " << f.returnType << " Fun_name:" << f.name << endl;
            file << "Parameter Types: ";
            for (auto &index : f.paramTypes)
                file << index << " ";
        }
    }
    for (const ClassId &clas : Clas)
    {
        file << endl
             << "Type class: " << clas.className << endl;
        for (const auto &objectid : clas.objects)
        {
            file << " Obj decl: " << objectid;
        }
        file << endl;
    }
}

SymbolTable::~SymbolTable()
{
    vars.clear();
}

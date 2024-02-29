#!/bin/bash

echo "compiling $1"
rm -f lex.yy.c
rm -f $1.tab.c
rm -f $1
bison -d -o parser.c $1.y
lex $1.l
g++ SymbolTable.cpp lex.yy.c  parser.c -std=c++17 -o $1 -g

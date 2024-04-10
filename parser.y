%{
#include "node.h"
extern int yylex();
void yyerror(const char *s) {}
%}
%union {
    Node *node;
    Block *block;
    Expression *expr;
    Statement *stmt;
    Identifier *ident;
    VariableDeclaration *var_decl;
    std::vector<VariableDeclaration*> *varvec;
    std::vector<Expression*> *exprvec;
    std::string *string;
    int token;
}
%token IDENTIFIER NUMBER LETTER DIGIT
%token PLUS MINUS MULTIPLY DIVIDE
%token GREATER LESSER GREATER_EQUAL LESSER_EQUAL EQUAL NOT_EQUAL ASSIGN
%token CHAVECLOSE CHAVEOPEN PARENTESESCLOSE PARENTESESOPEN PONTOVIRGULA
%token IF IFNOT WHILE PRINT

%left PLUS MINUS
%left MULTIPLY DIVIDE

%%

program: BLOCK '\n'
       | /* empty */
       ;

BLOCK: CHAVEOPEN statement_list CHAVECLOSE ;

statement_list: statement
              | statement_list statement
              ;

statement: PONTOVIRGULA
         | assignment
         | print_statement
         | while_loop
         | if_statement
         | if_not_statement
         ;

assignment: IDENTIFIER ASSIGN expression PONTOVIRGULA ;

print_statement: PRINT PARENTESESOPEN expression PARENTESESCLOSE PONTOVIRGULA ;

while_loop: WHILE PARENTESESOPEN expression PARENTESESCLOSE BLOCK ;

if_statement: IF PARENTESESOPEN expression PARENTESESCLOSE BLOCK ;

if_not_statement: IF PARENTESESOPEN expression PARENTESESCLOSE BLOCK IFNOT BLOCK ;

condition: expression GREATER expression
          | expression LESSER expression
          | expression GREATER_EQUAL expression
          | expression LESSER_EQUAL expression
          | expression EQUAL expression
          | expression NOT_EQUAL expression
          ;

expression: term
          | expression PLUS term
          | expression MINUS term
          ;

term: factor
    | term MULTIPLY factor
    | term DIVIDE factor
    ;

factor: PLUS factor
      | MINUS factor
      | NUMBER
      | PARENTESESOPEN expression PARENTESESCLOSE
      | IDENTIFIER
      ;

%%

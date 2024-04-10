%{
#include <string>
#include "node.h"
#include "parser.hpp"
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
%}

%%

[ \t]+          ; // Ignore whitespace

"print"         { return PRINT; }
"while"         { return WHILE; }
"ifnot"         { return IFNOT; }
"if"            { return IF; }
"{"             { return CHAVEOPEN; }
"}"             { return CHAVECLOSE; }
";"             { return PONTOVIRGULA; }
"("             { return PARENTESESOPEN; }
")"             { return PARENTESESCLOSE; }
"="             { return ASSIGN; }
">"             { return GREATER; }
"<"             { return LESSER; }
">="            { return GREATER_EQUAL; }
"<="            { return LESSER_EQUAL; }
"=="            { return EQUAL; }
"!="            { return NOT_EQUAL; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MULTIPLY; }
"/"             { return DIVIDE; }
.                       printf("Unknown token!n"); yyterminate();
[a-zA-Z_][a-zA-Z0-9_]*  SAVE_TOKEN; return IDENTIFIER;
[0-9]+                  SAVE_TOKEN; return NUMBER;
%%

int yywrap(void) {
    return 1;
}
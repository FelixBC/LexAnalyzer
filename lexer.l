%{
#include <stdio.h>

void printToken(const char* type);
%}

%option noyywrap

%%

if          { printToken("Palabra clave"); }    // Keywords
[a-zA-Z_][a-zA-Z0-9_]*  { printToken("Identificador"); }  // Identifiers
[=]         { printToken("Operador"); }    // Operators
[0-9]+      { printToken("Número"); }      // Numbers
[ \t\n]+    ;   // Ignore spaces and newlines
.           { printToken("Caracter no reconocido"); }  // Any other character

%%

void printToken(const char* type) {
    printf("%s: %s\n", type, yytext);
}

int main() {
    printf("Introduce código fuente:\n");
    yylex();
    return 0;
}

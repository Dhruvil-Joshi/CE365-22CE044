%{
#include <stdio.h>
%}

DIGIT      [0-9]
LETTER     [a-zA-Z]
ID         {LETTER}({LETTER}|{DIGIT})*
NUMBER     {DIGIT}+
WHITESPACE [ \t\n]+
SCOMMENT    "//".*
MCOMMET    "/*"[^*]*"*/"

%%

{SCOMMENT} {printf("single line comment: %s\n", yytext);  }

{MCOMMET}  {printf("multiple line comment: %s\n", yytext);  }

{WHITESPACE} { /* Ignore whitespace */ }

"int"|"float"|"char"|"double"|"return"|"if"|"else"|"while"|"for"|"do"|"switch"|"case"|"break"|"continue"|"void" {
    printf("Keyword: %s\n", yytext);
}

{ID} {printf("Identifier: %s\n", yytext);}
[0-9]+(\.[0-9]+) {printf("Real Number: %s\n", yytext);}

{NUMBER} {printf("Integer: %s\n", yytext);}

\"(\\.|[^"\\])*\"   {printf("String literal: %s\n", yytext);}

'([^'\\]|\\.)'      {printf("character literal: %s\n", yytext);}

"=="|"!="|"<="|">="|"++"|"&&"|"||"|"<"|">"|"="|"+"|"-"|"*"|"%" {printf("Operator: %s\n", yytext); }

"("|")"|"{"|"}"|"["|"]"|";"|"," { printf("Special Symbol: %s\n", yytext);}


. ;

%%

int main() {
    yyin = fopen("input.c", "r");  // Read from input C file
    if (!yyin) {
        printf("Error opening file\n");
        return 1;
    }
    yylex();
    fclose(yyin);
    return 0;
}

int yywrap() {
    return 1;
}

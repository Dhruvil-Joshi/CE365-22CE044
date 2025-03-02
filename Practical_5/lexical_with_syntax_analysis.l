%option noyywrap
%{
  #include <stdio.h>
%}

%%
"/*"[^*]*"*/" ;

"//".* ;

[ \t\n]+ ;

\".*\" { printf("String: %s\n", yytext); }

'[a-zA-Z0-9\_]' { printf("Character Constant: %s\n", yytext); }

auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while { printf("Keyword: %s\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]* { printf("Identifier: %s\n", yytext); }


\+\+|\+|--|-|\*|\/|=|!|<|>|\&|\||\^|% { printf("Operator: %s\n", yytext); }

[,;(){}[\]:] { printf("Punctuation: %s\n", yytext); }

[0-9]+"."[0-9]+ {printf("Real Constant: %s\n", yytext);}

[0-9]+"."[^0-9 ;\t\n]+ {printf("Unkown Token: %s\n", yytext);}

[0-9]* {printf("Integer Constant: %s\n", yytext);}

[0-9\-\-\+\+\=\=\!\@\#\$\%\&\*(),;\\]*[a-zA-Z0-9\_]* {printf("Unkown Token: %s\n", yytext);}

. ;

%%
int main() {
    yyin=fopen("demo.c","r");
    yylex();
    return 0;
}

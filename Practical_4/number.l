%option noyywrap
%{
  #include <stdio.h>
  int ch=0,w=0,l=0;
%}

%%
[0-9]+ {printf("%s\n", yytext);}
. ;
%%
int main()
{
printf("Enter your string to be checked: ");
yylex();
return 0;
}


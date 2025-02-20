%option noyywrap
%{
  #include <stdio.h>
  int ch=0,w=0,l=0;
%}

%%
charusat {printf("university");}
. {printf("%s",yytext);}
%%
int main()
{
printf("Enter your string to be checked: ");
yylex();
return 0;
}


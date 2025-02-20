%option noyywrap
%{
  #include <stdio.h>
  int ch=0,w=0,l=0;
%}

%%
[\n] {l++;}
[ \t] {ch+=yyleng;}
[^\t\n ]+ {w++;ch+=yyleng;};
%%
int main()
{
printf("Enter The sentences to be checked: \n");
yylex();
printf("\nNo of characters %d",ch);
printf("\nNo of words %d",w);
printf("\nNo of lines %d",l);
return 0;
}


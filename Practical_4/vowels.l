%option noyywrap
%{
  #include <stdio.h>
  int v=0,c=0;
%}

%%
[aeiouAEIOU] {v++;}
[a-z A-Z] {c++;}
[_\t\n] ;
. ;
%%
int main()
{
printf("Enter string: ");
yylex();
printf("\nNo of vowels %d",v);
printf("\nNo of consonants %d",c);
return 0;
}


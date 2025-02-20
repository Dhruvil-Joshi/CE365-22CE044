%option noyywrap
%{
  #include <stdio.h>
  int lc=0,uc=0,ec=0,ss=0,d=0,l=0;
%}

%%
[0-9] {d++;l++;}
[a-z] {lc++;l++;}
[A-Z] {uc++;l++;}
[* ; # $ @] {ss++;l++;}
[\n] {if(ec==0 && d>0 && lc>0 && uc>0 && ss>0 && l>=9 && l<=15)
{
    printf("Valid password\n");
    return 0;
}
else
{
    printf("Invalid password\n");
    return 0;
}
}
. {ec++;printf("Invalid password\n");return 0;}
%%
int main()
{
printf("Enter the passsword: ");
yylex();
return 0;
}


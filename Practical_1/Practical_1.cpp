#include <stdio.h>
#include <conio.h>
#include <string.h>
int main()
{
   int test=0;
   printf("\nEnter number of testcases: ");
   scanf("%d",&test);

   while (getchar() != '\n'); // Clear input buffer

   int k =0;
   for(k = 0;k<test;k++)
   {
        char str[20];
        printf("\nEnter string: ");
        gets(str);
        int verify=0;
        int i;
        for(i = 0;i<strlen(str);i++)
        {
        if(str[i] == 'a')
        {
                verify = 1;
                continue;
        }
        else
        {
                break;
        }
        }
        int noofb = 0;
        for(;i<strlen(str);i++){
        if(str[i] == 'b'){
                noofb++;
                verify = 1;
        }else{
                verify = 0;
                break;
        }
        }
        if(noofb == 2 && verify==1){
        verify = 1;
        }else{
        verify = 0;
        }

        if(verify == 0){
        printf("Invalid string\n");
        }else{
        printf("Valid string\n");}
   }
   return 0;
}
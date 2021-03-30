%{ 
#include<stdio.h> 
int flp = 0; int i = 0; /*Global variables*/
%} 
  
/*Rule Section*/
%% 
[0-9]+[ \n\t]+ i++;
[0-9]*\.[0-9]+[ \n\t]+ flp++;
[ \n\t]* ;
%% 
  
int main() 
{ 
    // The function that starts the analysis 
    yylex(); 
      
    printf("\nNo. of floating point =%d", flp);   
    printf("\nNo. of integers=%d", i); 
      
} 

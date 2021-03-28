%{ 
#include<stdio.h> 
    int w = 0;
%} 
  
/*Rule Section*/
%% 
[aeiouAEIOU]+[a-zA-Z]* w++;
[a-zA-Z0-9]* ;
[ \n\t]* ;
%% 
  
int main() 
{ 
    // The function that starts the analysis 
    yylex(); 
      
    printf("\nNo. of words =%d", w);   
      
} 

%{ 
#include<stdio.h> 
int lc=0, sc=0, tc=0, ch=0, w=0; /*Global variables*/
%} 
  
/*Rule Section*/
%% 
\n {lc++; ch++;} //line counter 
[a-zA-Z]+  {w++; ch += yyleng;}//word counter
. ch++;//all characters including white space
%% 
  
int main() 
{ 
    // The function that starts the analysis 
    yylex(); 
      
    printf("\nNo. of lines=%d", lc);   
    printf("\nNo. of words=%d", w); 
    printf("\nNo. of  characters=%d", ch); 
      
} 

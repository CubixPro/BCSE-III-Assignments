%{
#include <stdio.h>
int c=0;
%}

%%
[aeiouAEIOU][a-zA-Z0-9]*	c++;	
[a-zA-Z0-9]*			;
. 				;
%%

int yywrap(void){}

int main()
{
	yylex();
	
	printf("Number of words starting with vowels: %d\n", c);
	
	return 0;
}

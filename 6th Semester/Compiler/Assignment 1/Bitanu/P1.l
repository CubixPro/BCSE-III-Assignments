%{
#include <stdio.h>
int l=0, w=0, c=0;
%}

%%
\n		{l++;}
[^ \t\n]+	{w++; c+=yyleng;}
.		{c++;}
%%

int yywrap(void){}

int main()
{
	yylex();
	
	printf("Number of lines: %d\n", l);
	printf("Number of words: %d\n", w);
	printf("Number of characters are: %d\n", c);
	
	return 0;
}

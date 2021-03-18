%{
#include <stdio.h>
int i=0, f=0;
%}

%%
[0-9]+\.[0-9]+[ \t\n]+		f++;
\.[^ \t\n]*			;
[^ \t\n]*\.			;
[0-9]+[ \t\n]+			i++;
.				;
%%

int yywrap(void){}

int main()
{
	yylex();
	
	printf("Number of integers: %d\n", i);
	printf("Number of floats: %d\n", f);
	
	return 0;
}

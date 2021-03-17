%{
int num_dec=0, num_float=0;
%}

%%
\n 	;
[0-9]+\.[0-9]+ {printf("Floating point : %s\n", yytext); num_float++; }
[0-9]+ {printf("Decimal : %s\n", yytext); num_dec++;}
. 	;



%%

int yywrap(void)  
{
 return 1;
}

int main(){
	yylex();
	printf("Number of decimal numbers: %d\n", num_dec);
	printf("Number of floating numbers : %d\n", num_float);
}

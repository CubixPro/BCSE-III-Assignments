%{
int num_words=0;
%}

%%
\n 	;
[aeiouAEIOU][a-zA-Z0-9.]*     {num_words++; printf("%s\n", yytext);}
[a-zA-Z0-9(^aeiouAEIOU)][a-zA-Z0-9]*	;
.	;



%%

int yywrap(void)  
{
 return 1;
}

int main(){
	yylex();
	printf("Number of words that start with a vowel: %d\n", num_words);
}

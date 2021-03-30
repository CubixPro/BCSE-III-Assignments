%{
int num_lines=0, num_chars =0, num_words=0;
%}
%%

\n      num_lines++;num_chars++;
([a-zA-Z0-9])+ 	{num_words++; num_chars += strlen(yytext);}
.       num_chars++;

%%

int yywrap(void)  
{
 return 1;
}

int main(){
	yylex();
	printf("Number of lines : %d\n", num_lines);
	printf("Number of characters : %d\n", num_chars);
	printf("Number of words : %d\n", num_words);
}

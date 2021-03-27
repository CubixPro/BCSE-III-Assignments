%{
    #include<stdio.h>
    int total_lines = 0, total_words = 0, total_chars = 0;
%}

%%
\n          {total_lines++;}
[^ \t\n]+   {total_words++; total_chars += yyleng;}
.           {total_chars++;}

%%



int yywrap(void){}

int main()
{
    yylex();

    printf("\n******************************************\n");
    printf("Number of lines: %d\n", total_lines);
    printf("Number of words: %d\n", total_words);
    printf("Number of characters: %d\n", total_chars);
    printf("******************************************\n");

    return 0;

}
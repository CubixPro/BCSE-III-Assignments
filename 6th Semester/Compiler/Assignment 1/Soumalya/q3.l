%{
    #include<stdio.h>
    int total_words = 0;
%}

%%
[aeiouAEIOU][a-zA-z0-9]*        {total_words++;}
[a-zA-Z0-9]*                    ;
.                               ;
%%

int yywrap(void){}

int main()
{
    yylex();

    printf("\n******************************************\n");
    printf("Number of words starts with a vowel: %d\n", total_words);
    return 0;
}

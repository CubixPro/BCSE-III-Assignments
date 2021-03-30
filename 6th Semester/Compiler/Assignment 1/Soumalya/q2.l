%{
    #include<stdio.h>
    int total_numbers = 0, total_decimals = 0;
%}


%%
[0-9]+\.[0-9]+[ \t\n]       {total_numbers++;}
[0-9]+[ \t\n]+              {total_decimals++;}
.                           ;
%%


int yywrap(void){}

int main()
{
    yylex();

    printf("\n******************************************\n");
    printf("Number of Integers: %d\n", total_numbers);
    printf("Number of decimals: %d\n", total_decimals);
    printf("******************************************\n");

    return 0;

}
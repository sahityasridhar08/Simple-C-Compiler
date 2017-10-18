%{
#include<stdio.h>
#include<math.h>
#include "y.tab.h"

%}
%%
[ \t]+ ;
[0-9]+ {yylval = atoi(yytext); return INTEGER;}
"T" { yylval = 1; return BOOLEXP; }
"F" { yylval = 0; return BOOLEXP; }
"!F" { yylval = 1; return BOOLEXP; }
"!T" { yylval = 0; return BOOLEXP; }
[-+/*] {return *yytext;}
"#" {return *yytext;}
"(" {return *yytext;}
")" {return *yytext;}
\n {return *yytext;}
%%
void yyerror(char *str)
{
 printf("\n Invalid Character...");
}
int main()
{
 printf("Enter Expression => ");
 yyparse();
 return(0);
}



%{
#include <stdlib.h>
#include <stdio.h>
#include<math.h>
int yylex(void);
#include "y.tab.h"
%}

%token INTEGER
%token BOOLEXP

%%
program:
 line program
 | line

line:
 expr '\n' { printf("Answer is : %d\n",$1); }
 | '\n'
| boolexpr '\n'
{
if($1>0)
printf("\nTRUE\n");
else
printf("\nFALSE\n");
}

expr:
 expr '+' mulex { $$ = $1 + $3; }
 | expr '#' mulex {$$ = pow($1,$3); }
 | expr '-' mulex { $$ = $1 - $3; }
 | mulex { $$ = $1; }

mulex:
 mulex '*' term { $$ = $1 * $3; }
 | mulex '/' term { $$ = $1 / $3; }
 | term { $$ = $1; }

term:
 '(' expr ')' { $$ = $2; }
 | INTEGER { $$ = $1; }

boolexpr:
    BOOLEXP { $$ = $1; }
  | boolexpr '*' boolexpr { $$ = $1 * $3; }
  | boolexpr '+' boolexpr { $$ = $1 + $3; }
  | '(' boolexpr ')' { $$ = $2; }
  
%%

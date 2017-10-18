%{
#include <stdlib.h>
#include <stdio.h>
#include<math.h>
int yylex(void);
#include "y.tab.h"
%}


%token FLOAT INTEGER DOUBLE RELOP BOOL

%%
program:
 line program
 | line

line: expr '\n' 
{
	if($1==0)
		printf("\nRESULTANT TYPE IS INTEGER\n");
	else if($1==1)
		printf("\nRESULTANT TYPE IS FLOAT\n");
	else if($1==2)
		printf("\nRESULTANT TYPE IS DOUBLE\n");
	else if($1==-1)
		printf("\nRESULTANT TYPE IS BOOLEAN!\n");
} /*if construct*/
 | '\n'

expr: expr '+' mulex
{
  $$= $1>$3?$1:$3;	

}
 | expr '^' mulex 
{
  $$= $1>$3?$1:$3;	

}
 | expr '-' mulex
{
  $$= $1>$3?$1:$3;	

}
 | expr RELOP mulex
{
  $$= $1>$3?$1:$3;	

}
 | mulex { $$ = $1; }

mulex: mulex '*' term 
{
  $$= $1>$3?$1:$3;	

}
 | mulex '/' term 
{
  $$= $1>$3?$1:$3;	

}
 | mulex RELOP term 
{
  $$= $1>$3?$1:$3;	

}
 | term { $$ = $1; }

term:
 '(' expr ')' { $$ = $2; }
|INTEGER { $$ = $1; }
|FLOAT { $$ = $1; }
|DOUBLE { $$ = $1; }
|BOOL {$$=$1;}
%%



%{
#include<stdio.h>
#include<math.h>
#include "y.tab.h"

%}
digit [0-9]
%%
[ \t]+ ;
[0-9]+ {yylval= 0; return INTEGER;}
{digit}+\.{digit}({digit})? {yylval= 1; return FLOAT;}
{digit}+\.{digit}{digit}{digit}({digit})? {yylval= 2; return DOUBLE;}
"true"|"false" {yylval=-1; return BOOL;}
"==" {return RELOP;}
[-+/*] {return *yytext;}
"^" {return *yytext;}
"(" {return *yytext;}
")" {return *yytext;}
\n {return *yytext;}
%%
void yyerror(char *str)
{
 printf("\n You have entered a character out of syntax!\n\n --------END OF PROGRAM---------");
}
int main()
{
 printf("Enter Expression => ");
 yyparse();
 return(0);
}

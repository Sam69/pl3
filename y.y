%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#define YYSTYPE int
int nothreads,noexp;
char file[20];

%}

%token NUMBER
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

%pure-parser
%lex-param	{void *scanner}
%parse-param	{void *scanner}

%%

ArithmeticExpression:E	{return $$;}

E:E'+'E		{$$=$1+$3;}
 |E'-'E		{$$=$1-$3;}
 |E'*'E		{$$=$1*$3;}
 |E'/'E		{$$=$1/$3;}
 |E'%'E		{$$=$1%$3;}
 |'('E')'	{$$=$2;}
 |NUMBER	{$$=$1;}
;
%%


void calc()
{
	void *scanner;
	yylex_init(&scanner);
	FILE *fp;

	fp=fopen(file,"r");

	int i,res;
	char *s=(char *)malloc(100);
	size_t n=100;
	int tid;
	tid=omp_get_thread_num();

	for(i=0;i<(noexp*tid);i++)
		getline(&s,&n,fp);

	yyset_in(fp,scanner);

	for(i=0;i<(noexp);i++)
	{
		res=yyparse(scanner);
		printf("%d Expression =%d is evaluated by Thread with ID %d\n",noexp*tid+i+1,res,tid);
	}
	yylex_destroy(scanner);
	fclose(fp);
}


void main()
{
	printf("Enter the Input file name:\t");
	scanf("%s",file);
	
	printf("Enter the Number of threads to be created:\t");
	scanf("%d",&nothreads);
	
	printf("Enter the Number of Expressions to be evaluated per thread:\t");
	scanf("%d",&noexp);

	#pragma omp parallel num_threads(nothreads)
	{	calc();		}

}

int yyerror()
{
	printf("Arithmetic Expression is Invalid\n");
}
	

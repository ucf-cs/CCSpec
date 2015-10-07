%{
#include <stdlib.h>
#include <string.h>
#include "seqhistory.h"
#include "seqhistory.tab.h"
void yyerror(char *);
%}

%%

"enqueue"           return ENQUEUE;

"dequeue"           return DEQUEUE;

"push"              return PUSH;

"pop"               return POP;

"put"				return PUT;

"get"				return GET;

"remove"			return REMOVE;

"push_back"			return PUSHBACK;

"pop_back"			return POPBACK;

"pop_front"			return POPFRONT;

"push_front"		return PUSHFRONT;

"insert"            return INSERT;

"deletemin"         return DELETEMIN;

[0][x][a-f0-9]+ 	return HEX;

[a-z]       { 
                yylval.sIndex = *yytext - 'a';
                return VARIABLE;
            }      

0           {
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }

[1-9][0-9]?[0-9]?[0-9]?[0-9]?[0-9]?[0-9]?[0-9]?[0-9]? 	{
															yylval.iValue = atoi(yytext);
															return INTEGER;
														}
			

[1-9][0-9]* {
                yylval.iValue64 = strtoul(yytext, NULL, 10);
                return INTEGER64;
            }

[-()<>=+*/;{}.:,] {
                return *yytext;
             }
"["             return *yytext;
"]"             return *yytext;
">="            return GE;
"<="            return LE;
"=="            return EQ;
"!="            return NE;
"&&"            return AND;
"||"            return OR;
"while"         return WHILE;
"if"            return IF;
"else"          return ELSE;
"for"           return FOR;
"forall"        return FORALL;
"exists"        return EXISTS;
"print"         return PRINT;
".."            return RANGE;
"fprintf"       return FPRINTF;

[a-zA-Z][a-zA-Z0-9_]+	yylval.charArray=strdup(yytext); return ALPHANUM;

[ \t\n]+        ;       /* ignore whitespace */

%%

int yywrap(void) {
    return 1;
}


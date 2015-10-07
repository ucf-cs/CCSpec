%{
#include <stdlib.h>
#include <string.h>
#include "lcdc.h"
#include "lcdc.tab.h"
void yyerror(char *);
%}

%%

"h"                 return HISTORYOBJECT;
"p"                 return NUMTHREADS;
"length"            return STACKLENGTH;
"s"                 return HISTORYSTACK;
"get_type()"        return ACTGETTYPE;
"get_mo()"          return ACTGETORDER; 
"get_tid()"         return ACTGETTID; 
"get_seq_number()"  return ACTGETSEQNUM;  
"method_id"			return METHODID; 
"is_active" 		return ISACTIVE;
"method_name"		return METHODNAME; 
"happens_before"	return HAPPENSBEFORE; 
"INVOCATION"		return ACTTYPE_INVOCATION;
"RESPONSE" 			return ACTTYPE_RESPONSE;

[a-z]       { 
                yylval.sIndex = *yytext - 'a';
                return VARIABLE;
            }      

0           {
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }

[1-9][0-9]* {
                yylval.iValue = atoi(yytext);
                return INTEGER;
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
"++"			return INC;
"--"     		return DEC;

[a-zA-Z][a-zA-Z0-9_]+	yylval.charArray=strdup(yytext); return ALPHANUM;

[ \t\n]+        ;       /* ignore whitespace */

%%

int yywrap(void) {
    return 1;
}


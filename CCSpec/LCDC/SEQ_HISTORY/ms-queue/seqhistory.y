%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <string.h>
#include "seqhistory.h"
#include <queue>

FILE * pFile;

std::queue<int> *q;

/* prototypes */
extern "C"
{
    nodeType *opr(int oper, int nops, ...);
    nodeType *id(int i);
    nodeType *idString(char *i);
    nodeType *con(int value);
    void freeNode(nodeType *p);
    int ex(nodeType *p);
    unsigned long hash(char *str);
    int yylex(void);

    void yyerror(char *s);
}

//int sym[26];                    /* symbol table */

symbolType sym[SIZE];             /* symbol table */

%}

%union {
    int iValue;                 /* integer value */
    char sIndex;                /* symbol table index */
    nodeType *nPtr;             /* node pointer */
    char *charArray;
};

%token <iValue> INTEGER
%token <sIndex> VARIABLE
%token <charArray> ALPHANUM
%token WHILE IF PRINT FOR FORALL EXISTS FPRINTF 
%token ENQUEUE DEQUEUE
%nonassoc IFX
%nonassoc ELSE
%nonassoc RANGE
%nonassoc HEX

%left AND OR
%left GE LE EQ NE '>' '<' 
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%type <nPtr> stmt expr stmt_list stmt_partial 

%%

program:
        function                { /*exit(0);*/ ; }
        ;

function:
          function stmt         { ex($2); freeNode($2); }
        | /* NULL */
        ;

stmt:
          ';'                                               { $$ = opr(';', 2, NULL, NULL); }
        | expr ';'                                          { $$ = $1; }
        | PRINT expr ';'                                    { $$ = opr(PRINT, 1, $2); }
        | FPRINTF expr ';'                                  { $$ = opr(FPRINTF, 1, $2); }
        | VARIABLE '=' expr ';'                             { $$ = opr('=', 2, id($1), $3); }
        | ALPHANUM '=' expr ';'                             { $$ = opr('=', 2, idString($1), $3); }
        | WHILE '(' expr ')' stmt                           { $$ = opr(WHILE, 2, $3, $5); }
        | IF '(' expr ')' stmt %prec IFX                    { $$ = opr(IF, 2, $3, $5); }
        | IF '(' expr ')' stmt ELSE stmt                    { $$ = opr(IF, 3, $3, $5, $7); }
        | FOR '(' stmt expr ';' stmt_partial ')' stmt       { $$ = opr(FOR, 4, $3, $4, $6, $8); }      
        | '{' stmt_list '}'                                 { $$ = $2; }
		| ENQUEUE '(' expr ')' ';'              			{ $$ = opr(ENQUEUE, 1, $3); } 
        | DEQUEUE '(' ')' ';'        						{ $$ = opr(DEQUEUE,0); }  
        ;

stmt_list:
          stmt                  { $$ = $1; }
        | stmt_list stmt        { $$ = opr(';', 2, $1, $2); }
        ;

stmt_partial:
         VARIABLE '=' expr      { $$ = opr('=', 2, id($1), $3); }
        | ALPHANUM '=' expr     { $$ = opr('=', 2, idString($1), $3); }
        ;

expr:
          INTEGER                                                               { $$ = con($1); }
        | VARIABLE                                                              { $$ = id($1); }
        | ALPHANUM                                                              { $$ = idString($1); }
        | '-' expr %prec UMINUS                                                 { $$ = opr(UMINUS, 1, $2); }
        | expr '+' expr                                                         { $$ = opr('+', 2, $1, $3); }
        | expr '-' expr                                                         { $$ = opr('-', 2, $1, $3); }
        | expr '*' expr                                                         { $$ = opr('*', 2, $1, $3); }
        | expr '/' expr                                                         { $$ = opr('/', 2, $1, $3); }
        | expr '<' expr                                                         { $$ = opr('<', 2, $1, $3); }
        | expr '>' expr                                                         { $$ = opr('>', 2, $1, $3); }
        | expr GE expr                                                          { $$ = opr(GE, 2, $1, $3); }
        | expr LE expr                                                          { $$ = opr(LE, 2, $1, $3); }
        | expr NE expr                                                          { $$ = opr(NE, 2, $1, $3); }
        | expr EQ expr                                                          { $$ = opr(EQ, 2, $1, $3); }
        | expr AND expr                                                         { $$ = opr(AND, 2, $1, $3); }
        | expr OR expr                                                          { $$ = opr(OR, 2, $1, $3); }
        | FORALL VARIABLE ':' expr RANGE expr ',' '(' expr ')'                  { $$ = opr(FORALL, 4, id($2), $4, $6, $9); }
        | FORALL ALPHANUM ':' expr RANGE expr ',' '(' expr ')'                  { $$ = opr(FORALL, 4, idString($2), $4, $6, $9); }
        | EXISTS VARIABLE ':' expr RANGE expr ',' '(' expr ')'                  { $$ = opr(EXISTS, 4, id($2), $4, $6, $9); } 
        | EXISTS ALPHANUM ':' expr RANGE expr ',' '(' expr ')'                  { $$ = opr(EXISTS, 4, idString($2), $4, $6, $9); } 
        | '(' expr ')'                                                          { $$ = $2; }
        ;

         
%%

nodeType *con(int value) {
    nodeType *p;

    /* allocate node */
    if ((p = (nodeType*) malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeCon;
    p->con.value = value;

    return p;
}

nodeType *id(int i) {
    nodeType *p;

    /* allocate node */
    if ((p = (nodeType*) malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeId;
    p->id.i = i;
    printf("p->id.i = %d\n", i);

    return p;
}

nodeType *idString(char *i) {
    nodeType *p;
    unsigned long hashId;

    /* allocate node */
    if ((p = (nodeType*) malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeIdString;
    
    hashId = hash(i);
    printf("hashId = %lu\n", hashId);
    if(sym[hashId].key == NULL)
    {
        p->id.i = hashId;
    } else if (strcmp(i, sym[hashId].key) == 0)
    {
        p->id.i = hashId;
    } else 
    {
        int count = 0;
        do{
            hashId = (hashId + 1)%SIZE; //linear probing
            if(hashId < 26)
                hashId = hashId + 26; //first 26 reserved for single letter variables
            if(sym[hashId].key == NULL)
                break;
            if(++count > SIZE)
            {
                printf("Symbol Table is full\n");
                break;          
            }
        } while (strcmp(i, sym[hashId].key) != 0);
        p->id.i = hashId; 
    }

    return p;
}

nodeType *opr(int oper, int nops, ...) {
    va_list ap;
    nodeType *p;
    int i;

    /* allocate node */
    if ((p = (nodeType*) malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");
    if ((p->opr.op = (nodeType**) malloc(nops * sizeof(nodeType *))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
    va_start(ap, nops);
    for (i = 0; i < nops; i++)
        p->opr.op[i] = va_arg(ap, nodeType*);
    va_end(ap);
    return p;
}

void freeNode(nodeType *p) {
    int i;

    if (!p) return;
    if (p->type == typeOpr) {
        for (i = 0; i < p->opr.nops; i++)
            freeNode(p->opr.op[i]);
        free(p->opr.op);
    }
    free (p);
}

void yyerror(char *s) {
    fprintf(stdout, "%s\n", s);
}

int main(int argc, char *argv[]) {
       
    std::queue<int> queue;
    q = &queue;
	pFile = fopen("LCDC/SEQ_HISTORY/output.txt", "a");

	//pFile = fopen("example.txt", "a");     
  
    yyparse();

	fprintf(pFile, "\n");

	fclose(pFile);
	
    return 0;
}

int ex(nodeType *p) {

	int result;
    
    if (!p) return 0;
    switch(p->type) {
    case typeCon:       return p->con.value;
    case typeId:        return sym[p->id.i].value;
    case typeIdString:  return sym[p->id.i].value;
    case typeOpr:
        switch(p->opr.oper) {
        case WHILE:     while(ex(p->opr.op[0])) ex(p->opr.op[1]); return 0;
        case IF:        if (ex(p->opr.op[0]))
                            ex(p->opr.op[1]);
                        else if (p->opr.nops > 2)
                            ex(p->opr.op[2]);
                        return 0;
        case FOR:       for(ex(p->opr.op[0]); ex(p->opr.op[1]); ex(p->opr.op[2])) ex(p->opr.op[3]); return 0;
        case FORALL:    for(sym[p->opr.op[0]->id.i].value = ex(p->opr.op[1]); sym[p->opr.op[0]->id.i].value <= ex(p->opr.op[2]); sym[p->opr.op[0]->id.i].value++)
                        {
                            if(!ex(p->opr.op[3]))
                                return 0; 
                        }             
                        return 1;
        case EXISTS:    for(sym[p->opr.op[0]->id.i].value = ex(p->opr.op[1]); sym[p->opr.op[0]->id.i].value <= ex(p->opr.op[2]); sym[p->opr.op[0]->id.i].value++)
                        {
                            if(ex(p->opr.op[3]))
                                return 1; 
                        }   
                        return 0;                                                        
        case PRINT:     printf("%d\n", ex(p->opr.op[0])); return 0;
        //case FPRINTF:   fprintf(pFile, "%d\n", ex(p->opr.op[0])); return 0;
        case ';':       ex(p->opr.op[0]); return ex(p->opr.op[1]);
        case '=':       return sym[p->opr.op[0]->id.i].value = ex(p->opr.op[1]);
        case UMINUS:    return -ex(p->opr.op[0]);
        case '+':       return ex(p->opr.op[0]) + ex(p->opr.op[1]);
        case '-':       return ex(p->opr.op[0]) - ex(p->opr.op[1]);
        case '*':       return ex(p->opr.op[0]) * ex(p->opr.op[1]);
        case '/':       return ex(p->opr.op[0]) / ex(p->opr.op[1]);
        case '<':       return ex(p->opr.op[0]) < ex(p->opr.op[1]);
        case '>':       return ex(p->opr.op[0]) > ex(p->opr.op[1]);
        case GE:        return ex(p->opr.op[0]) >= ex(p->opr.op[1]);
        case LE:        return ex(p->opr.op[0]) <= ex(p->opr.op[1]);
        case NE:        return ex(p->opr.op[0]) != ex(p->opr.op[1]);
        case EQ:        return ex(p->opr.op[0]) == ex(p->opr.op[1]);
        case AND:       return ex(p->opr.op[0]) && ex(p->opr.op[1]);
        case OR:        return ex(p->opr.op[0]) || ex(p->opr.op[1]);
        case ENQUEUE:   fprintf(pFile, "0 "); q->push(ex(p->opr.op[0])); return 0;
        case DEQUEUE:   result = q->front(); q->pop(); fprintf(pFile, "%lu ", result); return result;
        }
    }
    return 0;
}

unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    hash = hash%SIZE;
    if(hash < 26)
        hash = hash + 26;
    
    return hash;
}



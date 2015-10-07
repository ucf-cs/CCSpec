%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <string.h>
#include "lcdc.h"
#include "HistoryShell.h"

FILE * pFile;

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
HistoryShell *h;

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
%token POSTINC POSTDEC PREINC PREDEC
%token WHILE IF PRINT FOR FORALL EXISTS FPRINTF 
%token HISTORYOBJECT NUMTHREADS STACKLENGTH HISTORYSTACK ACTGETTYPE ACTGETORDER ACTGETTID ACTGETSEQNUM 
%token ACTTYPE_INVOCATION ACTTYPE_RESPONSE
%token METHODID ISACTIVE HAPPENSBEFORE METHODNAME //STRCMP
%nonassoc IFX
%nonassoc ELSE
%nonassoc RANGE

%left AND OR
%left GE LE EQ NE '>' '<' 
%left '+' '-'
%left '*' '/'
%left INC DEC
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
		| expr HAPPENSBEFORE expr ';'						{ $$ = opr(HAPPENSBEFORE, 2, $1, $3); }
        | WHILE '(' expr ')' stmt                           { $$ = opr(WHILE, 2, $3, $5); }
        | IF '(' expr ')' stmt %prec IFX                    { $$ = opr(IF, 2, $3, $5); }
        | IF '(' expr ')' stmt ELSE stmt                    { $$ = opr(IF, 3, $3, $5, $7); }
        | FOR '(' stmt expr ';' stmt_partial ')' stmt       { $$ = opr(FOR, 4, $3, $4, $6, $8); }
        | '{' stmt_list '}'                                 { $$ = $2; }
        ;

stmt_list:
          stmt                  { $$ = $1; }
        | stmt_list stmt        { $$ = opr(';', 2, $1, $2); }
        ;

stmt_partial:
         VARIABLE '=' expr      { $$ = opr('=', 2, id($1), $3); }
        | ALPHANUM '=' expr     { $$ = opr('=', 2, idString($1), $3); }
		| VARIABLE INC			{ $$ = opr(POSTINC, 1, id($1)); }
		| VARIABLE DEC			{ $$ = opr(POSTDEC, 1, id($1)); }
		| INC VARIABLE 			{ $$ = opr(PREINC, 1, id($2)); }
		| DEC VARIABLE			{ $$ = opr(PREDEC, 1, id($2)); }
        ;

expr:
          INTEGER                                                               { $$ = con($1); }
        | VARIABLE                                                              { $$ = id($1); }
        | ALPHANUM                                                              { $$ = idString($1); }
		| ACTTYPE_INVOCATION													{ $$ = opr(ACTTYPE_INVOCATION, 0); }
		| ACTTYPE_RESPONSE														{ $$ = opr(ACTTYPE_RESPONSE, 0); }
        | HISTORYOBJECT '.' NUMTHREADS                                          { $$ = opr(NUMTHREADS, 0); }
        | HISTORYOBJECT '.' STACKLENGTH                                         { $$ = opr(STACKLENGTH, 0); }
        | HISTORYOBJECT '.' HISTORYSTACK '[' expr ']' '.' ACTGETTYPE        	{ $$ = opr(ACTGETTYPE, 1, $5); }
        | HISTORYOBJECT '.' HISTORYSTACK '[' expr ']' '.' ACTGETORDER       	{ $$ = opr(ACTGETORDER, 1, $5); }
        | HISTORYOBJECT '.' HISTORYSTACK '[' expr ']' '.' ACTGETTID         	{ $$ = opr(ACTGETTID, 1, $5); }
        | HISTORYOBJECT '.' HISTORYSTACK '[' expr ']' '.' ACTGETSEQNUM      	{ $$ = opr(ACTGETSEQNUM, 1, $5); }
		| METHODID '(' expr ',' expr ')' 										{ $$ = opr(METHODID, 2, $3, $5); }
		| ISACTIVE '(' expr ',' expr ')' 										{ $$ = opr(ISACTIVE, 2, $3, $5); }
		//| str EQ str															{ $$ = opr(STRCMP, 2, $1, $3); }
		| METHODNAME '(' expr ',' expr ')' EQ METHODNAME '(' expr ',' expr ')'  { $$ = opr(METHODNAME, 4, $3, $5, $10, $12); }
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
		| VARIABLE INC															{ $$ = opr(POSTINC, 1, id($1)); }
		| VARIABLE DEC															{ $$ = opr(POSTDEC, 1, id($1)); }
		| INC VARIABLE 															{ $$ = opr(PREINC, 1, id($2)); }
		| DEC VARIABLE															{ $$ = opr(PREDEC, 1, id($2)); }
        | FORALL VARIABLE ':' expr RANGE expr ',' '(' expr ')'                  { $$ = opr(FORALL, 4, id($2), $4, $6, $9); }
        | FORALL ALPHANUM ':' expr RANGE expr ',' '(' expr ')'                  { $$ = opr(FORALL, 4, idString($2), $4, $6, $9); }
        | EXISTS VARIABLE ':' expr RANGE expr ',' '(' expr ')'                  { $$ = opr(EXISTS, 4, id($2), $4, $6, $9); } 
        | EXISTS ALPHANUM ':' expr RANGE expr ',' '(' expr ')'                  { $$ = opr(EXISTS, 4, idString($2), $4, $6, $9); } 
        | '(' expr ')'                                                          { $$ = $2; }
        ;

//str:
//          METHODNAME '(' expr ',' expr ')'										{ $$ = opr(METHODNAME, 2, $3, $5); }
//		; 
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
    
    HistoryShell obj;
    h = &obj;
    
    pFile = fopen("LCDC/output.txt", "w");
    h->retrieve_history(pFile);
    
	
    yyparse();

	h->topological_sort(pFile);
	h->get_legal_seq_histories(pFile);
	h->map_legal_seq_histories(pFile); 

    fclose(pFile); 
    return 0;
}

int ex(nodeType *p) {
    
    if (!p) return 0;
    switch(p->type) {
    case typeCon:       return p->con.value; //fprintf(pFile, "%d\n", p->con.value); 
    case typeId:        return sym[p->id.i].value; //fprintf(pFile, "sym[%d] = %d\n", p->id.i, sym[p->id.i].value); 
    case typeIdString:  return sym[p->id.i].value; //fprintf(pFile, "sym[%d] = %d\n", p->id.i, sym[p->id.i].value); 
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
        case FPRINTF:   fprintf(pFile, "%d\n", ex(p->opr.op[0])); return 0;
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
		case POSTINC:       return sym[p->opr.op[0]->id.i].value++;
		case POSTDEC:       return sym[p->opr.op[0]->id.i].value--;
		case PREINC:        return ++sym[p->opr.op[0]->id.i].value;
		case PREDEC:        return --sym[p->opr.op[0]->id.i].value;
        case NUMTHREADS:    return h->p;
        case STACKLENGTH:   return h->length;
        case ACTGETTYPE:    return h->s[ex(p->opr.op[0])].type;
        case ACTGETORDER:   return h->s[ex(p->opr.op[0])].order;
        case ACTGETTID:     return h->s[ex(p->opr.op[0])].tid;
        case ACTGETSEQNUM:  return h->s[ex(p->opr.op[0])].seq_num;
		case METHODID:		return h->method_id((unsigned int) ex(p->opr.op[0]), ex(p->opr.op[1]));
		case ISACTIVE:		return h->is_active((unsigned int) ex(p->opr.op[0]), ex(p->opr.op[1]));
		case METHODNAME:	if(strcmp(h->method_name((unsigned int) ex(p->opr.op[0]), ex(p->opr.op[1])), h->method_name((unsigned int) ex(p->opr.op[2]), ex(p->opr.op[3]))) == 0)
								return 1;
							else
								return 0;
		case HAPPENSBEFORE:	fprintf(pFile, "%d happens before", ex(p->opr.op[0])); fprintf(pFile, " %d\n", ex(p->opr.op[1])); 
							h->happens_before(pFile, ex(p->opr.op[0]), ex(p->opr.op[1]));
							h->print_graph(pFile);
	 						return 0;
		case ACTTYPE_INVOCATION:	return INVOCATION;
		case ACTTYPE_RESPONSE:		return RESPONSE;
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



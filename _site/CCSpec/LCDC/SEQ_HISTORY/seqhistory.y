%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <string.h>
#include "seqhistory.h"
#include <queue>
#include <stack>
#include <map>
#include <deque>

#define EMPTY (uint64_t) 18446744073709551615

FILE * pFile;

std::queue<uint64_t> *q;
std::stack<uint64_t> *s;
std::map<uint64_t,uint64_t> *m;
std::deque<uint64_t> *dq; 
std::priority_queue<uint64_t, std::vector<uint64_t>, std::greater<uint64_t> > *pq_min;

/* prototypes */
extern "C"
{
    nodeType *opr(int oper, int nops, ...);
    nodeType *id(int i);
    nodeType *idString(char *i);
    nodeType *con(int value);
	nodeType *con64(uint64_t value);
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
	uint64_t iValue64;			 
};

%token <iValue> INTEGER
%token <sIndex> VARIABLE
%token <charArray> ALPHANUM
%token <iValue64> INTEGER64
%token WHILE IF PRINT FOR FORALL EXISTS FPRINTF 
%token ENQUEUE DEQUEUE
%token PUSH POP
%token PUT GET REMOVE
%token PUSHBACK POPBACK POPFRONT PUSHFRONT
%token INSERT DELETEMIN
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
        | PUSH '(' expr ')' ';'              			    { $$ = opr(PUSH, 1, $3); } 
        | POP '(' ')' ';'        						    { $$ = opr(POP,0); }  
		| PUT '(' expr ',' expr ')'	';'						{ $$ = opr(PUT, 2, $3, $5); } 
		| GET '(' expr ')' ';'								{ $$ = opr(GET, 1, $3); } 
		| REMOVE '(' expr ')' ';'							{ $$ = opr(REMOVE, 1, $3); } 
		| PUSHBACK '(' expr ')' ';'              			{ $$ = opr(PUSHBACK, 1, $3); } 
		| POPBACK '(' ')' ';'        						{ $$ = opr(POPBACK,0); }  
		| POPFRONT '(' ')' ';'        						{ $$ = opr(POPFRONT,0); }  
		| PUSHFRONT '(' expr ')' ';'              			{ $$ = opr(PUSHFRONT, 1, $3); }
		| INSERT '(' expr ')' ';'                           { $$ = opr(INSERT, 1, $3); }
		| DELETEMIN '(' ')' ';'        						{ $$ = opr(DELETEMIN, 0); }  
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
        | INTEGER64                                                             { $$ = con64($1); }
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

	/* copy information to con64 */
    p->con64.value = (uint64_t) value;

    return p;
}

nodeType *con64(uint64_t value) {
    nodeType *p;

    /* allocate node */
    if ((p = (nodeType*) malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeCon64;
    p->con64.value = value;
    //fprintf(pFile, "%lu ", p->con64.value); 
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
       
    std::queue<uint64_t> queue;
    q = &queue;
    
    std::stack<uint64_t> stack;  
    s = &stack; 

	std::map<uint64_t,uint64_t> map;
	m = &map;

	std::deque<uint64_t> deque; 
	dq = &deque;
	
	std::priority_queue<uint64_t, std::vector<uint64_t>, std::greater<uint64_t> > priorityqueue_min;
	pq_min = &priorityqueue_min;
    
	pFile = fopen("LCDC/SEQ_HISTORY/output.txt", "a");

	//pFile = fopen("example.txt", "a");     
  
    yyparse();

	fprintf(pFile, "\n");

	fclose(pFile);
	
    return 0;
}

int ex(nodeType *p) {

	int result;
	
	uint64_t result64;

	std::pair<std::map<uint64_t,uint64_t>::iterator,bool> got;
	std::map<uint64_t,uint64_t>::iterator it;
    
    if (!p) return 0;
    switch(p->type) {
    case typeCon:       return p->con.value; //fprintf(pFile, "%d ", p->con.value); 
	case typeCon64:     return 0;  //Need to directly access this parameter since it is type uint64_t //fprintf(pFile, "%lu ", p->con64.value); 
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
        case ENQUEUE:   fprintf(pFile, "0 "); q->push(p->opr.op[0]->con64.value); return 0;
        case DEQUEUE:   if(!q->empty()) 
						{ 
							result64 = q->front(); 
							q->pop(); 
						} else {
							result64 = 0;
						}
						fprintf(pFile, "%lu ", result64); 
						return result64;
        case PUSH:      fprintf(pFile, "0 "); s->push(p->opr.op[0]->con64.value); return 0; //fprintf(pFile, "%lu ", p->opr.op[0]->con64.value);
        case POP:       if(!s->empty())
                        {
                            result64 = s->top();
                            s->pop();                         
                        } else {
                            result64 = 0;                      
                        }
                        fprintf(pFile, "%lu ", result64);
                        return result64; //result = s->top(); s->pop(); fprintf(pFile, "%lu ", result); return result;
		case PUT: 		got = m->insert(std::pair<uint64_t,uint64_t>(p->opr.op[0]->con64.value, p->opr.op[1]->con64.value)); 
						//m->insert(std::make_pair(p->opr.op[0]->con64.value, p->opr.op[1]->con64.value));  
					
						if(got.second == false)
						{
							result64 = got.first->second;
						} else {
							result64 = 0;
						}
						fprintf(pFile, "%lu ", result64); 
						return 0; 
		case GET:		it = m->find(p->opr.op[0]->con64.value);
		                if(it != m->end())
		                {
		                    result64 = it->second;
		                } else {
		                    result64 = 0;
		                }
		                fprintf(pFile, "%lu ", result64); 
		                return 0;
		case REMOVE:	it = m->find(p->opr.op[0]->con64.value);
		                if(it != m->end())
		                {
		                    result64 = it->second;
		                    m->erase(it);
		                } else {
		                    result64 = 0;
		                }
		                fprintf(pFile, "%lu ", result64); 
		                return 0;
		case PUSHBACK:	fprintf(pFile, "0 "); dq->push_back(p->opr.op[0]->con64.value); return 0; //fprintf(pFile, "%lu ", p->opr.op[0]->con64.value);
		case POPBACK:	if(!dq->empty())
                        {
                            result64 = dq->back();
                            dq->pop_back();                         
                        } else {
							//result64 = 0;
                            result64 = EMPTY;                      
                        }
                        fprintf(pFile, "%lu ", result64);
                        return result64; //result = s->top(); s->pop(); fprintf(pFile, "%lu ", result); return result;
		case POPFRONT:	if(!dq->empty())
                        {
                            result64 = dq->front();
                            dq->pop_front();                         
                        } else {
							//result64 = 0;
                            result64 = EMPTY;                      
                        }
                        fprintf(pFile, "%lu ", result64);
                        return result64; //result = s->top(); s->pop(); fprintf(pFile, "%lu ", result); return result;
		case PUSHFRONT: fprintf(pFile, "0 "); dq->push_front(p->opr.op[0]->con64.value); return 0; //fprintf(pFile, "%lu ", p->opr.op[0]->con64.value);
		case INSERT:    fprintf(pFile, "0 "); pq_min->push(ex(p->opr.op[0])); return 0;
		case DELETEMIN: if(!pq_min->empty())
                        {
                            result64 = pq_min->top();
                            pq_min->pop();                         
                        } else {
							result64 = 0;
                            //result64 = EMPTY;                      
                        }
                        fprintf(pFile, "%lu ", result64);	
                        return result64;	
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



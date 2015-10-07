typedef struct Code{
	int op;
	int l;
	int m; 
	char name[MAX_WORD_LENGTH]; //NEW name up to 11 char      
} Code_t;

typedef enum op {
     LIT = 1, OPR, LOD, STO, CAL, INC, JMP, JPC, SIO     
} op_t;

typedef enum OPR_CODE {
     RET = 0, NEG, ADD, SUB, MUL, DIV, ODD, MOD, EQL, NEQ, LSS, LEQ, GTR, GEQ
} OPR_CODE_t;

void emit(int op, int l, int m);

void emit(int op, int l, int m, char *str); //NEW

int program(int i);

int block(int i);

int statement(int i);

int condition(int i);

int expression(int i);

int term(int i);

int factor(int i);

void generate_code();

extern Code_t code[MAX_CODE_LENGTH];

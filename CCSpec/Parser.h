typedef enum symbol_type{
    const_t = 1,
    var_t,
    proc_t
} symbol_type_t;

typedef struct symbol{
     symbol_type_t kind; //const = 1, var = 2, proc = 3
     char name[MAX_WORD_LENGTH]; //name up to 11 char
     int val; //number(ASCII value)
     int level; //L level
     int addr; //M address
} symbol_t;

int PROGRAM(int i);

int BLOCK(int i);

int STATEMENT(int i);

int CONDITION(int i);

int EXPRESSION(int i);

int TERM(int i);

int FACTOR(int i);

void parse_data();

extern symbol_t symbolTable[MAX_COMMANDS];



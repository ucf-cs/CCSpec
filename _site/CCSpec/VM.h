typedef struct instruction {
    int op; //opcode
    int l; //L
    int m; //M   
} instruction_t;

int base(int l, int base);

void run_VM();

extern int stack[MAX_COMMANDS];

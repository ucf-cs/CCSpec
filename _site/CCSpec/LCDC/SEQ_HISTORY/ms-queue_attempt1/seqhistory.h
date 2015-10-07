#define SIZE 126

typedef enum { typeCon, typeId, typeOpr, typeIdString, typePtr } nodeEnum;

/* constants */
typedef struct {
    int value;                  /* value of constant */
} conNodeType;

/* identifiers */
typedef struct {
    int i;                      /* subscript to sym array */
} idNodeType;

/* operators */
typedef struct {
    int oper;                   /* operator */
    int nops;                   /* number of operands */
    struct nodeTypeTag **op;	/* operands */
} oprNodeType;

/* constants */
typedef struct {
    void * addr;                  /* address of pointer */
} ptrNodeType;

typedef struct nodeTypeTag {
    nodeEnum type;              /* type of node */

    union {
        conNodeType con;        /* constants */
        idNodeType id;          /* identifiers */
        oprNodeType opr;        /* operators */
        ptrNodeType ptr;        /* pointers */
    };
} nodeType;

typedef struct {
    char *key;
    int value;
} symbolType;

//extern int sym[26];
extern symbolType sym[SIZE];



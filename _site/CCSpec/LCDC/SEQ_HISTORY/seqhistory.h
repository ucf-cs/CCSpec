#include <stdint.h>

#define SIZE 126

typedef enum { typeCon, typeId, typeOpr, typeIdString, typeCon64 } nodeEnum;

/* constants */
typedef struct {
    int value;                  /* value of constant */
} conNodeType;

/* constants */
typedef struct {
    uint64_t value;                  /* value of constant of type uint64_t */
} con64NodeType;

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

typedef struct nodeTypeTag {
    nodeEnum type;              /* type of node */

    union {
        conNodeType con;        /* constants */
        idNodeType id;          /* identifiers */
        oprNodeType opr;        /* operators */
		con64NodeType con64;    /* constants of type uint64_t */
    };
} nodeType;

typedef struct {
    char *key;
    int value;
} symbolType;

//extern int sym[26];
extern symbolType sym[SIZE];



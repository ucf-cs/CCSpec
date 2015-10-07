#include <string>

#define MAX_COMMANDS 2000
#define MAX_WORD_LENGTH 11
#define MAX_DIGIT_LENGTH 6
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 3

typedef enum token_type {
	nulsym = 1, identsym, numbersym, plussym, minussym,
    multsym,  slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
    gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
    periodsym, becomessym, beginsym, endsym, ifsym, thensym, 
    whilesym, dosym, callsym, constsym, intsym, procsym, outsym,
    insym , elsesym, 
	//TODO add more as needed
	andsym, orsym

} token_type_t;

typedef struct token_record {
	token_type_t type;
	char lexeme[MAX_WORD_LENGTH];
} token_record_t;

extern token_record_t tokenList[MAX_COMMANDS];

void lexical_analysis(std::string *s);

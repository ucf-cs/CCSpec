#include <string>

#include "modeltypes.h"
#include "../action.h"
#include "../stl-model.h"

/* Forward declaration */
//class ModelAction;

typedef enum operation_type {
	LOAD,
	STORE,
	EXCHANGE,
	FETCH_ADD,
	FETCH_SUB,
	COMPARE_EXCHANGE_STRONG,
	COMPARE_EXCHANGE_WEAK
	//ADD MORE AS NEEDED
} operation_type_t;

extern ModelVector<ModelAction *> program_stack;

void print_action_type(action_type_t type);

void function_call(std::string function_name, action_type_t func_type);

void function_call(std::string function_name, action_type_t func_type, uint64_t input);

void function_call(std::string function_name, action_type_t func_type, uint64_t input, uint64_t input2);

bool compare_str (std::string *first, std::string *second);

bool same_str (std::string *first, std::string *second);

void linearization_point(operation_type_t op, void *loc);

void linearization_point(operation_type_t op, std::string func_pair, void * loc);

void result(operation_type_t op, void* loc);

void invariant(std::string s);

void correctness_condition(std::string s);

void handle_invariant(std::string *s);

void variable(operation_type_t op, std::string variable, std::string validation);

void printInstructions();

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

typedef enum function_status {
    INACTIVE = 0,
	PENDING,
    ACTIVE
} function_status_t;

typedef struct LP_record {
	ModelAction const *LP;
	ModelAction const *from;
	unsigned int func_num;
	std::string *function_name;
	std::string function_pair;
	ModelList<std::string*> overlap;
		
} LP_record_t;

typedef struct LP_pending {
	std::string function_pair;
	action_type_t LP_action;
	//void *location;
} LP_pending_t;

typedef struct status_record {
	ModelVector<function_status_t> status;
	unsigned int func_num;
	std::string *function_name;
	//std::string function_pair;
   	ModelAction const *prev;
	ModelAction const *curr;
	ModelAction *result;
	ModelAction *result_final;
	//bool LP_flag;
	bool func_flag;
	bool invariant_flag;
	bool variable_flag;
	action_type_t variable_op;
	std::string *variable_name;
	std::string *validation_name;
	//action_type_t LP_action;
	ModelVector<LP_record_t> LP_records;
	ModelVector<LP_pending_t> LP_pending_list;
	//void *location;
} status_record_t;

extern ModelVector<ModelAction *> program_stack;

void print_action_type(action_type_t type);

void initialize_status_rec(unsigned int num_threads, status_record_t * records);

//void finalize_pending_func(unsigned int num_threads, status_record_t * records, int tid, ModelList<std::string*> *overlapping_functions);

void function_call(std::string function_name, action_type_t func_type);

void function_call(std::string function_name, action_type_t func_type, uint64_t input);

void function_call(std::string function_name, action_type_t func_type, uint64_t input, uint64_t input2);

bool compare_str (std::string *first, std::string *second);

bool same_str (std::string *first, std::string *second);

bool compare_LP (LP_record_t first, LP_record_t second);

bool isCyclicUtil(int v, bool visited[], bool *recStack, ModelVector<unsigned int> *func_graph);

bool isCyclic(unsigned int num_functions, ModelVector<unsigned int> *func_graph);

//void initialize_overlap_func(unsigned int num_threads, std::string **functions);

void linearization_point(operation_type_t op, void *loc);

void linearization_point(operation_type_t op, std::string func_pair, void * loc);

void result(operation_type_t op, void* loc);

void invariant(std::string s);

void correctness_condition(std::string s);

void handle_invariant(std::string *s);

void variable(operation_type_t op, std::string variable, std::string validation);

bool checkLinearizable();

void checkSeqConsistency();

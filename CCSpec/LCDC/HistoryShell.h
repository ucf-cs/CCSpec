#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector> 
#include <list>
#include <array>
#include <unordered_map>

#define CHAR_BUFFER 10000
#define FILENAME "LCDC/historyObj.txt"

typedef enum action_type {
	MODEL_FIXUP_RELSEQ,   /**< Special ModelAction: finalize a release
	                       *   sequence */
	THREAD_CREATE,        /**< A thread creation action */
	THREAD_START,         /**< First action in each thread */
	THREAD_YIELD,         /**< A thread yield action */
	THREAD_JOIN,          /**< A thread join action */
	THREAD_FINISH,        /**< A thread completion action */
	ATOMIC_UNINIT,        /**< Represents an uninitialized atomic */
	ATOMIC_READ,          /**< An atomic read action */
	ATOMIC_WRITE,         /**< An atomic write action */
	ATOMIC_RMWR,          /**< The read part of an atomic RMW action */
	ATOMIC_RMW,           /**< The write part of an atomic RMW action */
	ATOMIC_RMWC,          /**< Convert an atomic RMW action into a READ */
	ATOMIC_INIT,          /**< Initialization of an atomic object (e.g.,
	                       *   atomic_init()) */
	ATOMIC_FENCE,         /**< A fence action */
	ATOMIC_LOCK,          /**< A lock action */
	ATOMIC_TRYLOCK,       /**< A trylock action */
	ATOMIC_UNLOCK,        /**< An unlock action */
	ATOMIC_NOTIFY_ONE,    /**< A notify_one action */
	ATOMIC_NOTIFY_ALL,    /**< A notify all action */
	ATOMIC_WAIT,          /**< A wait action */
	ATOMIC_ANNOTATION,     /**< An annotation action to pass information
													 to a trace analysis */
    LINEARIZATION_POINT,   	/*CLP ADDED*/
    INVOCATION,             /*CLP ADDED*/
    RESPONSE,             /*CLP ADDED*/
	RESULT,					/*CLP ADDED*/
	INVARIANT,				/*CLP ADDED*/
	IDENTIFIER,               /*CLP ADDED*/
	CORRECTNESS_CONDITION   /*CLP ADDED*/
} action_type_t;            

typedef enum memory_order {
    memory_order_relaxed, memory_order_acquire, memory_order_release,
    memory_order_acq_rel, memory_order_seq_cst
} memory_order;

typedef struct action {
    action_type_t type;
    memory_order order;
    int tid;
    int seq_num;
} action_t;

class HistoryShell {
public:

    HistoryShell();
    ~HistoryShell();
    
    action_t *s;
    
    int p;
    unsigned int length;
    
    int method_id(unsigned int index, int tid);
    int is_active(unsigned int index, int tid);
	char * method_name(unsigned int index, int tid);
    void happens_before(FILE *pFile, int id1, int id2);
	bool retrieve_history(FILE *pFile);

	void print_graph(FILE *pFile);
	void topological_sort(FILE *pFile);
	//void bt_topological_sort(FILE *pFile, int n, std::list<int> L, std::list<int> S, std::vector<int> ts_graph[], std::list<int> inverse_graph[]);
	void bt_topological_sort(FILE *pFile, int n, std::list<int> L, std::list<int> S, std::vector<int> ts_graph[]);

	void get_legal_seq_histories(FILE *pFile);
	
	void map_legal_seq_histories(FILE *pFile);

	//static std::stringstream ss;
	//ModelOFstream ofs;

private:
	
	typedef enum method_status {
		INACTIVE = 0,
		ACTIVE
	} method_status_t;

	typedef struct method_record {
		method_status_t status;
		int method_number;
		char method_name[CHAR_BUFFER];
        uint64_t input;
		uint64_t input2;
		uint64_t output;
	} method_record_t;
	
	typedef struct method_descr {
	    char method_name[CHAR_BUFFER];
	    uint64_t input;	
		uint64_t input2;
	} method_descr_t;

	typedef struct output_record {
	    int method_number;
	    uint64_t output;	
	} output_record_t;
	
	std::unordered_map<int,method_descr_t> method_map;

	method_record_t **records;
	
	std::string *condition;

	//std::vector<int> *func_graph;
	//std::vector<int> func_graph[6]; //Trying changing to a list of vectors
	std::vector< std::vector<int> > func_graph;
	
	int num_functions;
	
	std::list<std::list<int>> legal_seq_histories;
	
	std::list<uint64_t> output;

	std::list<std::list<uint64_t>> output_matrix;

	uint64_t *output_array;

};


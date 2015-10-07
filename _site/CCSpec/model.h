/** @file model.h
 *  @brief Core model checker.
 */

#ifndef __MODEL_H__
#define __MODEL_H__

#include <cstddef>
#include <inttypes.h>

#include "mymemory.h"
#include "hashtable.h"
#include "config.h"
#include "modeltypes.h"
#include "stl-model.h"
#include "context.h"
#include "params.h"

/* Forward declaration */
class Node;
class NodeStack;
class CycleGraph;
class Promise;
class Scheduler;
class Thread;
class ClockVector;
class TraceAnalysis;
class ModelExecution;
class ModelAction;

typedef SnapList<ModelAction *> action_list_t;

/** @brief Model checker execution stats */
struct execution_stats {
	int num_total; /**< @brief Total number of executions */
	int num_infeasible; /**< @brief Number of infeasible executions */
	int num_buggy_executions; /** @brief Number of buggy executions */
	int num_complete; /**< @brief Number of feasible, non-buggy, complete executions */
	int num_redundant; /**< @brief Number of redundant, aborted executions */
};

/** @brief The central structure for model-checking */
class ModelChecker {
public:
	ModelChecker(struct model_params params);
	~ModelChecker();

	void run();

	/** @returns the context for the main model-checking system thread */
	ucontext_t * get_system_context() { return &system_context; }

	ModelExecution * get_execution() const { return execution; }

	int get_execution_number() const { return execution_number; }

	Thread * get_thread(thread_id_t tid) const;
	Thread * get_thread(const ModelAction *act) const;

	Thread * get_current_thread() const;

	void switch_from_master(Thread *thread);
	uint64_t switch_to_master(ModelAction *act);

	bool assert_bug(const char *msg, ...);
	void assert_user_bug(const char *msg);

	const model_params params;
	void add_trace_analysis(TraceAnalysis *a) {
		trace_analyses.push_back(a);
	}
	
	//CLP ADDED
	unsigned int get_num_threads_public() const;

	MEMALLOC
private:
	/** The scheduler to use: tracks the running/ready Threads */
	Scheduler * const scheduler;
	NodeStack * const node_stack;
	//CLP ADDED
	
	//CLP ADDED
	typedef struct output_record {
	    uint64_t value;
	} output_record_t;
	
    typedef struct stack_container {	
        ModelVector<output_record_t> stack;
    } stack_container_t;
	
	//ModelVector<ModelAction*> program_stack;
	//ModelVector<const NodeStack*> safeHistories;
	//ModelVector<const NodeStack*> unsureHistories;
	ModelVector<stack_container_t> safeHistories;
	ModelVector<stack_container_t> unsureHistories;

	bool checkReads();
	bool checkHistories();
	bool checkCorrectnessCondition();
	
	ModelExecution *execution;

	int execution_number;

	unsigned int get_num_threads() const;

	void execute_sleep_set();

	bool next_execution();
	bool should_terminate_execution();

	Thread * get_next_thread();
	void reset_to_initial_state();


	ModelAction *diverge;
	ModelAction *earliest_diverge;

	ucontext_t system_context;

	ModelVector<TraceAnalysis *> trace_analyses;

	/** @brief The cumulative execution stats */
	struct execution_stats stats;
	void record_stats();
	void run_trace_analyses();
	void print_bugs() const;
	void print_execution(bool printbugs) const;
	void print_stats() const;

	friend void user_main_wrapper();
};

extern ModelChecker *model;

#endif /* __MODEL_H__ */

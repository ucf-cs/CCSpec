//#include "impatomic.h"
//#include "common.h"
#include "linearizable_NEW.h"
#include "model.h"
#include "threads-model.h"
#include "execution.h"
#include "nodestack.h"
#include "clockvector.h"
#include "cyclegraph.h"

//TODO Revise so only need to attach one header file
#include "LexicalAnalyzer.h"
#include "Parser.h"
#include "CodeGenerator.h"
#include "VM.h"

//std::unordered_map<std::string,int> function_map;
//ModelList<std::string*> overlapping_functions;

ModelVector<ModelAction *> program_stack;

void print_action_type(action_type_t type)
{
    switch(type){
        case MODEL_FIXUP_RELSEQ:
            model_print("MODEL_FIXUP_RELSEQ ");
            break; 
        case THREAD_CREATE:
            model_print("THREAD_CREATE ");
            break; 
        case THREAD_START:
            model_print("THREAD_START ");
            break; 
        case THREAD_JOIN:
            model_print("THREAD_JOIN ");
            break; 
        case THREAD_YIELD:
            model_print("THREAD_YIELD ");
            break; 
        case THREAD_FINISH:
            model_print("THREAD_FINISH ");
            break; 
        case ATOMIC_UNINIT:
            model_print("ATOMIC_UNINIT ");
            break; 
        case ATOMIC_READ:
            model_print("ATOMIC_READ ");
            break;   
        case ATOMIC_WRITE:
            model_print("ATOMIC_WRITE ");
            break;   
        case ATOMIC_RMWR:
            model_print("ATOMIC_RMWR ");
            break;   
        case ATOMIC_RMW:
            model_print("ATOMIC_RMW ");
            break;  
        case ATOMIC_RMWC:
            model_print("ATOMIC_RMWC ");
            break;   
        case ATOMIC_INIT:
            model_print("ATOMIC_INIT ");
            break;   
        case ATOMIC_FENCE:
            model_print("ATOMIC_FENCE ");
            break;   
        case ATOMIC_LOCK:
            model_print("ATOMIC_LOCK ");
            break;   
        case ATOMIC_TRYLOCK:
            model_print("ATOMIC_TRYLOCK ");
            break;   
        case ATOMIC_UNLOCK:
            model_print("ATOMIC_UNLOCK ");
            break;   
        case ATOMIC_NOTIFY_ONE:
            model_print("ATOMIC_NOTIFY_ONE ");
            break;   
        case ATOMIC_NOTIFY_ALL:
            model_print("ATOMIC_NOTIFY_ALL ");
            break; 
        case ATOMIC_WAIT:
            model_print("ATOMIC_WAIT ");
            break;    
        case ATOMIC_ANNOTATION:
            model_print("ATOMIC_ANNOTATION ");
            break; 
        case LINEARIZATION_POINT:
            model_print("LINEARIZATION_POINT ");
            break;   
        case INVOCATION:
            model_print("INVOCATION ");
            break;  
		case RESPONSE:
            model_print("RESPONSE ");
            break;
		case RESULT:
            model_print("RESULT ");
            break;  
		case INVARIANT:
            model_print("INVARIANT ");
            break;  
        case IDENTIFIER:
            model_print("IDENTIFIER ");
            break; 
        case CORRECTNESS_CONDITION:
            model_print("CORRECTNESS_CONDITION ");
            break;
        default : 
           model_print("DEFAULT ");
           break;
    }
 
}

static const ModelExecution * get_execution()
{
	return model->get_execution();
}

void initialize_status_rec(unsigned int num_threads, status_record_t * records)
{
    for(unsigned int i = 0; i < num_threads; i++)
    {
		records[i].status.push_back(INACTIVE);
		records[i].func_num = 0;
        records[i].prev = NULL;
        records[i].curr = NULL;
		records[i].result = NULL;
		records[i].result_final = NULL;
        //records[i].LP = NULL;
        //records[i].from = NULL;
        //records[i].LP_flag = false;
		records[i].func_flag = false;
		records[i].invariant_flag = false;
		records[i].variable_flag = false;
        //records[i].LP_action = NULL;
		//records[i].location = NULL;
    }
}

/*
void finalize_pending_func(unsigned int num_threads, status_record_t * records, int tid, ModelList<std::string*> *overlapping_functions)
{
	for(unsigned int i = 2; i < num_threads; i++)
    {
		if (records[i].status == PENDING) 
		{
			records[i].status = INACTIVE;
			records[i].prev = records[tid].curr;
			records[tid].prev = records[i].curr;
			//TODO Check this line
			overlapping_functions[i].remove(records[tid].function_name); 
			
		}
	
    }

}
*/

void function_call(std::string function_name, action_type_t func_type)
{
	//model_print("FUNCTION CALL: %s\n", function_name);
	switch(func_type){
	    case INVOCATION:
	        //model->switch_to_master(new ModelAction(FUNCTION_CALL, function_name, BEGIN));
			program_stack.push_back(new ModelAction(INVOCATION, function_name, (uint64_t) NULL));
	        break;
	    case RESPONSE:
	        //model->switch_to_master(new ModelAction(FUNCTION_CALL, function_name, END));
			program_stack.push_back(new ModelAction(RESPONSE, function_name, (uint64_t) NULL));
	        break;
	    default :
	        model_print("DEFAULT ");
	        break;
	}
		
}

void function_call(std::string function_name, action_type_t func_type, uint64_t input)
{
	//model_print("FUNCTION CALL: %s\n", function_name);
	switch(func_type){
	    case INVOCATION:
	        //model->switch_to_master(new ModelAction(FUNCTION_CALL, function_name, BEGIN));
			program_stack.push_back(new ModelAction(INVOCATION, function_name, input));
	        break;
	    case RESPONSE:
	        //model->switch_to_master(new ModelAction(FUNCTION_CALL, function_name, END));
			program_stack.push_back(new ModelAction(RESPONSE, function_name, input));
	        break;
	    default :
	        model_print("DEFAULT ");
	        break;
	}
		
}

void function_call(std::string function_name, action_type_t func_type, uint64_t input, uint64_t input2)
{
	//model_print("FUNCTION CALL: %s\n", function_name);
	switch(func_type){
	    case INVOCATION:
	        //model->switch_to_master(new ModelAction(FUNCTION_CALL, function_name, BEGIN));
			program_stack.push_back(new ModelAction(INVOCATION, function_name, input, input2));
	        break;
	    case RESPONSE:
	        //model->switch_to_master(new ModelAction(FUNCTION_CALL, function_name, END));
			program_stack.push_back(new ModelAction(RESPONSE, function_name, input, input2));
	        break;
	    default :
	        model_print("DEFAULT ");
	        break;
	}
		
}

bool compare_str (std::string *first, std::string *second)
{
  	if(((*first).compare((*second)) == 0) || (*first).compare((*second)) < 0)
		return true;
  	else return false;
}

bool same_str (std::string *first, std::string *second) 
{ 
	return ( (*first).compare((*second)) == 0 ); 
}

bool compare_LP (LP_record_t first, LP_record_t second)
{
	if(first.LP->get_seq_number() < second.LP->get_seq_number())
		return true;
	else
		return false;
}

bool isCyclicUtil(unsigned int v, bool *visited, bool *recStack, ModelVector<unsigned int> *func_graph)
{
    if(visited[v] == false)
    {

        visited[v] = true;
        recStack[v] = true;
 
        ModelVector<unsigned int>::iterator i;
        for(i = func_graph[v].begin(); i != func_graph[v].end(); ++i)
        {
            if ( !visited[*i] && isCyclicUtil(*i, visited, recStack, func_graph) )
                return true;
            else if (recStack[*i])
                return true;
        }
 
    }
    recStack[v] = false; 
    return false;
}
 
bool isCyclic(unsigned int num_functions, ModelVector<unsigned int> *func_graph)
{
    
    bool visited[num_functions];
    bool recStack[num_functions];
    for(unsigned int i = 0; i < num_functions; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }
 
    for(unsigned int i = 0; i < num_functions; i++)
        if (isCyclicUtil(i, visited, recStack, func_graph))
            return true;
 
    return false;
}

/*
void initialize_overlap_func(unsigned int num_threads, std::string **functions)
{
    for(unsigned int i = 0; i < num_threads; i++)
    {
        functions[i] = NULL;
    }
}
*/

void linearization_point(operation_type_t op, void* loc)
{
	//Create new ModelAction
	//ModelAction needs new parameters that set the linearization point flag and identify the operation

	std::string func_pair("");

	switch(op){
        case LOAD:
            //model->switch_to_master(new ModelAction(LINEARIZATION_POINT, ATOMIC_READ, func_pair, loc));
			program_stack.push_back(new ModelAction(LINEARIZATION_POINT, ATOMIC_READ, func_pair, loc));
            break; 
        case STORE:
            //model->switch_to_master(new ModelAction(LINEARIZATION_POINT, ATOMIC_WRITE, func_pair, loc));
			program_stack.push_back(new ModelAction(LINEARIZATION_POINT, ATOMIC_WRITE, func_pair, loc));
            break; 
        case EXCHANGE:
            //model->switch_to_master(new ModelAction(LINEARIZATION_POINT, ATOMIC_RMWR, func_pair, loc));
			program_stack.push_back(new ModelAction(LINEARIZATION_POINT, ATOMIC_RMWR, func_pair, loc));
            break; 
        case FETCH_ADD:
            //model->switch_to_master(new ModelAction(LINEARIZATION_POINT, ATOMIC_RMW, func_pair, loc));
			program_stack.push_back(new ModelAction(LINEARIZATION_POINT, ATOMIC_RMW, func_pair, loc));
            break; 
        case FETCH_SUB:
            //model->switch_to_master(new ModelAction(LINEARIZATION_POINT, ATOMIC_RMW, func_pair, loc));
			program_stack.push_back(new ModelAction(LINEARIZATION_POINT, ATOMIC_RMW, func_pair, loc));
            break; 
        case COMPARE_EXCHANGE_STRONG:
            //model->switch_to_master(new ModelAction(LINEARIZATION_POINT, ATOMIC_RMW, func_pair, loc));
			program_stack.push_back(new ModelAction(LINEARIZATION_POINT, ATOMIC_RMW, func_pair, loc));
            break; 
        case COMPARE_EXCHANGE_WEAK:
            //model->switch_to_master(new ModelAction(LINEARIZATION_POINT, ATOMIC_RMW, func_pair, loc));
			program_stack.push_back(new ModelAction(LINEARIZATION_POINT, ATOMIC_RMW, func_pair, loc));
            break;   
        default : 
           break;
    }
	
}

void result(operation_type_t op, void* loc)
{

	switch(op){
        case LOAD:
            //model->switch_to_master(new ModelAction(RESULT, ATOMIC_READ, func_pair, loc));
			program_stack.push_back(new ModelAction(RESULT, ATOMIC_READ, loc));
            break; 
        case STORE:
            //model->switch_to_master(new ModelAction(RESULT, ATOMIC_WRITE, func_pair, loc));
			program_stack.push_back(new ModelAction(RESULT, ATOMIC_WRITE, loc));
            break; 
        case EXCHANGE:
            //model->switch_to_master(new ModelAction(RESULT, ATOMIC_RMWR, func_pair, loc));
			program_stack.push_back(new ModelAction(RESULT, ATOMIC_RMWR, loc));
            break; 
        case FETCH_ADD:
            //model->switch_to_master(new ModelAction(RESULT, ATOMIC_RMW, func_pair, loc));
			program_stack.push_back(new ModelAction(RESULT, ATOMIC_RMW, loc));
            break; 
        case FETCH_SUB:
            //model->switch_to_master(new ModelAction(RESULT, ATOMIC_RMW, func_pair, loc));
			program_stack.push_back(new ModelAction(RESULT, ATOMIC_RMW, loc));
            break; 
        case COMPARE_EXCHANGE_STRONG:
            //model->switch_to_master(new ModelAction(RESULT, ATOMIC_RMW, func_pair, loc));
			program_stack.push_back(new ModelAction(RESULT, ATOMIC_RMW, loc));
            break; 
        case COMPARE_EXCHANGE_WEAK:
            //model->switch_to_master(new ModelAction(RESULT, ATOMIC_RMW, func_pair, loc));
			program_stack.push_back(new ModelAction(RESULT, ATOMIC_RMW, loc));
            break;   
        default : 
           break;
    }
	
}

void linearization_point(operation_type_t op, std::string func_pair, void *loc)
{
	//this is when the linearization point only occurs with a specified overlapping function
	switch(op){
        case LOAD:
            //model->switch_to_master(new ModelAction(LINEARIZATION_POINT, ATOMIC_READ, func_pair, loc));
			program_stack.push_back(new ModelAction(LINEARIZATION_POINT, ATOMIC_READ, func_pair, loc));
            break; 
        case STORE:
            //model->switch_to_master(new ModelAction(LINEARIZATION_POINT, ATOMIC_WRITE, func_pair, loc));
			program_stack.push_back(new ModelAction(LINEARIZATION_POINT, ATOMIC_WRITE, func_pair, loc));
            break; 
        case EXCHANGE:
            //model->switch_to_master(new ModelAction(LINEARIZATION_POINT, ATOMIC_RMWR, func_pair, loc));
			program_stack.push_back(new ModelAction(LINEARIZATION_POINT, ATOMIC_RMWR, func_pair, loc));
            break; 
        case FETCH_ADD:
            //model->switch_to_master(new ModelAction(LINEARIZATION_POINT, ATOMIC_RMW, func_pair, loc));
			program_stack.push_back(new ModelAction(LINEARIZATION_POINT, ATOMIC_RMW, func_pair, loc));
            break; 
        case FETCH_SUB:
            //model->switch_to_master(new ModelAction(LINEARIZATION_POINT, ATOMIC_RMW, func_pair, loc));
			program_stack.push_back(new ModelAction(LINEARIZATION_POINT, ATOMIC_RMW, func_pair, loc));
            break; 
        case COMPARE_EXCHANGE_STRONG:
            //model->switch_to_master(new ModelAction(LINEARIZATION_POINT, ATOMIC_RMW, func_pair, loc));
			program_stack.push_back(new ModelAction(LINEARIZATION_POINT, ATOMIC_RMW, func_pair, loc));
            break; 
        case COMPARE_EXCHANGE_WEAK:
            //model->switch_to_master(new ModelAction(LINEARIZATION_POINT, ATOMIC_RMW, func_pair, loc));
			program_stack.push_back(new ModelAction(LINEARIZATION_POINT, ATOMIC_RMW, func_pair, loc));
            break;   
        default : 
           break;
    }
	
}

void invariant(std::string s) 
{
	program_stack.push_back(new ModelAction(INVARIANT, s));
}

void handle_invariant(std::string *s)
{
    lexical_analysis(s);
    parse_data();
	generate_code();
}

void correctness_condition(std::string s)
{
    program_stack.push_back(new ModelAction(CORRECTNESS_CONDITION, s));
}

void variable(operation_type_t op, std::string variable, std::string validation)
{

	switch(op){
        case LOAD:
            //model->switch_to_master(new ModelAction(IDENTIFIER, ATOMIC_READ, variable, validation));
			program_stack.push_back(new ModelAction(IDENTIFIER, ATOMIC_READ, variable, validation));
            break; 
        case STORE:
            //model->switch_to_master(new ModelAction(IDENTIFIER, ATOMIC_WRITE, variable, validation));
			program_stack.push_back(new ModelAction(IDENTIFIER, ATOMIC_WRITE, variable, validation));
            break; 
        case EXCHANGE:
            //model->switch_to_master(new ModelAction(IDENTIFIER, ATOMIC_RMWR, variable, validation));
			program_stack.push_back(new ModelAction(IDENTIFIER, ATOMIC_RMWR, variable, validation));
            break; 
        case FETCH_ADD:
            //model->switch_to_master(new ModelAction(IDENTIFIER, ATOMIC_RMW, variable, validation));
			program_stack.push_back(new ModelAction(IDENTIFIER, ATOMIC_RMW, variable, validation));
            break; 
        case FETCH_SUB:
            //model->switch_to_master(new ModelAction(IDENTIFIER, ATOMIC_RMW, variable, validation));
			program_stack.push_back(new ModelAction(IDENTIFIER, ATOMIC_RMW, variable, validation));
            break; 
        case COMPARE_EXCHANGE_STRONG:
            //model->switch_to_master(new ModelAction(IDENTIFIER, ATOMIC_RMW, variable, validation));
			program_stack.push_back(new ModelAction(IDENTIFIER, ATOMIC_RMW, variable, validation));
            break; 
        case COMPARE_EXCHANGE_WEAK:
            //model->switch_to_master(new ModelAction(IDENTIFIER, ATOMIC_RMW, variable, validation));
			program_stack.push_back(new ModelAction(IDENTIFIER, ATOMIC_RMW, variable, validation));
            break;   
        default : 
           break;
    }
}

bool checkLinearizable()
{
		
    model_print("Checking for linearizability\n");
    
    //ModelVector<ModelAction *> program_stack = get_execution()->get_program_stack();  
    //NodeStack * const node_stack = get_execution()->get_node_stack();     
    //int const head_index = node_stack->get_head_idx();
    //model_print("Head Index = %d\n", head_index);
 
    CycleGraph *graph = new CycleGraph();
    unsigned int const num_threads = model->get_num_threads_public();
    
    //model_print("Number of threads = %d\n", num_threads);
    
	status_record_t records[num_threads]; 
	initialize_status_rec(num_threads, records);
	
	//std::string *overlapping_functions[num_threads];
	//initialize_overlap_func(num_threads, overlapping_functions);
	
	ModelList<std::string*> overlapping_functions[num_threads];
	
	unsigned int function_counter = 0;
	
    //for(int i = 0; i < head_index; i++)
    for(unsigned int i = 0; i < program_stack.size(); i++)
    {
 
        //Node * const node = node_stack->get_node(i);
        //ModelAction * const act = node->get_action();
        ModelAction * act = program_stack[i];
        action_type_t const type = act->get_type();
        
        if(!act->is_linearization_point() && type != INVOCATION && type != RESPONSE)
		{
			//TODO Can possibly get rid of the curr placeholder
		 	records[act->get_tid()].curr = act;
		    if(records[act->get_tid()].prev != NULL)
		    {
		        graph->addEdge(records[act->get_tid()].prev, records[act->get_tid()].curr);
		        
		    }
			if(act->get_reads_from() != NULL)
	        {
	            graph->addEdge(act->get_reads_from(), records[act->get_tid()].curr);
	        }
			
			if(records[act->get_tid()].func_flag == true)
			{
				for(unsigned int j = 2; j < num_threads; j++)
		        {	
					//Add Edge between PENDING functions and current Function
					
					if (records[j].status[act->get_tid()] == PENDING) 
					{
						records[j].status[act->get_tid()] = INACTIVE;
						if(records[j].prev != NULL)
							graph->addEdge(records[j].prev, records[act->get_tid()].curr);

						//The edge for the PENDING function was just added, so no need to add it again
						records[j].prev = NULL; 
						/*
						ModelList<std::string*>::iterator it;
					    for(it = overlapping_functions[act->get_tid()].begin(); it != overlapping_functions[act->get_tid()].end(); ++it)
					    {				
						    model_print("Thread %d: Updated Overlap %s \n", act->get_tid(), (*it)->c_str());
					    }
						*/	
			
					}
						 
				}
				records[act->get_tid()].func_flag = false;
			}
		}
		/*
		curr = act;
		if(act->get_reads_from() != NULL)
		{
			graph->addEdge(act->get_reads_from(), curr);
		} else if (prev != NULL) {
			graph->addEdge(prev, curr); 
		}
		*/
      
		if(act->get_tid() != 1)
		{
		    model_print("\nThread %d: ", act->get_tid()); //act->get_seq_number(), 
		    print_action_type(type);
		} 
        if(type == ATOMIC_READ && act->get_tid() != 1) //&& act->get_tid() != 1
        {
            model_print("value = %lu ", act->get_reads_from_value()); 
        }
        if(type == ATOMIC_WRITE ) // && act->get_tid() != 1
        {
            model_print("value = %lu ", act->get_value());  
        }
        
        if(type == ATOMIC_RMW && act->get_tid() != 1) //&& act->get_tid() != 1
        {
            model_print("read value = %lu, write value = %lu ", act->get_reads_from_value(), act->get_value());  
        }

		if(type == INVARIANT)
		{
			records[act->get_tid()].invariant_flag = true;
			handle_invariant(act->get_function());
		}
		
		if(type == IDENTIFIER)
		{
		    records[act->get_tid()].variable_flag = true; 
		    records[act->get_tid()].variable_op = act->get_next_op();
		    records[act->get_tid()].variable_name = act->get_variable();
		    records[act->get_tid()].validation_name = act->get_validation();
		} else if ((records[act->get_tid()].variable_flag == true) && (records[act->get_tid()].invariant_flag == true)
		    && (type == records[act->get_tid()].variable_op))
		{
		    records[act->get_tid()].variable_flag = false;
		    for(int j = 0; j < (MAX_CODE_LENGTH - 1); j++)
		    {
		        if(code[j].op == 0)
		            break;
		        if(strcmp(records[act->get_tid()].variable_name->c_str(), code[j+1].name) == 0)
		        {
			        code[j].m = act->get_value();
			        model_print("\nLIT = %d %d %d\n", code[j].op, code[j].l, code[j].m);
			        break;
		        }
		    
		    }
		    run_VM();
		    
		    //Validate
            bool return_val = false;
            int pos = 0;
            for(int i = 0; i < MAX_CODE_LENGTH; i++)
            {
                if(code[i].op == 0)
                    break;
                if(strcmp(records[act->get_tid()].validation_name->c_str(), code[i].name) == 0)
                {
                    pos = code[i].m;        
                    break;
                }

            } 
            if(stack[pos] == 1)
                return_val = true;

		    if(return_val)
		        model_print("\nVALIDATION PASSED\n");
		    else 
		        model_print("\nVALIDATION FAILED\n");
		}

		if(records[act->get_tid()].result != NULL) 
		{
			if(type == records[act->get_tid()].result->get_next_op() ||
				((type == ATOMIC_RMW) && (records[act->get_tid()].result->get_next_op() == ATOMIC_RMWR)))
			{
				//act->set_result();
				model_print("result ");
				records[act->get_tid()].result_final = act;
				records[act->get_tid()].result = NULL;
				
			} 
		} else if(type == RESULT)
		{
			records[act->get_tid()].result = act;
		}
        
        if(type == INVOCATION)
        {
            model_print("Begin %s ", act->get_function()->c_str());
            if(act->get_input_output() != (uint64_t) NULL)
                model_print("input %lu ", act->get_input_output());
            //model_print("Begin %s", act->get_function());
            for(unsigned int j = 2; j < num_threads; j++)
                records[act->get_tid()].status[j] = ACTIVE;
            records[act->get_tid()].function_name = act->get_function();
			
			records[act->get_tid()].func_flag = true;

			records[act->get_tid()].func_num = function_counter++;

			//overlapping_functions.push_back(act->get_function());
			//overlapping_functions[act->get_tid()] = act->get_function();
			
			for(unsigned int j = 2; j < num_threads; j++)
            {
                
                if((int) j != act->get_tid())
				{
					overlapping_functions[j].push_back(act->get_function());
		            //overlapping_functions[j].sort(compare_str);
				    //overlapping_functions[j].unique(same_str);
				}
		        
		        ModelList<std::string*>::iterator it;
		        for(it = overlapping_functions[j].begin(); it != overlapping_functions[j].end(); ++it)
		        {				
			        //model_print("\nThread %d: Begin Overlap %s ",j, (*it)->c_str());
		        }
			
            }
            
				
	
			
            
        } else if (type == RESPONSE)
        {
            model_print("End %s output = %lu ", act->get_function()->c_str(), act->get_input_output());
            //model_print("End %s", act->get_function());
			//finalize_pending_func(num_threads, records, act->get_tid(), overlapping_functions);
			
			if(records[act->get_tid()].result_final != NULL)
			{
			    //model_print("HERE I AM ");
			    records[act->get_tid()].result_final->set_result();
			    //print_action_type(records[act->get_tid()].result_final->get_type());
			}

            for(unsigned int j = 2; j < num_threads; j++)
			    records[act->get_tid()].status[j] = PENDING;
			
			
			//overlapping_functions.remove(act->get_function());
			//overlapping_functions[act->get_tid()] = NULL;
			/*
			for(unsigned int j = 2; j < num_threads; j++)
            {             
		        ModelList<std::string*>::iterator it;
	            for(it = overlapping_functions[j].begin(); it != overlapping_functions[j].end(); ++it)
	            {				
		            model_print("\nThread %d: End Overlap %s ", j, (*it)->c_str());
	            }	       
			}
			*/
			//overlapping_functions[act->get_tid()].remove(records[j].function_name);
		
			for(unsigned int j = 0; j < records[act->get_tid()].LP_records.size(); j++)
			{
				//model_print("\n LP_records[j].func_num = %d records[act->get_tid()].func_num = %d", records[act->get_tid()].LP_records[j].func_num, records[act->get_tid()].func_num);
				if(records[act->get_tid()].LP_records[j].func_num == records[act->get_tid()].func_num)
				{
					ModelList<std::string*>::iterator it;
			        for(it = overlapping_functions[act->get_tid()].begin(); it != overlapping_functions[act->get_tid()].end(); ++it)
			        {		
				        //model_print("\nThread %d: Adding function %s to LP %d's list", act->get_tid(), (*it)->c_str(), j);
						records[act->get_tid()].LP_records[j].overlap.push_back(*it);
		            		
			        }
					records[act->get_tid()].LP_records[j].overlap.sort(compare_str);
				    records[act->get_tid()].LP_records[j].overlap.unique(same_str);		
				}
			}
			//records[act->get_tid()].func_num = records[act->get_tid()].func_num + 1;
			overlapping_functions[act->get_tid()].clear();
			for(unsigned int j = 2; j < num_threads; j++)
			{
				
				//TODO Check records[j].status[act->get_tid()] 
				if(((int) j!= act->get_tid()) && (records[j].status[act->get_tid()] == ACTIVE))
				{
					overlapping_functions[act->get_tid()].push_back(records[j].function_name);
				} else if(((int) j!= act->get_tid()) && ((records[j].status[act->get_tid()] == PENDING) || (records[j].status[act->get_tid()] == INACTIVE)) )
				{
					overlapping_functions[j].remove(records[act->get_tid()].function_name);
				}
				
			}
			
        } else {
            //model_print("Function type %d ", act->get_function_type());
        }
        
        if(act->is_linearization_point())
        {
            model_print("Linearization Point is ");
            print_action_type(act->get_next_op());
            //records[act->get_tid()].LP_flag = true;
            //records[act->get_tid()].LP_action = act->get_next_op();
           	//records[act->get_tid()].function_pair = *(act->get_function_pair());
			//records[act->get_tid()].location = act->get_location();
			LP_pending_t LP_item;
			LP_item.LP_action = act->get_next_op();
			LP_item.function_pair = *(act->get_function_pair());
			//LP_item.location = act->get_location();
			records[act->get_tid()].LP_pending_list.push_back(LP_item);

		/*
        } else if((records[act->get_tid()].LP_flag == true) && (type == records[act->get_tid()].LP_action)) {
			//&& ((act->get_location() == records[act->get_tid()].location) || (act->get_location() == NULL))) {            
            
            model_print("Linearization Point ");
            act->set_LP();
			LP_record_t LP_rec;
			LP_rec.LP = act;
			if(records[act->get_tid()].prev != NULL)
				LP_rec.from = records[act->get_tid()].prev;				
			else
            	LP_rec.from = act->get_reads_from();
			LP_rec.func_num = records[act->get_tid()].func_num;
			//model_print("Sequence number = %d ", LP_rec.func_num);
			
			LP_rec.function_name = records[act->get_tid()].function_name;
			LP_rec.function_pair.assign(records[act->get_tid()].function_pair);
			//model_print("Function pair = %s ", LP_rec.function_pair.c_str()); 
			model_print("Function name = %s ", LP_rec.function_name->c_str()); 
			//LP_rec.function_pair.assign(*(act->get_function_pair()));
			
			
			records[act->get_tid()].LP_records.push_back(LP_rec);
            records[act->get_tid()].LP_flag = false; 
			    
        }
        */
		} else if(records[act->get_tid()].LP_pending_list.size() != 0 ) {
			//ModelList<LP_pending_t>::iterator it;
			//for(it = records[act->get_tid()].LP_pending_list.begin(); it != records[act->get_tid()].LP_pending_list.end(); ++it)
			for(unsigned int j = 0; j < records[act->get_tid()].LP_pending_list.size(); j++)
			{
				//if(type == (*it).LP_action)
				if(type == records[act->get_tid()].LP_pending_list[j].LP_action)
				{
					model_print("Linearization Point ");
				    act->set_LP();
					LP_record_t LP_rec;
					LP_rec.LP = act;
					if(records[act->get_tid()].prev != NULL)
						LP_rec.from = records[act->get_tid()].prev;				
					else
				    	LP_rec.from = act->get_reads_from();
					LP_rec.func_num = records[act->get_tid()].func_num;
					//model_print("Sequence number = %d ", LP_rec.func_num);
			
					LP_rec.function_name = records[act->get_tid()].function_name;
					//LP_rec.function_pair.assign((*it).function_pair);
					LP_rec.function_pair.assign(records[act->get_tid()].LP_pending_list[j].function_pair);
					//model_print("Function pair = %s ", LP_rec.function_pair.c_str()); 
					model_print("Function name = %s ", LP_rec.function_name->c_str()); 
					//LP_rec.function_pair.assign(*(act->get_function_pair()));
			
					records[act->get_tid()].LP_records.push_back(LP_rec);
					records[act->get_tid()].LP_pending_list.erase(records[act->get_tid()].LP_pending_list.begin() + j);
					break;
				}

			}
			
		}
        
        
        //model_print("\n");
        //model_print("Clock Vector: %u\n", act->get_cv()->getClock(act->get_tid()));
        //model_print("Sequence Number: %u\n", act->get_func_number());
        
		if(!act->is_linearization_point() && type != INVOCATION && type != RESPONSE)
		{
			records[act->get_tid()].prev = records[act->get_tid()].curr;
		}
    }
    
    if(graph->checkForCycles())
    {
        //model_print("Cycles detected\n");
    
    } else {
        //model_print("No cycles detected\n");
    }
    bool check_overlap = false;
	bool safe_history = true;
	ModelList<LP_record_t> LP_record_list;
	for(unsigned int i = 2; i < num_threads; i++)
    {
		
		for(unsigned int j = 0; j < records[i].LP_records.size(); j++)
		{
			LP_record_t curr = records[i].LP_records[j];
			LP_record_list.push_back(curr);
			if(curr.LP != NULL && curr.from != NULL)
		    {
		       
		        bool result = graph->checkReachable(curr.LP, curr.from); //This method crashes if NULL pointers are passed to it
		        if(result)
		        {
		            //model_print("Thread %d has a LP within a cycle.\n", curr.LP->get_tid());
					safe_history = false;
		        } else {
		            //model_print("Thread %d does not have any cycles.\n", curr.LP->get_tid());   
		        }
		      
		    }
		
			if(curr.function_pair.empty())
			{
				//model_print("Only one LP in this function. Overlap shouldn't be an issue.\n");
			} else {
				if(curr.overlap.size() > 1)
				{
					//model_print("Overlap over multiple functions exists. Continue checking.\n");
					check_overlap = true;
				} else {
					//model_print("No overlap.\n");
				}
			}
			
			
		}
           	
    }
	//The following code checks for problems with multiple overlapping functions.
	//If no overlap exists or the history is already flagged, we can skip this step.
	if(check_overlap && safe_history) 
	{
		LP_record_list.sort(compare_LP);
		ModelList<LP_record_t>::iterator it;
		unsigned int const num_functions = function_counter;
		ModelVector<unsigned int> func_graph[num_functions];
		for(it = LP_record_list.begin(); it != LP_record_list.end(); ++it)
		{		
		
		    /*
		    model_print("Function Name = %s \n", (*it).function_name->c_str());
			model_print("Function Number = %u \n", (*it).func_num);
			model_print("Function Pair = %s \n", (*it).function_pair.c_str());
			model_print("--------------------\n");
	        */
			ModelList<LP_record_t>::iterator curr = it;
			for(++curr; curr != LP_record_list.end(); ++curr)
			{
                /*
				model_print("~Function Name = %s \n", (*curr).function_name->c_str());
				model_print("~Function Number = %u \n", (*curr).func_num);
				model_print("~Function Pair = %s \n", (*curr).function_pair.c_str());
				model_print("--------------------\n");
                */
				if((*it).func_num != (*curr).func_num) 
				{	     
				    //if((*it).function_pair.empty() || (((*it).function_pair.compare(*((*curr).function_name)) == 0) 
					    //&& (((*it).function_pair.compare((*curr).function_pair) == 0) || (*curr).function_pair.empty())))
				    if((*it).function_pair.empty() || ((*it).function_pair.compare(*((*curr).function_name)) == 0))
					{
					    
				        //model_print("\nFunction Pair: it = %s, curr = %s \n", (*it).function_pair.c_str(),(*curr).function_pair.c_str());
					    bool exists = false;
					    model_print("\nFunction %u happens before Function %u", (*it).func_num, (*curr).func_num);	
					    for(unsigned int i = 0; i < func_graph[(*it).func_num].size(); i++)
					    {
						    if(func_graph[(*it).func_num][i] == (*curr).func_num)
						    {
							    exists = true;
							    break;
						    }
					
					    } //We only want to add an edge in once
					    if(!exists)
						    func_graph[(*it).func_num].push_back((*curr).func_num);					      
					}
			
				}

			}
		
		}
		bool has_cycles = isCyclic(num_functions, func_graph);
		if(has_cycles)
		{
			//model_print("Cyclic dependencies within overlapping functions\n");
			safe_history = false;
		}
		
	}
	if(safe_history)
	{
		model_print("\nHistory is safe\n");
		return true;
	} else {
		model_print("\nHistory flagged as potentially non-linearizable\n");
		return false;
    }
}

void checkSeqConsistency()
{
    model_print("Checking for Sequential Consistency\n");
    NodeStack * const node_stack = get_execution()->get_node_stack(); 
    int const head_index = node_stack->get_head_idx();
    //model_print("Head Index = %d\n", head_index);
    
    CycleGraph *graph = new CycleGraph();
    unsigned int const num_threads = model->get_num_threads_public();
    
    ModelAction const *prev[num_threads], *curr[num_threads], *LP[num_threads], *from[num_threads];
    //ModelAction const *curr[num_threads];
    //ModelAction const *LP[num_threads];
    //ModelAction const *from[num_threads];
    bool LP_flag[num_threads];
    action_type_t LP_action[num_threads];
    
    for(unsigned int i = 0; i < num_threads; i++)
    {
        prev[i] = NULL;
        curr[i] = NULL;
        LP[i] = NULL;
        from[i] = NULL;
        LP_flag[i] = false;
      
    }
    
    for(int i = 0; i < head_index; i++)
    {
        //int counter = head_index;
        
        Node * const node = node_stack->get_node(i);
        ModelAction * const act = node->get_action();
        action_type_t const type = act->get_type();
        
        curr[act->get_tid()] = act;
        if(prev[act->get_tid()] != NULL)
        {
            graph->addEdge(prev[act->get_tid()], curr[act->get_tid()]);
            if(act->get_reads_from() != NULL)
            {
                graph->addEdge(act->get_reads_from(), curr[act->get_tid()]);
            }
        }
        
        
        /*
        bool flag = false;
        for(int j = 0; j < head_index; j++)
        {

            //if(act->happens_before(node_stack->get_node(j)->get_action()))
                //counter--;
          
            if (node_stack->get_node(j)->get_action() == act->get_reads_from())

            {
                flag = true;
            }
        

        }
     
        */
        
        model_print("Thread %d: ", act->get_tid());
        print_action_type(type);
        if(type == ATOMIC_READ)
        {
            model_print("value = %lu ", act->get_reads_from_value()); 
            //model_print("execution order = %d ", counter);      
        }
        if(type == ATOMIC_WRITE)
        {
            model_print("value = %lu ", act->get_value());  
            //model_print("execution order = %d ", counter);       
        }
        
        if(type == INVOCATION)
        {
            model_print("Begin %s ", act->get_function()->c_str());
            //model_print("Begin %s", act->get_function());
        } else if (type == RESPONSE)
        {
            model_print("End %s ", act->get_function()->c_str());
            //model_print("End %s", act->get_function());
        } else {
            //model_print("Function type %d ", act->get_function_type());
        }
        
        if(act->is_linearization_point())
        {
            model_print("Linearization Point is ");
            print_action_type(act->get_next_op());
            LP_flag[act->get_tid()] = true;
            LP_action[act->get_tid()] = act->get_next_op();
           
        } else if((LP_flag[act->get_tid()] == true) && (type == LP_action[act->get_tid()])) {            
            
            model_print("Linearization Point ");
            act->set_LP();
            LP[act->get_tid()] = act;
            from[act->get_tid()] = prev[act->get_tid()];
            LP_flag[act->get_tid()] = false;       
        }
        
        
        
        model_print("\n");
        //model_print("Clock Vector: %u\n", act->get_cv()->getClock(act->get_tid()));
        //model_print("Sequence Number: %u\n", act->get_func_number());
        
        prev[act->get_tid()] = curr[act->get_tid()];
    }
    
    if(graph->checkForCycles())
    {
        model_print("Cycles detected\n");
    
    } else {
        model_print("No cycles detected\n");
    }
    for(unsigned int i = 0; i < num_threads; i++)
    {
        if(LP[i] != NULL && from[i] != NULL)
        {
            bool result = graph->checkReachable(LP[i], from[i]); //This method crashes if NULL pointers are passed to it
            if(result)
            {
                model_print("Thread %d is not sequentially consistent\n", LP[i]->get_tid());
            } else {
                model_print("Thread %d is sequentially consistent\n", LP[i]->get_tid());   
            }
        
        }
    
    }

}



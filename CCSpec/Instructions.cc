//#include "impatomic.h"
//#include "common.h"
#include "Instructions.h"
#include "model.h"
#include "threads-model.h"
#include "execution.h"
#include "nodestack.h"
#include "clockvector.h"
#include "cyclegraph.h"

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

void printInstructions()
{
		
    model_print("Printing Instruction Stack\n");
   
    for(unsigned int i = 0; i < program_stack.size(); i++)
    {
 
        //Node * const node = node_stack->get_node(i);
        //ModelAction * const act = node->get_action();
        ModelAction * act = program_stack[i];
        action_type_t const type = act->get_type();
        
		//if(act->get_tid() != 1)
		if(true)
		{
		    model_print("\nThread %d: ", act->get_tid()); //act->get_seq_number(), 
		    print_action_type(type);
		} 
        if(type == ATOMIC_READ ) //&& act->get_tid() != 1
        {
            model_print("value = %lu ", act->get_reads_from_value()); 
        }
        if(type == ATOMIC_WRITE ) // && act->get_tid() != 1
        {
            model_print("value = %lu ", act->get_value());  
        }
        
        if(type == ATOMIC_RMW ) //&& act->get_tid() != 1
        {
            model_print("read value = %lu, write value = %lu ", act->get_reads_from_value(), act->get_value());  
        }
		
		if(type == LINEARIZATION_POINT)
        {
            model_print("Linearization Point is ");
            print_action_type(act->get_next_op());
            
		} 
        
        if(type == INVOCATION)
        {
            model_print("Begin %s ", act->get_function()->c_str());
            if(act->get_input_output() != (uint64_t) NULL)
                model_print("input %lu ", act->get_input_output());
            //model_print("Begin %s", act->get_function());
            
            
        } else if (type == RESPONSE)
        {
            model_print("End %s output = %lu ", act->get_function()->c_str(), act->get_input_output());
            //model_print("End %s", act->get_function());
	
        }
        
        if(type == INVARIANT)
		{
			handle_invariant(act->get_function());
		}
		
		if(type == IDENTIFIER)
		{
		    
		} 

		if(type == RESULT)
		{
			
		}
        
    }
    model_print("\n");
    
}

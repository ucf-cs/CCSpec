#include "model.h"
#include "threads-model.h"
#include "mymemory.h"
#include "execution.h"
#include "nodestack.h"

#include "History.h"
#include "linearizable_NEW.h"

#include <fcntl.h>

//std::stringstream History::ss;

History::History()
{
    p = 0;
    length = 0;
    records = NULL;
}

History::History(ModelChecker *model_arg)
{
    condition = NULL;
    p = model->get_num_threads_public();
    length = program_stack.size();
    
    records = (method_record_t **) model_malloc(length*sizeof(method_record_t *));
 
    int method_counter = -1;
    
    for(unsigned int i = 0; i < length; i++)
    {
        ModelAction * act = program_stack[i];
        
        s.push_back(act);

        records[i] = (method_record_t *) model_malloc(p*sizeof(method_record_t));
        
        //set the correctness condition
        if(act->get_type() == CORRECTNESS_CONDITION)
        {
            condition = act->get_function();      
        }   
        //handle current thread
		if(act->get_type() == INVOCATION)
		{
		    records[i][act->get_tid()].status = ACTIVE;
		    records[i][act->get_tid()].method_number = ++method_counter;
			records[i][act->get_tid()].method_name = act->get_function();
			records[i][act->get_tid()].input = act->get_input_output();
			records[i][act->get_tid()].input2 = act->get_input_output2();
			records[i][act->get_tid()].output = (uint64_t) NULL;
		} else if (act->get_type() == RESPONSE)
		{
		    records[i][act->get_tid()].status = INACTIVE;
			records[i][act->get_tid()].method_number = records[i-1][act->get_tid()].method_number;
	        records[i][act->get_tid()].method_name = records[i-1][act->get_tid()].method_name; 	
	        records[i][act->get_tid()].input = records[i-1][act->get_tid()].input; 
			records[i][act->get_tid()].input2 = records[i-1][act->get_tid()].input2; 
			records[i][act->get_tid()].output = act->get_input_output();
			/*
		    records[i][act->get_tid()].method_number = -1;
		    records[i][act->get_tid()].method_name = NULL;	
		    records[i][act->get_tid()].input = (uint64_t) NULL;	
			*/
		} else if (i == 0)
		{
		    records[i][act->get_tid()].status = INACTIVE; 
            records[i][act->get_tid()].method_number = -1;
            records[i][act->get_tid()].method_name = NULL;
            records[i][act->get_tid()].input = (uint64_t) NULL;	
			records[i][act->get_tid()].input2 = (uint64_t) NULL;	
			records[i][act->get_tid()].output = (uint64_t) NULL;			
		} else 
		{
		    records[i][act->get_tid()].status = records[i-1][act->get_tid()].status;
            records[i][act->get_tid()].method_number = records[i-1][act->get_tid()].method_number;
	        records[i][act->get_tid()].method_name = records[i-1][act->get_tid()].method_name; 	
	        records[i][act->get_tid()].input = records[i-1][act->get_tid()].input; 
			records[i][act->get_tid()].input2 = records[i-1][act->get_tid()].input2; 
			records[i][act->get_tid()].output = records[i-1][act->get_tid()].output; 
		}
				
	    //handle the other threads
		for(int j = 0; j < p; j++)
		{
		    if(j != act->get_tid())
		    {
		        if(i == 0)
		        {
		            records[i][j].status = INACTIVE; 
		            records[i][j].method_number = -1;
		            records[i][j].method_name = NULL;	
		            records[i][j].input = (uint64_t) NULL;	
					records[i][j].input2 = (uint64_t) NULL;	
					records[i][j].output = (uint64_t) NULL;	             
		        } else 
		        {
		            records[i][j].status = records[i-1][j].status;
		            records[i][j].method_number = records[i-1][j].method_number;
			        records[i][j].method_name = records[i-1][j].method_name; 
			        records[i][j].input = records[i-1][j].input;
					records[i][j].input2 = records[i-1][j].input2;
					records[i][j].output = records[i-1][j].output;
		        }
		         		    
		    }
		
		}
    }
	
}

History::~History()
{

    if(records != NULL)
    {
        for(unsigned int i = 0; i < length; i++)
        {
            if(records[i] != NULL)
            {
                model_free(records[i]);
            }
        }
        model_free(records);
    }

}


int History::method_id(unsigned int index, int tid)
{
    return records[index][tid].method_number;
}

bool History::is_active(unsigned int index, int tid)
{
    if(records[index][tid].status == ACTIVE)
        return true;
    else 
        return false;
}

bool History::check_correctness()
{
    //model_print("Address = %p\n", this);

    //std::string *objAddress = reinterpret_cast<std::string *>(this);
    
    //History *obj = reinterpret_cast<History *>(objAddress);
    
    //model_print("Address = %p\n", obj);
    
    //const char *objAddress = (const char *) this;
    
	if(condition != NULL)
	{
	  
	    /* model_print("Correctness condition = %s\n", condition->c_str()); */
	    //FILE *pFile = (FILE *) model_malloc(sizeof(FILE));
	    //pFile = fopen ("../FLEXParser/example.txt","w");
        //fprintf(pFile, "%s", condition->c_str());
        //fclose(pFile);
        //echo condition->c_str() > "../FLEXParser/example.txt";
	    //std::string script("./../FLEXParser/script.sh \"");
        char script[CHAR_BUFFER]; 
       
	    //strcpy(script, "../FLEXParser/lcdc/script.sh \"");
	    strcpy(script, "./LCDC/script.sh \"");
        strcat(script, condition->c_str());
        //strcat(script, "\" ");
        //strcat(script, "\" \"");
        //strcat(script, objAddress->c_str());
        //strcat(script, objAddress);
        strcat(script, "\"");
        /* model_print("%s\n", script); */
      
	    system(script);
	
	}
	
	return true;

}
void History::archive_history()
{
    
    //std::ofstream ofs;
    //ofs.open ("historyObj.txt", std::ofstream::out | std::ofstream::app);
	//std::ofstream ofs("historyObj.txt", std::ofstream::out);
	/*
	{
		boost::archive::text_oarchive oa(ofs);
        // write class instance to archive
        oa << (*h);

	}
	
    */
    //ofs.close();

    /*
    {   
        boost::archive::text_oarchive oa{History::ss};
        
        oa << (*h);
    }
    */
    /*
    {
        boost::archive::text_oarchive oa{std::cout};
        int i = 1;
        oa << i;   
    }
    */
    //ModelOFstream ofs("historyObj.txt", std::ofstream::out);
    //h->ofs.open("historyObj.txt", std::ofstream::out | std::ofstream::app);
    int fd = creat("LCDC/historyObj.txt", 0777);
    //fd = open("historyObj.txt", O_APPEND);
    
    dprintf(fd, "%d\n", p);
    dprintf(fd, "%u\n", length);
    
    //model_print("Output:\n");
    for(unsigned int i = 0; i < length; i++)
    {       
        dprintf(fd, "%d ", s[i]->get_type());
        dprintf(fd, "%d ", s[i]->get_mo());
        dprintf(fd, "%d ", s[i]->get_tid());
        dprintf(fd, "%d\t", s[i]->get_seq_number());
     
        for(int j = 0; j < p; j++)
        {
            dprintf(fd, "%d ", records[i][j].status); 
            dprintf(fd, "%d ", records[i][j].method_number); 
         
            if(records[i][j].method_name != NULL)
            {
                dprintf(fd, "%s ", records[i][j].method_name->c_str());
            } else {
                dprintf(fd, "NULL ");
            }
            dprintf(fd, "%lu ", records[i][j].input);
			dprintf(fd, "%lu ", records[i][j].input2);  
			dprintf(fd, "%lu\t ", records[i][j].output); 
        } 
        /*
        if(s[i]->get_type() == RESPONSE) 
        {
            model_print("%d ", records[i][s[i]->get_tid()].output);
        
        }
        */
        dprintf(fd, "\n"); 
       
    }
    //model_print("\n");
     
    close(fd);
    
}

void History::retrieve_history()
{
    /*
	std::ifstream ifs(FILENAME);
    boost::archive::text_iarchive ia(ifs);
    // read class state from archive
    ia >> h;
    */
    /*
    const char buffer[16]; 
    size_t bytes_read; 
      
    int fd = open("LCDC/historyObj.txt", O_WRONLY, 0777);
    
    bytes_read = read (fd, buffer, sizeof (buffer)); 
    model_print("%02x \n", buffer[0]); 
  
    close(fd);
    */
#ifndef __MODEL_H__
        FILE *file = fopen("LCDC/historyObj.txt", "r");
        fscanf(file, "%d", p);
        fscanf(file, "%u", length);
        for(unsigned int i = 0; i < length; i++)
        {
            int type, order, tid, num;
            fscanf(fd, "%d ", &type);
            fscanf(fd, "%d ", &order);
            fscanf(fd, "%d ", &tid);
            fscanf(fd, "%d", &num);
            
            ModelAction act = new ModelAction(type, order, tid, num);
            s.push_back(act);
           
        }
        
        fclose(file);
    
#else
        model_print("Cannot call retrieve_history() from model checker context\n");
#endif
    
}


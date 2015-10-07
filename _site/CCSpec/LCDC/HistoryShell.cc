#include "HistoryShell.h"
#include <fstream>  

#include <fcntl.h>

HistoryShell::HistoryShell()
{
    p = 0;
    length = 0;
    records = NULL;
	num_functions = 0;
	s = NULL;
	//func_graph = NULL;
}



HistoryShell::~HistoryShell()
{

    if(records != NULL)
    {
        for(unsigned int i = 0; i < length; i++)
        {
            if(records[i] != NULL)
            {
                free(records[i]);
            }
        }
        free(records);
    }
    if(s != NULL)
        free(s);
	//if(func_graph != NULL)
		//free(func_graph);
	if(output_array != NULL)
		free(output_array);
}


int HistoryShell::method_id(unsigned int index, int tid)
{
    return records[index][tid].method_number;
}

int HistoryShell::is_active(unsigned int index, int tid)
{
    if(records[index][tid].status == ACTIVE)
        return 1;
    else 
        return 0;
}

char * HistoryShell::method_name(unsigned int index, int tid)
{
	return records[index][tid].method_name;
}

void HistoryShell::happens_before(FILE *pFile, int id1, int id2)
{
	if(id1 == id2)
		return; //can't be related to itself
/*
	if(func_graph == NULL)
	{
		fprintf(pFile, "function graph = NULL\n");
		return;
	} */
	fprintf(pFile, "function graph size = %lu\n", func_graph[id1].size());

	//if(!func_graph[id1].empty())
	//{
		
		for(int i = 0; i < func_graph[id1].size(); i++)
		{
			if(func_graph[id1][i] == id2)
				return; //no duplicates allowed
		}
	//}

	func_graph[id1].push_back(id2);
	
}

void HistoryShell::print_graph(FILE *pFile)
{
	fprintf(pFile, "PRINTING GRAPH\n");
	for(int i = 0; i < num_functions; i++)
	{
		fprintf(pFile, "%d ->", i);
		//fprintf(pFile, "\nFunc Graph Size = %d \n", func_graph[i].size());

		for(int j = 0; j < func_graph[i].size(); j++)
		{
			fprintf(pFile, "%d ->", func_graph[i][j]);
		}
		
		fprintf(pFile, "\n");
	}
}

void HistoryShell::topological_sort(FILE *pFile)
{
	std::list<int> L; //Empty list that contains sorted elements
	std::list<int> S; //Set of all nodes with no incoming edges

	const int _num_functions = num_functions;

	std::vector<int> ts_graph[_num_functions];
	//std::list<int> inverse_graph[_num_functions];
    
	//initialize S
	for(int i = 0; i < num_functions;i++)
	{
		fprintf(pFile, "Adding %d to S\n", i);
		S.push_back(i);
		ts_graph[i].clear();
	}
	
	for(int i = 0; i < num_functions; i++)
	{
		fprintf(pFile, "Func Graph Size = %lu\n", func_graph[i].size());
	}

	//construct ts_graph
	for(int i = 0; i < num_functions; i++)
	{
		for(int j = 0; j < func_graph[i].size(); j++)
		{
			ts_graph[i].push_back(func_graph[i][j]); 
			//inverse_graph[func_graph[i][j]].push_back(i);

			fprintf(pFile, "Removing %d from S\n", func_graph[i][j]);
			S.remove(func_graph[i][j]); //func_graph[i][j] has an incoming edge			
		}
	}
	for (std::list<int>::iterator it=S.begin(); it != S.end(); ++it)
	{
		//bt_topological_sort(pFile, *it, L, S, ts_graph, inverse_graph);	
		bt_topological_sort(pFile, *it, L, S, ts_graph);
	}

	/*
	while(S.size() != 0)
	{
		int n = S.front();
		L.push_back(n);
		S.pop_front();
		for(int j = 0; j < ts_graph[n].size(); j++)
		{
			int m = ts_graph[n].back();
			ts_graph[n].pop_back();
			inverse_graph[m].remove(n);
			if(inverse_graph[m].size() == 0)
				S.push_back(m);
		}
	}
	for (std::list<int>::iterator it=L.begin(); it != L.end(); ++it)
    	fprintf(pFile, "%d ->", *it);
    */
}

//void HistoryShell::bt_topological_sort(FILE *pFile, int n, std::list<int> L, std::list<int> S, std::vector<int> ts_graph[], std::list<int> inverse_graph[])
void HistoryShell::bt_topological_sort(FILE *pFile, int n, std::list<int> L, std::list<int> S, std::vector<int> ts_graph[])
{
    if(S.size() == 0)
    {
        return;  
    }

    std::vector<int> local_ts_graph[num_functions];
    std::list<int> local_inverse_graph[num_functions];

    fprintf(pFile, "Exploring %d\n", n);
    fprintf(pFile, "Local ts graph\n");
    for(int i = 0; i < num_functions; i++)
	{
	    fprintf(pFile, "%d ->", i);
		for(int j = 0; j < ts_graph[i].size(); j++)
		{
			local_ts_graph[i].push_back(ts_graph[i][j]);
			fprintf(pFile, "%d ->", ts_graph[i][j]);
			
			local_inverse_graph[ts_graph[i][j]].push_back(i);
		}
		fprintf(pFile, "\n");
	}
	
	fprintf(pFile, "Local inverse graph\n");
    for(int i = 0; i < num_functions; i++)
	{
	    fprintf(pFile, "%d ->", i);
		for(std::list<int>::iterator it=local_inverse_graph[i].begin(); it != local_inverse_graph[i].end(); ++it)
		{
			fprintf(pFile, "%d ->", *it);
		
		}
		fprintf(pFile, "\n");
	}
    
    L.push_back(n);
	S.remove(n);
	int size = local_ts_graph[n].size();
	for(int j = 0; j < size; j++)
	{
		int m = local_ts_graph[n].back();
		local_ts_graph[n].pop_back();
		local_inverse_graph[m].remove(n);
		if(local_inverse_graph[m].size() == 0)
		{
		    fprintf(pFile, "Adding %d to S\n", m);
			S.push_back(m);
	    } else {
	        fprintf(pFile, "Incoming nodes to %d\n", m);
	        for(std::list<int>::iterator it=local_inverse_graph[m].begin(); it != local_inverse_graph[m].end(); ++it)
	        {
	            fprintf(pFile, "%d ->", *it);       
	        }
	        fprintf(pFile, "\n"); 
	    }
	}
	for (std::list<int>::iterator it=S.begin(); it != S.end(); ++it)
	{
		//bt_topological_sort(pFile, *it, L, S, local_ts_graph, local_inverse_graph);
		bt_topological_sort(pFile, *it, L, S, local_ts_graph);	
	}
	if(S.size() == 0)
    {
        fprintf(pFile, "\n");
        for (std::list<int>::iterator it=L.begin(); it != L.end(); ++it)
        	fprintf(pFile, "%d ->", *it);
        fprintf(pFile, "\n"); 
        legal_seq_histories.push_back(L);
        return;  
    }
	
}

void HistoryShell::get_legal_seq_histories(FILE *pFile)
{
	fprintf(pFile, "Method_map size = %lu\n", method_map.size());
	for ( auto it = method_map.begin(); it != method_map.end(); ++it )
	{
	    fprintf(pFile, "Method %d: %s with input %lu\n", it->first, it->second.method_name, it->second.input);
	} 

	std::list<std::list<int>>::iterator it_i;
	fprintf(pFile, "Legal Sequential Histories:\n");

	FILE *clearFile = fopen("LCDC/SEQ_HISTORY/output.txt", "w");
	fclose(clearFile);
	
	FILE *curr_example = fopen("LCDC/SEQ_HISTORY/curr_example.txt", "w");
	
    
	for (it_i=legal_seq_histories.begin(); it_i != legal_seq_histories.end(); ++it_i)
	{
		char seq_history[CHAR_BUFFER];
    	std::list<int>::iterator it_j;

		std::list<uint64_t> temp;
		
		for (it_j=(*it_i).begin(); it_j != (*it_i).end(); ++it_j)
		{
			
			temp.push_back(output_array[*it_j]);

        	fprintf(pFile, "%d ->", *it_j);
			std::unordered_map<int,method_descr_t>::const_iterator got = method_map.find (*it_j);
			strcat(seq_history, got->second.method_name);
			if(got->second.input == (uint64_t) NULL)
				strcat(seq_history, "(); "); 
			else if(got->second.input2 == (uint64_t) NULL)
			{
				char input_str[CHAR_BUFFER];
				sprintf(input_str, "%lu", got->second.input);

				strcat(seq_history, "(");
				strcat(seq_history, input_str);
				strcat(seq_history, "); "); 

				strcpy(input_str, ""); 
			} else {
				char input_str[CHAR_BUFFER];
				sprintf(input_str, "%lu, %lu", got->second.input, got->second.input2);

				strcat(seq_history, "(");
				strcat(seq_history, input_str);
				strcat(seq_history, "); "); 

				strcpy(input_str, ""); 
			}
			
		}
		output_matrix.push_back(temp);
		fprintf(pFile, "\n%s\n", seq_history);
		
		fprintf(curr_example, "%s\n", seq_history);

		char script[CHAR_BUFFER]; 
       
	    strcpy(script, "./LCDC/SEQ_HISTORY/script.sh \"");
        strcat(script, seq_history);
    
        strcat(script, "\"");
        fprintf(pFile, "%s\n", script);
      
	    system(script);

		strcpy(seq_history, "");
		strcpy(script, "");
	}
	fclose(curr_example);
}

void HistoryShell::map_legal_seq_histories(FILE *pFile)
{	
	//Verify Output
	
	FILE *outputFile = fopen("LCDC/SEQ_HISTORY/output.txt", "r");
	FILE *vFile = fopen("LCDC/SEQ_HISTORY/verification.txt", "a");
    
    FILE *curr_example = fopen("LCDC/SEQ_HISTORY/curr_example.txt", "a+");
    
    char buffer[CHAR_BUFFER];

    bool flag;

	std::list<std::list<uint64_t>>::iterator it_o = output_matrix.begin();
	
    while(fgets (buffer, CHAR_BUFFER, outputFile) != NULL)
    {
        fprintf(vFile, "Buffer: %s\n", buffer);
        
        //Place sequential history in list
        std::list<uint64_t> seq_history_output;
        
        int nums_now, bytes_now;
        int bytes_consumed = 0, nums_read = 0;
        uint64_t val;
        
        fprintf(curr_example, "Sequential Specification output:\n");
        
        while ( ( nums_now = 
                sscanf( buffer + bytes_consumed, "%lu%n", &val, &bytes_now )
                ) > 0 ) {
            bytes_consumed += bytes_now;
            nums_read += nums_now;
            seq_history_output.push_back(val);
            fprintf(pFile, "%lu ", val);
            fprintf(curr_example, "%lu ", val);
        }
        fprintf(pFile, "\n");
        fprintf(curr_example, "\n");

		output.clear();
		output.assign((*it_o).begin(), (*it_o).end());
		it_o++;
        
        if(seq_history_output.size() != output.size())
        {
            fprintf(curr_example, "seq history output size = %lu \n", seq_history_output.size());
            fprintf(curr_example, "output size = %lu \n", output.size());
            flag = false;
            break;       
        }
        std::list<uint64_t>::iterator it, it_v;
        
        flag = true;
        it_v = seq_history_output.begin();
        fprintf(curr_example, "Program output:\n");
        for (it=output.begin(); it != output.end(); ++it)
        {
            
            fprintf(vFile, "%lu::%lu ", (uint64_t) *it, *it_v);
            
            fprintf(curr_example, "%lu ", (uint64_t) *it);
            
            if((*it) != (*it_v))
            {
                flag = false;               
                //break;
            }
            ++it_v;
        }
        fprintf(vFile, "\n");
        fprintf(curr_example, "\n");
        if(flag == true)
            break;
       
    }
    fclose(outputFile);
    fclose(curr_example);
    if(flag == true)
        fprintf(vFile, "A mapping was found\n");
    else
    {
        fprintf(vFile, "A mapping does not exist\n");
        FILE *outcome = fopen("LCDC/outcome.txt", "w"); 
        fprintf(outcome, "The program does not meet the correctness condition\n");
        fclose(outcome);
        
        
		std::ifstream ifile("LCDC/SEQ_HISTORY/curr_example.txt", std::ios::in);
		std::ofstream ofile("LCDC/SEQ_HISTORY/example.txt", std::ios::out | std::ios::app);

		//check to see that it exists:
		if (!ifile.is_open()) {
			//file not found (i.e. it is not opened). Print an error message or do something else.
		}
		else {
			ofile << ifile.rdbuf();
			//then add more lines to the file if need be...
		}

        /*
        FILE *f = fopen("LCDC/SEQ_HISTORY/curr_example.txt", "rb");
        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET);

        char *string = (char *) malloc(fsize + 1);
        fread(string, fsize, 1, f);
        fclose(f);

        string[fsize] = 0;
        
        FILE *example = fopen("LCDC/SEQ_HISTORY/example.txt", "a");
        fprintf(example, "%s\n", string);
        fclose(example);
		*/
        
    }
	fclose(vFile);
	
}

bool HistoryShell::retrieve_history(FILE *pFile)
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
		std::vector<output_record_t> output_list;

        FILE *file = fopen("LCDC/historyObj.txt", "r");

		int max = -1; //Will be set to the max method id
        
        fscanf(file, "%d", &p);
        fscanf(file, "%u", &length);
        
        fprintf(pFile, "P = %d LENGTH = %u\n", p, length);
        
        records = (method_record_t **) malloc(length*sizeof(method_record_t *));
        
        s = (action_t *) malloc(length*sizeof(action_t));
        for(unsigned int i = 0; i < length; i++)
        {
            int type, order, tid, seq_num;
            fscanf(file, "%d ", &type);
            fscanf(file, "%d ", &order);
            fscanf(file, "%d ", &tid);
            fscanf(file, "%d", &seq_num);

            s[i].type = (action_type_t) type;
            s[i].order = (memory_order) order;
            s[i].tid = tid;
            s[i].seq_num = seq_num;
     
            
            records[i] = (method_record_t *) malloc(p*sizeof(method_record_t));
            for(unsigned int j = 0; j < p; j++)
            {
                
                fscanf(file, "%d ", (int *) &records[i][j].status);
                fscanf(file, "%d ", (int *) &records[i][j].method_number);
                char buffer[CHAR_BUFFER];
                fscanf(file, "%s ", buffer); 
                strcpy(records[i][j].method_name, buffer);
                fscanf(file, "%lu ", &records[i][j].input);
				fscanf(file, "%lu ", &records[i][j].input2);
				fscanf(file, "%lu ", &records[i][j].output);

				if(records[i][j].method_number > max)
					max = records[i][j].method_number;
					
				if(records[i][j].method_number >= 0)
				{
			        std::unordered_map<int,method_descr_t>::const_iterator got = method_map.find (records[i][j].method_number);

                    if ( got == method_map.end() )
                    {
                        
                        method_descr_t desc;
                        strcpy(desc.method_name, records[i][j].method_name);
                        desc.input = records[i][j].input;
						desc.input2 = records[i][j].input2;
                        std::pair<int,method_descr_t> pair (records[i][j].method_number,desc);
                        method_map.insert(pair);
                    
                    }
                }
	    
            }
            
            if(s[i].type == RESPONSE) //&& records[i][s[i].tid].output != (uint64_t) NULL
            {
                //output.push_back((uint64_t) records[i][s[i].tid].output);
                fprintf(pFile, "Pushing %lu into output list\n", records[i][s[i].tid].output);

				output_record_t output_rec;
				output_rec.method_number = records[i][s[i].tid].method_number;
				output_rec.output = records[i][s[i].tid].output;
				
				output_list.push_back(output_rec);
            
            }
            
        }
        
        fclose(file);
        
		num_functions = max + 1; //id starts at 0, so add 1 for total
		fprintf(pFile, "number of functions = %d\n", num_functions);
		//func_graph = (std::vector<int> *) malloc(num_functions * sizeof(std::vector<int>));
		
		output_array = (uint64_t *) malloc (num_functions*sizeof(uint64_t));		

		for(int i = 0; i < num_functions; i++)
		{
		    std::vector<int> v;
		    func_graph.push_back(v);
			//func_graph[i].clear();
			
			output_array[output_list[i].method_number] = output_list[i].output;

		}
		
		
		/*
        FILE *tfile = fopen("LCDC/test1.txt", "a");
        fprintf(tfile, "History Shell Output:\n");
     
        std::list<uint64_t>::iterator it;
        
        for (it=output.begin(); it != output.end(); ++it)
        {
            
            fprintf(tfile, "%lu ", *it);
            
        }
        
        fprintf(tfile, "\n");
        fclose(tfile);
        */
        return true;
#else
        model_print("Cannot call retrieve_history() from model checker context\n");
        return false;
#endif
    
}


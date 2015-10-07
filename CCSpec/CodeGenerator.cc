#include "model.h"
#include "LexicalAnalyzer.h"
#include "Parser.h"
#include "CodeGenerator.h"

Code_t code[MAX_CODE_LENGTH];

int cx = 0;
int M = 3;
int L = 0;
int proc_status = 0; //used for Procedures
int proc = 0; //used for Procedures
int jGlobal, cxGlobal; //used for recursive programs

//TODO Revise to be more similiar to VM.cc
void reset()
{
	cx = 0;
	M = 3;
	L = 0;
	proc_status = 0; //used for Procedures
	proc = 0; //used for Procedures
}

void generate_code()
{

	program(0);
  
  	model_print("\nGenerated Code:");

	for(int i = 0; i < cx; i++) {
		if(code[i].op == LIT)
			model_print("\nLIT %d %d", code[i].l, code[i].m);
		else if(code[i].op == OPR)
			model_print("\nOPR %d %d", code[i].l, code[i].m); 
		else if(code[i].op == LOD)
			model_print("\nLOD %d %d", code[i].l, code[i].m); 
		else if(code[i].op == STO)
			model_print("\nSTO %d %d", code[i].l, code[i].m); 
		else if(code[i].op == CAL)
			model_print("\nCAL %d %d", code[i].l, code[i].m); 
		else if(code[i].op == INC)
			model_print("\nINC %d %d", code[i].l, code[i].m); 
		else if(code[i].op == JMP)
			model_print("\nJMP %d %d", code[i].l, code[i].m); 
		else if(code[i].op == JPC)
			model_print("\nJPC %d %d", code[i].l, code[i].m); 
		else if(code[i].op ==  SIO)
			model_print("\nSIO %d %d", code[i].l, code[i].m); 
		if(strlen(code[i].name) != 0)
			model_print(" %s", code[i].name);
  	}
	reset();
}

void emit(int op, int l, int m) {
     
     if(cx > MAX_CODE_LENGTH) {
          model_print("\nCode length too long.\n");
     } else {
          code[cx].op = op;
          code[cx].l = l;
          code[cx].m = m; 
          cx++;
     }     
} //end emit function

void emit(int op, int l, int m, char *str) {
     
     if(cx > MAX_CODE_LENGTH) {
          model_print("\nCode length too long.\n");
     } else {
          code[cx].op = op;
          code[cx].l = l;
          code[cx].m = m; 
		  strcpy(code[cx].name, str);
          cx++;
     }     
} //end emit function


int expression(int i) {

     int addop;
     int j;
     
     if(tokenList[i].type == plussym || tokenList[i].type == minussym) {
       
          addop = tokenList[i].type;
          i++;
          i = term(i);
       
          if(addop == minussym) {
               emit(OPR, 0, NEG);
          }
     } else  {
     
          i = term(i);
     }
     j = i;
     while (tokenList[i].type == plussym || tokenList[i].type == minussym) {
      
          addop = tokenList[i].type;
          j++;
          j = term(j);
          if(addop == plussym) {
             
               emit(OPR, 0, ADD);
              
                        
          } else if(addop == minussym) {
             
               emit(OPR, 0, SUB);   
            
              
          }
          i = j;
     }    
     return i;               
} //end expression function



int term(int i) {
   
     int mulop, j;
     i = factor(i);
     j = i;
     while(tokenList[i].type == multsym || tokenList[i].type == slashsym) {
          mulop = tokenList[i].type;
          j++;
          j = factor(j);  
          if(mulop == multsym) {
        
               emit(OPR, 0, MUL);
             
              
          } else if(mulop == slashsym) {
          
               emit(OPR, 0, DIV);
            
          } 
          i = j;            
     }
     return i;
           
} //end term function


int factor(int i) {
    
    int j;
  
    if(tokenList[i].type == identsym) {
         for(j = 0; j < MAX_COMMANDS; j++) {
              if(symbolTable[j].kind != 0) {
                   if(strcmp(symbolTable[i].name, symbolTable[j].name) == 0 && symbolTable[j].kind != 0) { 
                        break; 
                   }
              }                            
              
              
         }
         if(symbolTable[j].kind == const_t) { //symbol is a constant
              emit(LIT, 0, symbolTable[j].val);                      
         } else if(symbolTable[j].kind == var_t) { //symbol is a variable   
              /*
              //the purpose of the if statement is so that a variable is not loaded in a stack location reserved for a variable
              if(proc_status == 0) { //all variables have not been stored                 
                   incM = M - symbolTable[j].addr; //increment past the stack locations reserved for variables
                   if(incM > 0)
                        emit(INC, L, incM);
                   proc_status = 1;
              }  
              
              */
              emit(LOD, L - symbolTable[j].level, symbolTable[j].addr);
             
         } 
         i++;  
        
    } else if(tokenList[i].type == numbersym) {
         emit(LIT, 0, symbolTable[i].val); 
         i++;
    } else if(tokenList[i].type == lparentsym) {
         i++;
         i = expression(i);
         
         i++;     
    } 
    return i;   
} //end factor function

int condition(int i) {
     
     if(tokenList[i].type == oddsym) {
          emit(OPR, 0, ODD);
          i++;
          i = expression(i);                
     } else {
          i = expression(i);
          if (tokenList[i].type == eqsym) {
               i++;
               i = expression(i);
               emit(OPR, 0, EQL);
                               
          } else if (tokenList[i].type == neqsym) {
               i++;
               i = expression(i);
               emit(OPR, 0, NEQ);
                      
          } else if (tokenList[i].type == lessym) {
               i++;
               i = expression(i);
               emit(OPR, 0, LSS);
                     
          } else if (tokenList[i].type == leqsym) {
               i++;
               i = expression(i);
               emit(OPR, 0, LEQ);
              
          } else if (tokenList[i].type == gtrsym) {
               i++;       
               i = expression(i);
               emit(OPR, 0, GTR);
               
          } else if (tokenList[i].type == geqsym) {
               i++;       
               i = expression(i);
               emit(OPR, 0, GEQ);
              
          } else {
               model_print("\nERROR: Relational operator expected at token[%d] = %d\n", i, tokenList[i].type);   
               exit(1);    
          }   
                   
     }   
     return i;
} //end condition function

int statement(int i) {
    
     int j, k, identToken, ctemp, ctemp2;
     if(tokenList[i].type == identsym) {
              
          for(k = 0; k < MAX_COMMANDS; k++) {
              if(symbolTable[k].kind != 0) {
                   if(strcmp(symbolTable[k].name, symbolTable[i].name) == 0 && symbolTable[k].addr >= 3) { 
                        identToken = k;
                        break; 
                   }
              }                            
                
          }     
                 
          i++;
          if(tokenList[i].type != becomessym) {
               model_print("\nERROR: Identifier must be followed by := at token[%d] = %d\n", i, tokenList[i].type); 
               exit(1);
          }
          i++;
          
          i = expression(i);
          emit(STO, L - symbolTable[identToken].level, symbolTable[identToken].addr, symbolTable[identToken].name); //NEW
          //if(symbolTable[identToken].addr == M) //all variables have been stored
               //proc_status = 1;             
     } else if(tokenList[i].type == callsym) {
          i++;
          if(tokenList[i].type != identsym) {
               model_print("\nERROR: Keyword call must be followed by an identifier at token[%d] = %d\n", i, tokenList[i].type);
               exit(1);
          }
          //new
          for(k = 0; k < MAX_COMMANDS; k++) {
              if(symbolTable[k].kind != 0) {
                   if(strcmp(symbolTable[k].name, symbolTable[i].name) == 0 && symbolTable[k].kind == 3) { 
                        identToken = k;
                        break; 
                   }
              }                             
          }
          emit(CAL, L - symbolTable[identToken].level, symbolTable[identToken].addr); //new
          //model_print("symbolTable[%d].addr = %d\n", identToken, symbolTable[identToken].addr);
          i++;       
     } else if(tokenList[i].type == beginsym) {
          i++;
        
          i = statement(i);
          j = i;
          while(tokenList[i].type == semicolonsym) {
               j++;
             
               j = statement(j);  
               i = j;                 
          } 
          if(tokenList[i].type != endsym) {
               model_print("\nERROR: Keyword 'end' expected at token[%d] = %d\n", i, tokenList[i].type);
               exit(1);
          } else {
               i++;
          
          }    
     } else if(tokenList[i].type == ifsym) {
          i++;
          i = condition(i);
          if(tokenList[i].type != thensym) {
               model_print("\nERROR: Keyword 'then' expected at token[%d] = %d\n", i, tokenList[i].type);
               exit(1);
          } else             
               i++;
          ctemp = cx;
          emit(JPC, 0, 0);
          
          i = statement(i);
          
           
          code[ctemp].m = cx; 
          if(tokenList[i+1].type == elsesym) {
               ctemp2 = cx;
               emit(JMP, 0, 0); 
               code[ctemp].m = cx;
               i++;
               i++;
          
               i = statement(i); 
               code[ctemp2].m = cx;        
          }      
     } else if(tokenList[i].type == whilesym) {
          int cx1 = cx;
          i++;
          i = condition(i);
          int cx2 = cx;
          emit(JPC, 0, 0);
          if(tokenList[i].type != dosym) {
               model_print("\nERROR: Keyword 'do' expected at token[%d] = %d\n", i, tokenList[i].type);
               exit(1);
          } else 
               i++;
          i = statement(i);
          emit(JMP, 0, cx1);   
          code[cx2].m = cx;    
     } else if (tokenList[i].type == insym) {
          i++;
          if(tokenList[i].type != identsym) {
               model_print("\nERROR: Identifier expected at token[%d] = %d\n", i, tokenList[i].type);
               exit(1);
                   
          } 
          for(k = 0; k < MAX_COMMANDS; k++) {
              if(symbolTable[k].kind != 0) {
                   if(strcmp(symbolTable[k].name, symbolTable[i].name) == 0 && symbolTable[k].addr >= 3) { 
                        identToken = k;
                        break; 
                   }
              }                            
                
          }     
          i++;  
          emit(SIO, 0, 2); 
          emit(STO, L - symbolTable[identToken].level, symbolTable[identToken].addr, symbolTable[identToken].name); //NEW
     } else if (tokenList[i].type == outsym) {
          i++;
          i = expression(i);
          emit(SIO, 0, 1); 
            
     } 
     return i;   
    
    
} //end statement function

int block(int i) {
   
     M = 3;
     int j, Mtemp;
     if (tokenList[i].type == constsym) {
          i++;
          j = i;
          do {
               if(tokenList[j].type != identsym) {
                    model_print("\nERROR: Identifier expected at token[%d] = %d\n", j, tokenList[j].type);
                    exit(1);
               }
          
               symbolTable[j].kind = const_t;
               symbolTable[j].val = symbolTable[j+2].val;
               
          
               
               j++;
               if(tokenList[j].type != eqsym) {
                    model_print("\nERROR: Identifier must be followed by = at token[%d] = %d\n", j, tokenList[j].type);
                    exit(1);
               }
               
               j++;
               if(tokenList[j].type != numbersym) {
                    model_print("\nERROR: = must be followed by a number at token[%d] = %d\n", j, tokenList[j].type);
                    exit(1);
               } 
               j++;
               i = j;
               j++;
          } while(tokenList[i].type == commasym);
          if (tokenList[i].type != semicolonsym) {         
               model_print("\nERROR: Semicolon expected at token[%d] = %d\n", i, tokenList[i].type);
               exit(1);
          } 
          i++;            
       } //end if statement checking if token is constsym
       
       if (tokenList[i].type == intsym) {            
            i++;
            j = i;
            do {
                 if(tokenList[j].type != identsym) { 
                      model_print("\nERROR: Identifier expected at token[%d] = %d\n", j, tokenList[j].type);
                      exit(1);
                 }
                 
                 
                 symbolTable[j].kind = var_t; 
                 symbolTable[j].addr = M; 
                 M++;
                
                 
                 symbolTable[j].level = L;
                 j++;
                 i = j;
                 j++;
            } while(tokenList[i].type == commasym);
            if (tokenList[i].type != semicolonsym) {         
                 model_print("\nERROR: Semicolon expected at token[%d] = %d\n", i, tokenList[i].type);
                 exit(1);
            }
            i++;
       } //end if statement checking if token is a variable
       j = i;
       Mtemp = M;
       while(tokenList[i].type == procsym) {
            proc = 1;
            
            int cx2 = cx; //new
            cxGlobal = cx; //new
            emit(JMP, 0, 0); //new
            j++;
            if(tokenList[j].type != identsym) {
                 model_print("\nERROR: Identifier expected at token[%d] = %d\n", j, tokenList[j].type);
                 exit(1);
            }
            int jTemp = j;
            jGlobal = j;
            symbolTable[j].kind = proc_t;  
            symbolTable[j].level = L;
            
            
            j++; 
            if(tokenList[j].type != semicolonsym) {
                 model_print("\nERROR: Semicolon expected at token[%d] = %d\n", j, tokenList[j].type);
                 exit(1);
            }
            j++;
            L++; 
            
            j = block(j); 
            
            code[cx2].m = cx + 1; //new 
            symbolTable[jTemp].addr = code[cx2+1].m; //new 
            //model_print("Code[%d].m = %d\n", cx2+1, code[cx2+1].m);
            
             
            emit(OPR, 0, 0); //new 
            L--;             
            if(tokenList[j].type != semicolonsym) { 
                 model_print("\nERROR: Semicolon expected at token[%d] = %d\n", j, tokenList[j].type); 
                 exit(1);
            }
            j++;
            i = j;   
                            
       }
       if(proc_status == 0 && proc == 1) {
            emit(JMP, 0, cx+1); //new  
            proc_status = 1;                 
       }  
       
       emit(INC, 0, Mtemp);
       symbolTable[jGlobal].addr = code[cxGlobal+1].m; //necessary for recursive program
     
       i = statement(i); 
       
       return i;
} //end block function

int program(int i) {
     i = block(i);
     if(tokenList[i].type != periodsym) {
          model_print("\nERROR: Period expected at token[%d]: %d\n", i, tokenList[i].type);
          exit(1);  
     }
     emit(OPR, 0, 0);
	 return i;
} //end program function

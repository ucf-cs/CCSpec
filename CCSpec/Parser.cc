#include "model.h"
#include "LexicalAnalyzer.h"
#include "Parser.h"

symbol_t symbolTable[MAX_COMMANDS];

bool status;

void parse_data()
{
    model_print("\nSymbol Table List\n");  

    for(unsigned int i = 0; i < MAX_COMMANDS; i++) {
 
        if(tokenList[i].type == 0)
            break;
 
        //token is an identifier 
        if(tokenList[i].type == identsym) {
            
            strcpy(symbolTable[i].name, tokenList[i].lexeme); 
            model_print("%s\n", symbolTable[i].name);           
        }

        //token is a number
        if(tokenList[i].type == numbersym) {
            symbolTable[i].val = atoi(tokenList[i].lexeme);
            model_print("%d\n", symbolTable[i].val);    
        } 
               
    } //end for loop to read in the tokens   
    
    status = true;
    PROGRAM(0);
    
    if(status == true)
       model_print("\nNo errors, program is syntactically correct.\n");
}

int FACTOR(int i) {
    if(tokenList[i].type == identsym)
         i++;
    else if(tokenList[i].type == numbersym)
         i++;
    else if(tokenList[i].type == lparentsym) {
         i++;
         i = EXPRESSION(i);
         if(tokenList[i].type != rparentsym) { 
              model_print("\nERROR: Right parenthesis missing");
              status = 1;
         }
         i++;     
    }
    return i;   
} //end FACTOR function

int TERM(int i) {
    i = FACTOR(i);
    int j = i;
    while(tokenList[i].type == multsym || tokenList[i].type == slashsym) {
         j++;
         j = FACTOR(j); 
         i = j;                
    }  
    return i; 
} //end TERM function

int EXPRESSION(int i) {
    
    if(tokenList[i].type == plussym || tokenList[i].type == minussym)
         i++;
    i = TERM(i);
    int j = i;
    while(tokenList[i].type == plussym || tokenList[i].type == minussym) {
         j++;
         j = TERM(j); 
         i = j;                 
    }
    return i;
}

int CONDITION(int i) {
     if(tokenList[i].type == oddsym) {
          i++;
          i = EXPRESSION(i);               
     } else {
       
          i = EXPRESSION(i);
          if (tokenList[i].type != eqsym && tokenList[i].type != neqsym && tokenList[i].type != lessym && tokenList[i].type != leqsym && tokenList[i].type != gtrsym && tokenList[i].type != geqsym) {   
               model_print("\nERROR: Relational operator expected\n");  
               status = false;
          }
          i++;
          i = EXPRESSION(i);   
          
     }   
     return i;
}



int STATEMENT(int i) {
     int j;
     if(tokenList[i].type == identsym) {
          i++;
          if(tokenList[i].type != becomessym) {
               model_print("\nERROR: Identifier must be followed by :=\n");  
          status = false;    
          }
          i++;
          i = EXPRESSION(i);              
     } else if(tokenList[i].type == callsym) {
          i++;
          if(tokenList[i].type != identsym) {
               model_print("\nERROR: Keyword call must be followed by an identifier\n");
               status = false;    
          }
          i++;       
     } else if(tokenList[i].type == beginsym) {
          i++;
          i = STATEMENT(i);
          j = i;
          while(tokenList[i].type == semicolonsym) {
               j++;
               j = STATEMENT(j); 
               i = j;                  
          } 
          if(tokenList[i].type != endsym) {
               model_print("\nERROR: Keyword 'end' expected\n");
               status = false;    
          }
          i++;     
     } else if(tokenList[i].type == ifsym) {
          do { //NEW
              i++;
              i = CONDITION(i);
          } while (tokenList[i].type == andsym || tokenList[i].type == orsym); //NEW
          if(tokenList[i].type != thensym) { 
               model_print("\nERROR: Keyword 'then' expected\n"); 
               status = false;    
          }             
          i++;
          i = STATEMENT(i);
            
          if(tokenList[i+1].type == elsesym) {
               i++;
               i++;
               i = STATEMENT(i);         
          }     
     } else if(tokenList[i].type == whilesym) {
          do { //NEW
              i++;
              i = CONDITION(i);
          } while (tokenList[i].type == andsym || tokenList[i].type == orsym); //NEW
          if(tokenList[i].type != dosym) {
               model_print("\nERROR: Keyword 'do' expected\n"); 
               status = false;    
          }
          i++;
          i = STATEMENT(i);       
     } else if (tokenList[i].type == insym) {
          i++;
          if(tokenList[i].type != identsym) {
               model_print("\nERROR: Identifier expected\n"); 
               status = false;    
          } 
          i++;  
            
     } else if (tokenList[i].type == outsym) {
          i++;
          i = EXPRESSION(i);
           
            
     }
     return i;
}

int BLOCK(int i) {
     int j;
     if (tokenList[i].type == constsym) {
          i++;
          j = i;
          do {
               if(tokenList[j].type != identsym) {
                    model_print("\nERROR: Identifier expected\n");
                    status = false;     
               }
               j++;
               if(tokenList[j].type != eqsym) {
                    model_print("\nERROR: Identifier must be followed by = \n");
                    status = 1;
                }
                j++;
                if(tokenList[j].type != numbersym) {
                     model_print("\nERROR: = must be followed by a number\n");
                     status = false;    
                }
                symbolTable[j].kind = const_t;
                
                j++;
                i = j;
                j++;
          } while(tokenList[i].type == commasym);
          if (tokenList[i].type != semicolonsym) {          
               model_print("\nERROR: Semicolon expected\n");
               status = false;    
          }
          i++;            
     } //end if statement checking if token is constsym
       
     if (tokenList[i].type == intsym) {            
          i++;
          j = i;
          do {
               if(tokenList[j].type != identsym) {
                    model_print("\nERROR: Identifier expected\n");
                    status = false;    
               }
               symbolTable[j].kind = var_t;   
               j++;
               i = j;
               j++;
          } while(tokenList[i].type == commasym);
          if (tokenList[i].type != semicolonsym) {         
               model_print("\nERROR: Semicolon expected\n");
               status = false;    
          }     
          i++;
     } //end if statement checking if token is a variable
     j = i;
     while(tokenList[i].type == procsym) {
          j++;
          if(tokenList[j].type != identsym) {
               model_print("\nERROR: Identifier expected\n");  
               status = false;    
          }
          symbolTable[j].kind = proc_t; 
          j++; 
          if(tokenList[j].type != semicolonsym) {
               model_print("\nERROR: Semicolon expected\n");  
               status = false;    
          } 
          j++;
          j = BLOCK(j);                     
          if(tokenList[j].type != semicolonsym) {
               model_print("\nERROR: Semicolon expected\n"); 
               status = false;    
          }
          j++;
          i = j;                     
     }  
       
     i = STATEMENT(i);  
     return i;
}

int PROGRAM(int i) {
     i = BLOCK(i);
     if(tokenList[i].type != periodsym) {
          model_print("\nERROR: Period expected\n"); 
          status = false;    
     } 
     return i;
}

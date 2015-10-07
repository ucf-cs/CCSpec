#include <ctype.h>
#include "model.h"
#include "LexicalAnalyzer.h"

token_record_t tokenList[MAX_COMMANDS];

void lexical_analysis(std::string *s)
{
	const char* charArray = s->c_str();
	char tempString[MAX_WORD_LENGTH];		
	unsigned int count = 0;
	unsigned int i = 0;
	unsigned int j;	
	unsigned int k;
	
	//TODO Figure out how to handle errors, and make consistent
	while(i < s->size())
	{
		j = i;	
		k = 0;	
		for(int m = 0; m < MAX_WORD_LENGTH; m++)
		    tempString[m] = '\0';
		if(isalpha(charArray[j]))
		{
			while(isalnum(charArray[j]) && k < MAX_WORD_LENGTH) {
				model_print("%c", charArray[j]);
				tempString[k] = charArray[j];
				j++;	
				k++;	
				
			}
			if(k == MAX_WORD_LENGTH) {
				while(isalnum(charArray[j]))
				{
					j++;
					k++;
				}
				if(k > MAX_WORD_LENGTH) {
					model_print("\nERROR:  Identifier length too long.\n");
					break;
				}
			} else {
				tempString[k] = '\0';
			}
			//std::string tempString((*s), i, j-1);

			//check for reserved words		
			if (strcmp(tempString, "call") == 0) {
				tokenList[count].type = callsym;
				strcpy(tokenList[count].lexeme, tempString);
			  	count++;                         
			}
			else if (strcmp(tempString, "begin") == 0) {
			  	tokenList[count].type = beginsym;
				strcpy(tokenList[count].lexeme, tempString);
			  	count++;                              
			}
			else if (strcmp(tempString, "end") == 0) {
			  	tokenList[count].type = endsym;
				strcpy(tokenList[count].lexeme, tempString);
			  	count++;                                    
			}
			else if (strcmp(tempString, "if") == 0) {
			  	tokenList[count].type = ifsym;
				strcpy(tokenList[count].lexeme, tempString);
			  	count++;                                          
			}
			else if (strcmp(tempString, "then") == 0) {
			  	tokenList[count].type = thensym;
				strcpy(tokenList[count].lexeme, tempString);
			  	count++;                                         
			}
			else if (strcmp(tempString, "else") == 0) {
			  	tokenList[count].type = elsesym;
				strcpy(tokenList[count].lexeme, tempString);
			  	count++;                                         
			}
			else if (strcmp(tempString, "while") == 0) {
			  	tokenList[count].type = whilesym;
				strcpy(tokenList[count].lexeme, tempString);
			  	count++;                                      
			}
			else if (strcmp(tempString, "do") == 0) {
			  	tokenList[count].type = dosym;
				strcpy(tokenList[count].lexeme, tempString);
			  	count++;                                        
			}
			else if (strcmp(tempString, "in") == 0 || strcmp(tempString, "read") == 0) {
			  	tokenList[count].type = insym;
				strcpy(tokenList[count].lexeme, tempString);
			  	count++;                                        
			}
			else if (strcmp(tempString, "out") == 0 || strcmp(tempString, "write") == 0 ) {
			  	tokenList[count].type = outsym;
				strcpy(tokenList[count].lexeme, tempString);
			  	count++;                                       
			}
			else if (strcmp(tempString, "const") == 0) {
			  	tokenList[count].type = constsym;
				strcpy(tokenList[count].lexeme, tempString);
			  	count++;                                       
			}
			else if (strcmp(tempString, "int") == 0) {
			  	tokenList[count].type = intsym;
				strcpy(tokenList[count].lexeme, tempString);
			  	count++;                                       
			}
			else if (strcmp(tempString, "procedure") == 0) {
			  	tokenList[count].type = procsym;
				strcpy(tokenList[count].lexeme, tempString);
			  	count++;                                          
			}
			else if (strcmp(tempString, "odd") == 0) {
			  	tokenList[count].type = oddsym;
				strcpy(tokenList[count].lexeme, tempString);
			  	count++;                                         
			} 
			else if (strcmp(tempString, "null") == 0) {
			  	tokenList[count].type = nulsym;
				strcpy(tokenList[count].lexeme, tempString);
			  	count++;                                        
			} 
			else { //tempString is not a reserved word, so it is an identifier
			  	tokenList[count].type = identsym;
				strcpy(tokenList[count].lexeme, tempString);
			  	count++;                                        
			} //end if statement check for reserved words
          
		} //end isalpha check
		else if(isdigit(charArray[j])) {

            while(isdigit(charArray[j]) && k < MAX_DIGIT_LENGTH) {
                model_print("%c", charArray[j]);
				tempString[k] = charArray[j];
				j++;	
				k++;	                        
            }
            
            if(k == MAX_DIGIT_LENGTH) {
				while(isdigit(charArray[j]))
				{
					j++;
					k++;
				}
				if(k > MAX_DIGIT_LENGTH) {
					model_print("\nERROR: Number is too long.\n");
					break;
				}
			}
		    if(isalpha(charArray[j])) { 

                while(isalnum(charArray[j])) 
                    j++;
                    
                model_print("\nERROR: Variable must start with a letter.\n");
                break;
            } else {
			    tempString[k] = '\0';
                tokenList[count].type = numbersym;
				strcpy(tokenList[count].lexeme, tempString);
			  	count++;  
		    }
	
		} //end isdigit check
		else if (ispunct(charArray[j])){
		    
		    while(ispunct(charArray[j]))
		    {
		        model_print("%c", charArray[j]);
		        tempString[k] = charArray[j]; 
		        //some symbols can have spaces between them and still have meaning, such as < = or < =
                //the following if statment will skip over the space as long as the symbol is not a colon 
                //or newline 
                if(j + 1 < s->size())
                {
                    if(strcmp(tempString, ":") != 0 && charArray[j+1] != '\n' && isspace(charArray[j+1]) ) {    
                        j = j + 1;
                        //k++;                                 
                    }    
		        } //end if statments to skip over the space
		        j++;
		        k++;
		        
                if(strcmp(tempString, "+") == 0 || strcmp(tempString, "-") == 0 || strcmp(tempString, "*") == 0)
                    break;
                if(strcmp(tempString, "/") == 0 || strcmp(tempString, "(") == 0 || strcmp(tempString, ")") == 0)
                    break;
                if(strcmp(tempString, ":=") == 0 || strcmp(tempString, ",") == 0 || strcmp(tempString, ";") == 0)
                    break;  
                if(strcmp(tempString, ".") == 0)
                    break;             
		    } //end while loop cycling through symbols 
		    
		    //if an item comes after the \ symbol, then increment j and skip over it
            if(strcmp(tempString, "\\") == 0) {
                j++;                    
            }    
            //check if tempString is a valid symbol 
            else if(strcmp(tempString, "+") == 0) {
                tokenList[count].type = plussym;
				strcpy(tokenList[count].lexeme, tempString);
                count++;                      
            }   
            else if(strcmp(tempString, "-") == 0) {
                tokenList[count].type = minussym;
				strcpy(tokenList[count].lexeme, tempString);
                count++;                      
            }        
            else if(strcmp(tempString, "*") == 0) {
                tokenList[count].type = multsym;
				strcpy(tokenList[count].lexeme, tempString);
                count++;                      
            }      
            else if(strcmp(tempString, "/") == 0) {
                tokenList[count].type = slashsym;
				strcpy(tokenList[count].lexeme, tempString);
                count++;                      
            }   
            else if(strcmp(tempString, "(") == 0) {
                tokenList[count].type = lparentsym;
				strcpy(tokenList[count].lexeme, tempString);
                count++;                      
            }        
            else if(strcmp(tempString, ")") == 0) {
                tokenList[count].type = rparentsym;
				strcpy(tokenList[count].lexeme, tempString);
                count++;                      
            }    
            else if(strcmp(tempString, "=") == 0) {
                tokenList[count].type = eqsym;
				strcpy(tokenList[count].lexeme, tempString);
                count++;                      
            }
            else if(strcmp(tempString, ",") == 0) {
                tokenList[count].type = commasym;
				strcpy(tokenList[count].lexeme, tempString);
                count++;                      
            }    
            else if(strcmp(tempString, ".") == 0) {
                tokenList[count].type = periodsym;
				strcpy(tokenList[count].lexeme, tempString);
                count++;                      
            }   
            else if(strcmp(tempString, "<") == 0) {
                tokenList[count].type = lessym;
				strcpy(tokenList[count].lexeme, tempString);
                count++;                      
            }     
            else if(strcmp(tempString, ">") == 0) {
                tokenList[count].type = gtrsym;
				strcpy(tokenList[count].lexeme, tempString);
                count++;                      
            }   
            else if(strcmp(tempString, ";") == 0) {
                tokenList[count].type = semicolonsym;
				strcpy(tokenList[count].lexeme, tempString);
                count++;                      
            } 
            else if(strcmp(tempString, ":=") == 0) {
                tokenList[count].type = becomessym;
				strcpy(tokenList[count].lexeme, tempString);
                count++;                      
            }    
            else if(strcmp(tempString, "!=") == 0) { //NEW, changed from <>
                tokenList[count].type = neqsym;
				strcpy(tokenList[count].lexeme, tempString);
                count++;                      
            }   
            else if(strcmp(tempString, "<=") == 0) {
                tokenList[count].type = leqsym;
				strcpy(tokenList[count].lexeme, tempString);
                count++;                      
            }  
            else if(strcmp(tempString, ">=") == 0) {
                tokenList[count].type = geqsym;
				strcpy(tokenList[count].lexeme, tempString);
                count++;                      
            } 
            else if(strcmp(tempString, "&&") == 0) { //NEW
                tokenList[count].type = andsym;
				strcpy(tokenList[count].lexeme, tempString);
                count++;                      
            }
            else if(strcmp(tempString, "||") == 0) { //NEW
                tokenList[count].type = orsym;
				strcpy(tokenList[count].lexeme, tempString);
                count++;                      
            } else { 
                model_print("\nERROR: Invalid symbol.\n");  
                model_print("\nZZZ%sZZZ\n", tempString); //TODO Remove after debugging
                break;   
            } 
		    
		} //end ispunct check
		else {
		    model_print("%c", charArray[j]);
			j++;
		}		
		i = j;
		
	} //end while loop iterating through string
	
    model_print("\nLexeme Table:\n");
    model_print("lexeme\t\t\ttoken type\n");
    for(unsigned int m = 0; m < count; m++) {
        model_print("%s\t\t\t", tokenList[m].lexeme);
        model_print("%d\n", tokenList[m].type);    
    }

}

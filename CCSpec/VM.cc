#include "model.h"
#include "LexicalAnalyzer.h"
#include "Parser.h"
#include "CodeGenerator.h"
#include "VM.h"

int stack[MAX_COMMANDS];

instruction_t IR[MAX_CODE_LENGTH]; //IR Register

//Initial values for PM/0 CPU registers
int sp; //stack pointer
int bp; //base pointer
int pc; //program counter
int ir; //instruction register

int temp; //used for printing a | between acivation records
int SIOPrint; //SIOPrint stores the sp to be printed if the SIO instruction is called


void reset_stack()
{
	sp = 0;
	bp = 1;
	pc = 0;
	ir = 0; 
	
	temp = 0;
	SIOPrint = 0;
	//Initialize "stack" store values
	for(int i = 0; i < MAX_COMMANDS; i++)
	{
	    stack[i] = 0;
	}
}

int base (int l, int base) {
    int b1;
    b1 = base;
    while(l > 0) {
    b1 = stack[b1];
    l--;        
    } 
    return b1;
}

void run_VM()
{
    
    reset_stack();

    //TODO Can remove this loop by replace IR with code
    //cycle through the code
    for (int i = 0; i < MAX_CODE_LENGTH; i++) {
        if(code[i].op == 0)
            break;
            
        IR[i].op = code[i].op;
        IR[i].l = code[i].l;
        IR[i].m = code[i].m;

    }
    
    model_print("\t\t\tpc\tbp\tsp\tstack\n");
    model_print("Initial Values\t\t%d\t", pc);   
    model_print("%d\t", bp);
    model_print("%d\t", sp);
    for (int i = 1; i <= 3; i++)
        model_print("%d ", stack[i]);
    model_print("\n");
    
    //cycle through the instructions based on the instruction at the pc value 
    for (int i = 0; i < MAX_CODE_LENGTH; i++) {
    
        model_print("%d ", pc);

        if(IR[pc].op == 1) { 
            model_print("LIT "); 
            model_print("%d ", IR[pc].l);
            model_print("%d\t\t", IR[pc].m);
            sp++;
            stack[sp] = IR[pc].m;  
            pc = pc + 1;             
        }
        else if(IR[pc].op == 2) {
            model_print("OPR "); 
            model_print("%d ", IR[pc].l);
            model_print("%d\t\t", IR[pc].m);
            if(IR[pc].m == 0) { //RET
              sp = bp - 1;
              pc = stack[sp + 3];
              bp = stack[sp + 2];           
            }  
            else if(IR[pc].m == 1) { //NEG
              stack[sp] = -stack[sp]; 
              pc = pc + 1;
            }   
            else if(IR[pc].m == 2) { //ADD
              sp = sp - 1;
              stack[sp] = stack[sp] + stack[sp + 1];
              pc = pc + 1;
            }   
            else if(IR[pc].m == 3) { //SUB
              sp = sp - 1;
              stack[sp] = stack[sp] - stack[sp + 1];
              pc = pc + 1;
            } 
            else if(IR[pc].m == 4) { //MUL
              sp = sp - 1;
              stack[sp] = stack[sp]*stack[sp + 1];
              pc = pc + 1;
            }   
            else if(IR[pc].m == 5) { //DIV
              sp = sp - 1;
              stack[sp] = stack[sp]/stack[sp + 1];   
              pc = pc + 1;
            }     
            else if(IR[pc].m == 6) { //ODD
              stack[sp] = stack[sp]%2;
              pc = pc + 1;

            }   
            else if(IR[pc].m == 7) { //MOD
              sp = sp - 1;
              stack[sp] = stack[sp]%stack[sp + 1];
              pc = pc + 1;
            }   
            else if(IR[pc].m == 8) { //EQL
              sp = sp - 1;
              stack[sp] = stack[sp] == stack[sp + 1];
              pc = pc + 1;
            }   
            else if(IR[pc].m == 9) { //NEQ
              sp = sp - 1;
              stack[sp] = stack[sp] != stack[sp + 1];
              pc = pc + 1;
            }   
            else if(IR[pc].m == 10) { //LSS
              sp = sp - 1;
              stack[sp] = stack[sp] < stack[sp + 1];
              pc = pc + 1;
            }   
            else if(IR[pc].m == 11) { //LEQ
              sp = sp - 1;
              stack[sp] = stack[sp] <= stack[sp +1];  
              pc = pc + 1;
            }   
            else if(IR[pc].m == 12) { //GTR
              sp = sp - 1;
              stack[sp] = stack[sp] > stack[sp + 1];
              pc = pc + 1;
            }   
            else if(IR[pc].m == 13) { //GEQ
              sp = sp - 1;
              stack[sp] = stack[sp] >= stack[sp + 1];
              pc = pc + 1;
            }   
        } //end IR[pc].op == 2
        else if(IR[pc].op == 3) {
            model_print("LOD ");
            model_print("%d ", IR[pc].l);
            model_print("%d\t\t", IR[pc].m);
            sp = sp + 1;
            stack[sp] = stack[base(IR[pc].l, bp) + IR[pc].m];  
            pc = pc + 1;        
        }
        else if(IR[pc].op == 4) {
            model_print("STO ");
            model_print("%d ", IR[pc].l);
            model_print("%d\t\t", IR[pc].m);
            stack[base(IR[pc].l, bp) + IR[pc].m] = stack[sp];
            sp = sp - 1; 
            pc = pc + 1; 
        }
        else if(IR[pc].op == 5) {
            model_print("CAL ");
            model_print("%d ", IR[pc].l);
            model_print("%d\t\t", IR[pc].m);
            stack[sp + 1] = base(IR[pc].l, bp); //static link
            stack[sp + 2] = bp; //dynamic link
            stack[sp + 3] = pc + 1; //return address
            bp = sp + 1;
            pc = IR[pc].m;          
        }
        else if(IR[pc].op == 6) {
            model_print("INC ");
            model_print("%d ", IR[pc].l);
            model_print("%d\t\t", IR[pc].m);
            sp = sp + IR[pc].m;
            pc = pc + 1;   
        }
        else if(IR[pc].op == 7) {
            model_print("JMP ");
            model_print("%d ", IR[pc].l);
            model_print("%d\t\t", IR[pc].m);
            pc = IR[pc].m;    
        }
        else if(IR[pc].op == 8) {
            model_print("JPC ");
            model_print("%d ", IR[pc].l);
            model_print("%d\t\t", IR[pc].m);
            if (stack[sp] == 0) {
              pc = IR[pc].m;
            }
            else
              pc = pc + 1;
            sp = sp - 1;  
        }
        else if(IR[pc].op == 9) {
            if(IR[pc].m == 1) {
               model_print("SIO ");
               model_print("%d ", IR[pc].l);
               model_print("%d\t\t", IR[pc].m);
               SIOPrint = sp; //set SIOPrint to sp
               sp = sp - 1;
               pc = pc + 1;        
            } else if(IR[pc].m == 2) {
               model_print("SIO ");
               model_print("%d ", IR[pc].l);
               model_print("%d\t\t", IR[pc].m);
               printf("Enter an integer: ");
               sp = sp + 1;
               scanf("%d", &stack[sp]);
               pc = pc + 1;    
            }     
        }

        model_print("%d\t", pc);   
        model_print("%d\t", bp);
        model_print("%d\t", sp);

        //print out the initial stack even though the sp value is 0
        if (bp == 1 && sp == 0) {
          for (int j = 1; j <= 3; j++)
              model_print("%d ", stack[j]);
        }

        //print out the stack up to the bp
        for(int j = 1; j < bp; j++) {
           model_print("%d ", stack[j]); 
           temp = bp + 1; //set temp equal to the value of the dynamic link
           while (stack[temp] > j) 
               temp = stack[temp] + 1; //continue to trace through the dynamic links while stack[temp] > k
           
           //if k + 2 is equal to the dynamic link value stored in temp, then a "|" needs to be printed
           //for the new activation record     
           if((j+2) == temp)
               model_print("|");    

        } //end for loop printing the stack up to bp

        //print the stack for the new activation record
        if (bp > 1 && bp > sp) {
          for (int j = bp; j <= (sp + 3); j++)
              model_print("%d ", stack[j]);
        }

        //print the stack from bp to the sp
        if (sp != 0) {
          for(int j = bp; j <= sp; j++) 
              model_print("%d ", stack[j]);     
        }

        //if the SIO instruction is performed, then SIOPrint will equal the value of sp
        if ( SIOPrint > 0) {
          printf("\nOutput: %d\n\n", stack[SIOPrint]);
          SIOPrint = 0; //reset SIOPrint back to 0
        }
        model_print("\n");


        if(bp == 0 && pc == 0 && sp == 0) 
          break; //if bp, pc, and sp all equal 0, end cycling through instructions
      
    } //end for loop cycling through the instructions
}


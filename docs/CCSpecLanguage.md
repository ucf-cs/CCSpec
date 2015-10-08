---
layout: tervel_documentation
---

# CCSpec Interpreter Grammar
The grammar for the CCSpec interpreter is designed to be similar to the C programming language such that the specification of a correctness condition is both concise and intuitive.

{% highlight bash %}
program:     
    function  
  ;
  
function:
function stmt       
  | /* NULL */
  ;
  
stmt:
    ';'                                               
  | expr ';'                                
  | VARIABLE '=' expr ';' 
  | INTEGER HAPPENSBEFORE INTEGER ';'
  | WHILE '(' expr ')' stmt                           
  | IF '(' expr ')' stmt                   
  | IF '(' expr ')' stmt ELSE stmt                    
  | FOR '(' stmt expr ';' stmt_partial ')' stmt       
  | '{' stmt_list '}'                                 
  ;
  
stmt_list:
stmt                  
  | stmt_list stmt       
  ; 
  
stmt_partial:
VARIABLE '=' expr      
  ;
  
expr:
    INTEGER 
  | VARIABLE  
  | HISTORYOBJECT '.' HISTORYFIELD 
  | HISTORYOBJECT '.' HISTORYSTACK '[' VARIABLE ']' '.' ACTIONMETHOD
  | expr OPERATOR expr                                       
  | FORALL VARIABLE ':' expr RANGE expr ',' '(' expr ')'          
  | EXISTS VARIABLE ':' expr RANGE expr ',' '(' expr ')'  
  | METHODNAME '(' expr ',' expr ')' '==' METHODNAME '(' expr ',' expr ')'         
  | '(' expr ')'                                              
  ;
  
INTEGER: 
    0 | [1-9][0-9]*
  ;	
  
OPERATOR:
    [+-*/<>] | ">=" | "<=" | "!=" 
  | "==" | "&&" | "||"
  ;
  
HISTORYOBJECT:
    "h"
  ;	
  
HISTORYFIELD:
    "p" | "length" 
  ;
  
HISTORYSTACK:
    "s"
  ;
  
ACTIONMETHOD:
    "get_type()"
  | "get_mo()"
  | "get_tid()"
  | "get_seq_number()"
  ;
  
HAPPENSBEFORE:
    "happens_before"
  ;
  
METHODNAME:
    "method_name"
  ;
  
VARIABLE:
    [a-zA-Z][a-zA-Z0-9_]*
  ;
{% endhighlight %}
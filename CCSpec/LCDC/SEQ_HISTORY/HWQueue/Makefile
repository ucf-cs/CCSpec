BASE := ../..

#OBJECTS := $(patsubst %.c, %.o, $(wildcard *.c))
#OBJECTS += $(patsubst %.cc, %.o, $(wildcard *.cc))

include $(BASE)/common.mk

#DIR := litmus
#include $(DIR)/Makefile

#DEPS := $(join $(addsuffix ., $(dir $(OBJECTS))), $(addsuffix .d, $(notdir $(OBJECTS))))

CPPFLAGS += -I$(BASE) -I$(BASE)/include
LDFLAGS := -ldl -lrt -rdynamic -pthread
SHARED := -shared

all: lex yacc history_gen
#parser

-include $(DEPS)

lex: 
	flex seqhistory.l

yacc: 
	bison -d seqhistory.y

lex.yy.o: lex yacc 
	$(CC) -c lex.yy.c -o lex.yy.o 
#-I$(BASE) -I$(BASE)/include -L$(BASE) -l$(LIB_NAME)

#malloc.o: ../malloc.c
#	$(CC) -fPIC -c malloc.c -DMSPACES -DONLY_MSPACES -DHAVE_MMAP=0 $(CPPFLAGS) -Wno-unused-variable -L$(BASE) -l$(LIB_NAME)

#%.o: %.c
#	$(CC) -MMD -MF $(@D)/.$(@F).d -o $@ $< $(CPPFLAGS) -L$(BASE) -l$(LIB_NAME)

#%.o: ../%.cc
#	$(CXX) -MMD -MF $(@D)/.$(@F).d -o $@ $< $(CPPFLAGS) -L$(BASE) -l$(LIB_NAME)

#CLP ADDED
#lex.yy.o: seqhistory.h lex.yy.c seqhistory.tab.c seqhistory.tab.h 
#	$(CC) -c lex.yy.c -o lex.yy.o $(CPPFLAGS) -L -l$(LIB_NAME)
#-o ../FLEXParser/seqhistory/lex.yy.o

history_gen: lex.yy.o yacc 
	$(CXX) -Wno-write-strings lex.yy.o seqhistory.tab.c -o history_gen
	
#parser: lex.yy.o yacc $(OBJECTS)
#	$(CXX) -Wno-write-strings lex.yy.o  $(OBJECTS) seqhistory.tab.c -o parser $(LDFLAGS) -L$(BASE) -l$(LIB_NAME)
#-I$(BASE) -I$(BASE)/include -L$(BASE) -L$(BASE)/include -l$(LIB_NAME)
#$(CPPFLAGS) 

clean::
	rm -f lex.yy.c lex.yy.o seqhistory.tab.c seqhistory.tab.h history_gen
#$(OBJECTS) $(DEPS)

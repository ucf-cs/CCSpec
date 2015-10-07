BASE := ..

#OBJECTS := $(patsubst %.c, %.o, $(wildcard *.c))
#OBJECTS += $(patsubst %.cc, %.o, $(wildcard *.cc))

include $(BASE)/common.mk

#DIR := litmus
#include $(DIR)/Makefile

#DEPS := $(join $(addsuffix ., $(dir $(OBJECTS))), $(addsuffix .d, $(notdir $(OBJECTS))))

CPPFLAGS += -I$(BASE) -I$(BASE)/include
LDFLAGS := -ldl -lrt -rdynamic -pthread
SHARED := -shared

all: lex yacc parser
#parser

-include $(DEPS)

lex: 
	flex lcdc.l

yacc: 
	bison -d lcdc.y

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
#lex.yy.o: lcdc.h lex.yy.c lcdc.tab.c lcdc.tab.h 
#	$(CC) -c lex.yy.c -o lex.yy.o $(CPPFLAGS) -L -l$(LIB_NAME)
#-o ../FLEXParser/lcdc/lex.yy.o

HistoryShell.o: HistoryShell.cc
	$(CXX) -c HistoryShell.cc -o HistoryShell.o

parser: lex.yy.o yacc HistoryShell.o
	$(CXX) -Wno-write-strings lex.yy.o HistoryShell.o lcdc.tab.c -o parser 
	
#parser: lex.yy.o yacc $(OBJECTS)
#	$(CXX) -Wno-write-strings lex.yy.o  $(OBJECTS) lcdc.tab.c -o parser $(LDFLAGS) -L$(BASE) -l$(LIB_NAME)
#-I$(BASE) -I$(BASE)/include -L$(BASE) -L$(BASE)/include -l$(LIB_NAME)
#$(CPPFLAGS) 

clean::
	rm -f lex.yy.c lex.yy.o lcdc.tab.c lcdc.tab.h parser HistoryShell.o
#$(OBJECTS) $(DEPS)

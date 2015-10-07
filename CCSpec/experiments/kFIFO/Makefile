include ../benchmarks.mk

TESTNAME = main

HEADERS = boundedsize_kfifo.h
OBJECTS = main.o

#LDFLAGS += -lpthread

all: $(TESTNAME)

$(TESTNAME): $(HEADERS) $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(CFLAGS) $(LDFLAGS)
#	$(CC) -o $@ $(OBJECTS) $(CFLAGS) $(LDFLAGS)

%.o: %.cc
	$(CXX) -c -o $@ $< $(CFLAGS) $(INC)
#	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(TESTNAME) *.o

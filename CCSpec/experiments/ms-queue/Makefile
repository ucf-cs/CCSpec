include ../benchmarks.mk

TESTNAME = main

HEADERS = my_queue.h
OBJECTS = main.o my_queue.o

all: $(TESTNAME)

$(TESTNAME): $(HEADERS) $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(CFLAGS) $(LDFLAGS)
#	$(CC) -o $@ $(OBJECTS) $(CFLAGS) $(LDFLAGS)

%.o: %.c
	$(CXX) -c -o $@ $< $(CFLAGS)
#	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(TESTNAME) *.o

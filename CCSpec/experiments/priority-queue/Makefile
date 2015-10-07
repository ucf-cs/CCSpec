include ../benchmarks.mk

TESTNAME = main

HEADERS = priorityqueue/queueadaptor.h priorityqueue/mdlist/allocator.h priorityqueue/mdlist/mdlist.h common/assert.h common/threadbarrier.h common/timehelper.h
OBJECTS = main.o priorityqueue/mdlist/allocator.o priorityqueue/mdlist/mdlist.o common/assert.o common/timehelper.o


all: $(TESTNAME)

$(TESTNAME): $(HEADERS) $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(CFLAGS) $(LDFLAGS)
#	$(CC) -o $@ $(OBJECTS) $(CFLAGS) $(LDFLAGS)

main.o: main.cc 
	$(CXX) -c -o $@ $< $(CFLAGS) $(INC)
#	$(CC) -c -o $@ $< $(CFLAGS)

priorityqueue/mdlist/allocator.o: priorityqueue/mdlist/allocator.cc 
	$(CXX) -c -o $@ $< $(CFLAGS) $(INC)

priorityqueue/mdlist/mdlist.o: priorityqueue/mdlist/mdlist.cc 
	$(CXX) -c -o $@ $< $(CFLAGS) $(INC)

common/assert.o: common/assert.cc
	$(CXX) -c -o $@ $< $(CFLAGS) $(INC)

common/timehelper.o: common/timehelper.cc
	$(CXX) -c -o $@ $< $(CFLAGS) $(INC)
	
clean:
	rm -f $(TESTNAME) *.o priorityqueue/mdlist/allocator.o priorityqueue/mdlist/mdlist.o common/assert.o common/timehelper.o

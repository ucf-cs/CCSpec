include ../benchmarks.mk

TESTS := table 

all: $(TESTS)

table: main.cc
	$(CXX) -o $@ $^ $(SPEC_OBJ) $(CXXFLAGS) -std=c++0x $(LDFLAGS)

clean:
	rm -f *.o *.d $(TESTS)

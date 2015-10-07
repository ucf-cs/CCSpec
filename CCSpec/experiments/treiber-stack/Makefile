include ../benchmarks.mk

main: my_stack.o main.c
	$(CXX) -o $@ $^ $(CFLAGS) $(LDFLAGS)
#   $(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

%.o: %.c
	$(CXX) -c -o $@ $^ $(CFLAGS)
#	$(CC) -c -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o

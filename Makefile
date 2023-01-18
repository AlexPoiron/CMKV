CC = g++

CFLAGS = -g -DNDEBUG -O5 -std=c++17 -lpthread -Wl,-no-as-needed

all: a.out bench

bench: bench.o tetravex.o solver.o
	$(CC) $(CFLAGS) -o bench bench.o tetravex.o solver.o

a.out: main.o tetravex.o solver.o
	$(CC) $(CFLAGS) -o a.out main.o tetravex.o solver.o
  
main.o: main.cc 
	$(CC) $(CFLAGS) -c main.cc

bench.o : bench.cc
	$(CC) $(CFLAGS) -c bench.cc

tetravex.o: tetravex.cc
	$(CC) $(CFLAGS) -c tetravex.cc

solver.o : solver.cc
	$(CC) $(CFLAGS) -c solver.cc

clean:
	rm -rf *.o  a.out bench
	

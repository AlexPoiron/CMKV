CC = g++

CFLAGS = -g -DNDEBUG -O5 -std=c++17 -lpthread -Wl,-no-as-needed

all: a.out bench

bench: bench.o tetravex.o solver.o
	$(CC) $(CFLAGS) -o bench bench.o tetravex.o solver.o

a.out: main.o tetravex.o solver.o
	$(CC) $(CFLAGS) -o a.out main.o tetravex.o solver.o
  
main.o: main.cpp 
	$(CC) $(CFLAGS) -c main.cpp

bench.o : bench.cpp
	$(CC) $(CFLAGS) -c bench.cpp

tetravex.o: tetravex.cpp
	$(CC) $(CFLAGS) -c tetravex.cpp

solver.o : solver.cpp
	$(CC) $(CFLAGS) -c solver.cpp

clean:
	rm -rf *.o  a.out bench
	

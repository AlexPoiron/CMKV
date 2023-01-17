CC = g++

CFLAGS = -DNDEBUG -O5 -std=c++17 -lpthread -Wl,-no-as-needed

all: a.out

a.out: main.o tetravex.o solver.o
	$(CC) $(CFLAGS) -o a.out main.o tetravex.o solver.o
  
main.o: main.cpp 
	$(CC) $(CFLAGS) -c main.cpp

tetravex.o: tetravex.cpp
	$(CC) $(CFLAGS) -c tetravex.cpp

solver.o : solver.cpp
	$(CC) $(CFLAGS) -c solver.cpp

clean:
	rm *.o  a.out
	

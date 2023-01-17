CC = g++

CFLAGS = -DNDEBUG -O5 -std=c++17 -lpthread -Wl,-no-as-needed

all: a.out

a.out: main.o
	$(CC) $(CFLAGS) -o a.out main.o 
  
main.o: main.cpp 
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm *.o a.out

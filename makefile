CC = gcc
CFLAGS = -g -Wall

# typing 'make' will invoke the first target entry in the file
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#

default: main


# To create the executable file iamroot we need the object files
# main.o:
#

main: main.o deque.o utils.o adjlist.o
	$(CC) $(CFLAGS) -o main main.o deque.o utils.o adjlist.o

main.o: main.c main.h deque.h utils.h adjlist.h
	$(CC) $(CFLAGS) -c main.c

deque.o: deque.c deque.h
	$(CC) $(CFLAGS) -c deque.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

adjlist.o: adjlist.c adjlist.h
	$(CC) $(CFLAGS) -c adjlist.c



# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#

clean:
	$(RM) main *.o *~

#sets the compiler and basic flags
CC = gcc -Wall -g

#defines additional compiler flags 
CFLAGS = -Wall -Wextra -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition \
		 -Wmissing-prototypes -Wdeclaration-after-statement -Wno-return-local-addr -Wunsafe-loop-optimizations \
		 -Wuninitialized -Werror

#set variables to hold name of executables
PROG1 = caesar
PROG2 = xor

#rule to build all the programs
all: $(PROG1) $(PROG2)

#this rule specifies how to link the object file into the executable
$(PROG1): caesar.o
	$(CC) $(CFLAGS) -o $(PROG1) caesar.o

#this rule specifies how to compile the caesar.c file into and object file
caesar.o: caesar.c
	$(CC) $(CFLAGS) -c caesar.c

#rule to build xor
$(PROG2) : xor.o
	$(CC) $(CFLAGS) -o $(PROG2) xor.o

#rule to compile xor.c into an object file
xor.o : xor.c
	$(CC) $(CFLAGS) -c xor.c

#adds -DNOISY_DEBUG to the compile flags for program to define the macro at compile time
#and print out the debug statements while the program is running
debug: CFLAGS += -DNOISY_DEBUG
debug: all

#this fule handles the git commands. If a get repo doesnt exist, it creates one
#it adds all .c, .h, and Makefile changes to the repo and commits with message
#call with 'make git'
git:
	if [ ! -d .git] ; then git init; fi
	git add *.[ch] ?akefile
	git commit -m "lazy auto makefile git commit"

#removes all compiled object files, executables, and editor temp files
#call with 'make clean'
clean cls:
	rm -f *.o $(PROG1) $(PROG2) *~ \#*



CFlags:= -g -O -Wall -DDEBUG
Includes:= 
Libs:= -lpthread -lm -lstdc++
Target=scan

all : $(subst .c,.o,$(wildcard *.c))
	gcc -o $(Target) $^ $(Includes) $(Libs) $(CFlags)

%.o : %.c
	gcc -c $< $(Includes) $(CFlags)

clean :
	rm -f $(Target) *.o

sources = $(wildcard *.cc)
objects = $(addsuffix .o, $(basename $(sources)))
flags = -g -W -Wall -std=c++14 -DDEBUG=1 -DTEST=1
target = bst


$(target) : $(objects)
	g++ -o $(target) $(objects)

%.o : %.cc
	g++ -c $(flags) $< -o $@
clean :
	rm $(target) $(objects)

db: $(target)
	gdb --args ./$(target) -t 10 -s 10

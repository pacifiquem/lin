exec = lin.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g
libs = -lreadline

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec) $(libs)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	cp ./lin.out /usr/local/bin/lin

clean:
	-rm *.out
	-rm src/*.o
	
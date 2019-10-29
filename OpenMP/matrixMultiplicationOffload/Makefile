COMPILER = icc
FLAGS = -no-vec -qopenmp -Wall -Wextra

OBJSUM := $(patsubst %.c,%.o,$(wildcard src/*.c))
OBJSUMF := $(patsubst %.c,%.exec,$(wildcard src/*.c))

%.o: %.c
	$(COMPILER) $(FLAGS) -c -o $@ $<

all: main.o matrix
	@echo "Compiled!"

%.exec: %.o
	$(COMPILER) $(FLAGS) -o $@ $< main.o

matrix: $(OBJSUMF)

clean:
	rm -rf main.o $(OBJSUM) $(OBJSUMF)
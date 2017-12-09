COMPILER = icc
FLAGS = -no-vec -qopenmp -mmic -Wall -Wextra

all: matrixMultiplicationOffload.exec
	@echo "Compiled!"

%.exec: %.o
	$(COMPILER) -o $@ $+ $(FLAGS)

%.o: %.c
	$(COMPILER) -o $@ -c $< $(FLAGS)

clean:
	rm -f *.o *.exec *.optrpt
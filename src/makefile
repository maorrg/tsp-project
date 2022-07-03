all: parallel clean

sequential:
	g++ main.cpp sequential_tsp.cpp -o main -std=c++11
	./main

parallel:
	g++ -fopenmp -lpthread parallel_tsp.cpp -o main -std=c++11
	./main 10

clean:
	rm -f *.bin *.txt *.blif *.out *~

.PHONY: all clean
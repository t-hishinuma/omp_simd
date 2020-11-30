SRC=vecadd
OPT=-g -O3 -fopenmp-simd -fopenmp 
OPT+=-mavx512f -march=native
#-fopt-info-vec-missed

all:
	g++ $(OPT) $(SRC).cpp -o $(SRC).o
	g++ $(OPT) -S $(SRC).cpp -o $(SRC).s

run:
	./$(SRC).o 100000000

clang:
clang++ -g -O3 -fopenmp-simd -fopenmp -mavx512f -march=native vecadd.cpp

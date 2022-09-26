build: main.cpp calc.cpp calc.hpp
	g++ main.cpp calc.cpp -o calc
clean:
	rm calc

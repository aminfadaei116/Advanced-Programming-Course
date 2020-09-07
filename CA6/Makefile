cm = g++ -std=c++11

# run: all
# 	./a.out
	
all: main.cpp tree.o node.o functions.o operand.o operator.o add.o mult.o not.o median.o
	$(cm) main.cpp tree.o node.o functions.o add.o mult.o not.o median.o operand.o operator.o
	rm *.o

tree.o: tree.cpp add.o add.hpp mult.o mult.hpp not.o not.hpp median.o median.hpp functions.o functions.hpp
	$(cm) -c tree.cpp 

node.o: node.cpp
	$(cm) -c node.cpp 

functions.o: functions.cpp
	$(cm) -c functions.cpp 

add.o: add.cpp
	$(cm) -c add.cpp 

mult.o: mult.cpp
	$(cm) -c mult.cpp 

not.o: not.cpp
	$(cm) -c not.cpp 

median.o: median.cpp
	$(cm) -c median.cpp 

operand.o: operand.cpp
	$(cm) -c operand.cpp

operator.o: operator.cpp
	$(cm) -c operator.cpp

.PHONY: clean
clean:
	rm *.o a.out
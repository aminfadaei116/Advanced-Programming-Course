cm = g++ -std=c++11

run: all
	./a.out
	
all: main.cpp utrello_interface.o user.o lists.o task.o functions.o
	$(cm) main.cpp utrello_interface.o user.o lists.o task.o functions.o

utrello_interface.o: utrello_interface.cpp utrello_interface.hpp user.hpp lists.hpp functions.hpp
	$(cm) -c utrello_interface.cpp -o utrello_interface.o

user.o: user.cpp user.hpp functions.o
	$(cm) -c user.cpp -o user.o

lists.o: lists.cpp lists.hpp task.hpp functions.o
	$(cm) -c lists.cpp -o lists.o

task.o: task.cpp task.hpp functions.o
	$(cm) -c task.cpp -o task.o

functions.o: functions.cpp functions.hpp
	$(cm) -c functions.cpp -o functions.o
	
.PHONY: clean
clean:
	rm *.o a.out
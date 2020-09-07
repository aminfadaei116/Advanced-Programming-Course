CC := g++ -std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: test.out

test.out: main.o TankTrouble.o tank.o bullet.o rsdl.o
	$(CC) main.o rsdl.o TankTrouble.o tank.o bullet.o $(CCFLAGS) -o test.out

example.out: example.o rsdl.o
	$(CC) example.o rsdl.o $(CCFLAGS) -o example.out

main.o: src/rsdl.hpp example/TankTrouble.hpp example/main.cpp
	$(CC) -c example/main.cpp -o main.o

TankTrouble.o: src/rsdl.hpp example/TankTrouble.hpp example/tank.hpp example/TankTrouble.cpp
	$(CC) -c example/TankTrouble.cpp -o TankTrouble.o

tank.o: example/tank.hpp example/tank.cpp
	$(CC) -c example/tank.cpp -o tank.o

bullet.o: example/bullet.hpp  example/bullet.cpp example/Entity.hpp
	$(CC) -c example/bullet.cpp -o bullet.o

rsdl.o: src/rsdl.hpp src/rsdl.cpp
	$(CC) -c src/rsdl.cpp -o rsdl.o

.PHONY: clean
clean:
	rm -r *.o
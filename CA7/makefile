cm = g++ -std=c++11


	
all: main.cpp functions.o interface.o user.o manager.o customer.o salesman.o car.o mobile.o tv.o product.o offer.o wallet.o discount.o comment.o cart.o word.o model.o
	$(cm) main.cpp functions.o interface.o market.o user.o manager.o customer.o salesman.o car.o mobile.o tv.o product.o offer.o wallet.o discount.o comment.o cart.o model.o word.o
	rm *.o

interface.o: interface.cpp functions.o functions.hpp market.o market.hpp user.hpp
	$(cm) -c interface.cpp

functions.o: functions.cpp user.hpp 
	$(cm) -c functions.cpp 

market.o: market.cpp functions.o functions.hpp user.hpp
	$(cm) -c market.cpp

user.o: user.cpp functions.o functions.hpp manager.o manager.hpp customer.o customer.hpp salesman.o salesman.hpp offer.o offer.hpp cart.o cart.hpp
	$(cm) -c user.cpp 

manager.o: manager.cpp functions.o functions.hpp
	$(cm) -c manager.cpp

customer.o: customer.cpp functions.o functions.hpp
	$(cm) -c customer.cpp

salesman.o: salesman.cpp functions.o functions.hpp offer.o offer.hpp
	$(cm) -c salesman.cpp

product.o: product.cpp functions.o functions.hpp car.o car.hpp tv.o tv.hpp mobile.o mobile.hpp
	$(cm) -c product.cpp

car.o: car.cpp functions.o functions.hpp
	$(cm) -c car.cpp

tv.o: tv.cpp functions.o functions.hpp
	$(cm) -c tv.cpp

mobile.o: mobile.cpp functions.o functions.hpp
	$(cm) -c mobile.cpp

offer.o: offer.cpp functions.o functions.hpp product.o product.o cart.o cart.hpp
	$(cm) -c offer.cpp

wallet.o: wallet.cpp wallet.hpp
	$(cm) -c wallet.cpp

discount.o: discount.cpp discount.hpp
	$(cm) -c discount.cpp

comment.o: comment.cpp comment.hpp
	$(cm) -c comment.cpp

cart.o: cart.cpp cart.hpp
	$(cm) -c cart.cpp

model.o: model.cpp model.hpp
	$(cm) -c model.cpp

word.o: word.cpp word.hpp
	$(cm) -c word.cpp

.PHONY: clean
clean:
	rm *.o *.gch a.out
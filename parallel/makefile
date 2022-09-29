CC = g++ -std=c++11

all: PhonePricePrediction.out

PhonePricePrediction.out: main.o functions.o
	$(CC) main.o functions.o -o PhonePricePrediction.out -lpthread

main.o: main.cpp header.hpp
	$(CC) -c main.cpp -o main.o -lpthread

functions.o: functions.cpp header.hpp
	$(CC) -c functions.cpp -o functions.o -lpthread

clean:
	rm *.o PhonePricePrediction.out main.o functions.o
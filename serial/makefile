CC = g++ -std=c++11

all: PhonePricePrediction.out

PhonePricePrediction.out: main.o functions.o
	$(CC) main.o functions.o -o PhonePricePrediction.out

main.o: main.cpp header.hpp
	$(CC) -c main.cpp -o main.o

functions.o: functions.cpp header.hpp
	$(CC) -c functions.cpp -o functions.o

clean:
	rm *.o PhonePricePrediction.out main.o functions.o
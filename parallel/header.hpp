#ifndef _HEADER_
#define _HEADER_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <pthread.h>
#include <algorithm> 

#define NUMBER_OF_THREADS 4

struct thread_data
{
    int thread_id;
    std::vector <std::vector <double>> train;
    std::vector <std::vector <double>> weights;
    std::vector <double> max;
    std::vector <double> min;
};

int find_max_score(std::vector <double> input);
int classification(std::vector <std::vector <double>> train, std::vector <std::vector <double>> weights);
std::vector <double> max_and_min(std::vector <std::vector <double>> data, int column);
std::vector <double> split(std::string input, char value);
std::vector <std::vector <double>> read_csv_file(const char *path);
std::vector <std::vector <double>> normalization(std::vector <std::vector <double>> data, std::vector <double> max, std::vector <double> min);
void* phone_price_prediction(void* args);
void* find_max_and_min(void* args);

#endif
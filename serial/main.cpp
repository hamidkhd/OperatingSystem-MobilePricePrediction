#include "header.hpp"

int main(int argc, char const *argv[])
{
    std::string datasets_train = argv[1];
    std::string datasets_weights = argv[1];

    std::vector <std::vector <double>> train = read_csv_file((datasets_train.append("train.csv")).c_str());
    std::vector <std::vector <double>> weights = read_csv_file((datasets_weights.append("weights.csv")).c_str());

    train = normalization(train);

    double accuracy_counter = classification(train, weights);
    double accuracy = (double)(accuracy_counter / train.size()) * 100;

    printf("Accuracy: %.2f%\n", accuracy);  

    return 0;
}
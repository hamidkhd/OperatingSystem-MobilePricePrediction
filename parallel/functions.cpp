#include "header.hpp"

int find_max_score(std::vector <double> input)
{
    int result = 0;
    double max = input[0];

    for (int i = 0; i < input.size(); i++)
    {
        if (max < input[i])
        {
            max = input[i];
            result = i;
        }
    }

    return result;
}

int classification(std::vector <std::vector <double>> train, std::vector <std::vector <double>> weights)
{
    int accuracy_counter = 0;

    for (int i = 0; i < train.size(); i++)
    {
        std::vector <double> results;

        for (int k = 0; k < weights.size(); k++)
        {
            double temp_result = 0;

            for (int j = 0; j < train[i].size() - 1; j++)
            {
                temp_result += (double)(train[i][j] * weights[k][j]);
            }
            temp_result += weights[k][weights[k].size() - 1];
            
            results.push_back(temp_result);
        }
        if (find_max_score(results) == train[i][train[i].size() - 1])
        {
            accuracy_counter++;
        }
    }
    return accuracy_counter;
}

std::vector <double> max_and_min(std::vector <std::vector <double>> data, int column)
{
    std::vector <double> result;

    double max = data[0][column], min = data[0][column];

    for (int i = 1; i < data.size(); i++)
    {
        if (data[i][column] > max)
            max = data[i][column];

        if (data[i][column] < min)
            min = data[i][column];
    }

    result.push_back(min);
    result.push_back(max);

    return result;
}

std::vector <double> split(std::string input, char value)
{
    std::vector <double> result;
    std::string word;
  
    for (auto x : input) 
    {
        if (x == value)
        {
            result.push_back(stof(word));
            word = "";
        }
        else 
            word += x;
    }
    result.push_back(stof(word));

    return result;
}

std::vector <std::vector <double>> read_csv_file(const char *path) 
{
	int i = 0;
	std::ifstream infile(path);
	std::string line;

    std::vector <std::vector <double>> data;

	while (getline(infile, line))
	{
        if (i != 0)
            data.push_back(split(line, ','));
		i++;
	}

	return data;
}

std::vector <std::vector <double>> normalization(std::vector <std::vector <double>> data, std::vector <double> max, std::vector <double> min)
{    
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].size() - 1; j++)
        {
            data[i][j] = (double)(data[i][j] - min[j]) / (max[j] - min[j]);
        }
    }

    return data;
}

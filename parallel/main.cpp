#include "header.hpp"

pthread_t threads[NUMBER_OF_THREADS];
pthread_mutex_t mutex;

struct thread_data thread_data_array[NUMBER_OF_THREADS];
std::vector <std::vector <double>> maxs;
std::vector <std::vector <double>> mins;
int train_size = 0;
double accuracy_counter = 0;
std::string datasets;

int main(int argc, char const *argv[])
{
    datasets = argv[1];

    std::string datasets_temp = datasets;
    
    pthread_mutex_init(&mutex, NULL);

    std::vector <double> max;
    std::vector <double> min;
    std::vector <double> temp;

    int return_status;

    std::vector <std::vector <double>> weights = read_csv_file((datasets_temp.append("weights.csv")).c_str());

    for (int i = 0; i < weights[0].size() - 1; i++)
    {
        maxs.push_back(temp);
        mins.push_back(temp);
    }

    for(long tid = 0; tid < NUMBER_OF_THREADS; tid++)
	{
        thread_data_array[tid].thread_id = tid;
		thread_data_array[tid].weights = weights;

	    return_status = pthread_create(&threads[tid], NULL, find_max_and_min, (void*)tid);
        if (return_status)
		{
            std::cout << "ERROR: return code from pthread_create() is" << return_status << std::endl;
			exit(-1);
		}
	}

    for(long tid = 0; tid < NUMBER_OF_THREADS; tid++)
	{
        void* sub_thread_data_array;
		return_status = pthread_join(threads[tid], &sub_thread_data_array);
		if (return_status)
		{
            std::cout << "ERROR: return code from pthread_create() is" << return_status << std::endl;
			exit(-1);
		}
	}

    for (int i = 0; i < weights[0].size() - 1; i++)
    {
        max.push_back(*max_element(maxs[i].begin(), maxs[i].end()));
        min.push_back(*min_element(mins[i].begin(), mins[i].end()));
    }  

    for(long tid = 0; tid < NUMBER_OF_THREADS; tid++)
	{
		thread_data_array[tid].max = max;
        thread_data_array[tid].min = min;

		return_status = pthread_create(&threads[tid], NULL, phone_price_prediction, (void*)tid);
        if (return_status)
		{
            std::cout << "ERROR: return code from pthread_create() is" << return_status << std::endl;
			exit(-1);
		}
	}

    for(int tid = 0; tid < NUMBER_OF_THREADS; tid++)
	{
        void* sub_accuracy_counter;
		return_status = pthread_join(threads[tid], &sub_accuracy_counter);
		if (return_status)
		{
            std::cout << "ERROR: return code from pthread_create() is" << return_status << std::endl;
			exit(-1);
		}
	}

    pthread_mutex_destroy(&mutex);

    double accuracy = (double)(accuracy_counter / train_size) * 100;

    printf("Accuracy: %.2f%\n", accuracy);  

	pthread_exit(NULL);
}

void* find_max_and_min(void* args)
{
	long offset = (long)args;

    std::string datasets_temp = datasets;
    std::string a = "train_", b = ".csv";

    std::string train_file = datasets_temp.append(a).append(std::to_string(thread_data_array[offset].thread_id)).append(b);

    thread_data_array[offset].train = read_csv_file(train_file.c_str());

    pthread_mutex_lock(&mutex);

    train_size += thread_data_array[offset].train.size();

    for (int i = 0; i < thread_data_array[offset].train[0].size() - 1; i++)
    {
        std::vector <double> temp = max_and_min(thread_data_array[offset].train, i);
        mins[i].push_back(temp[0]);
        maxs[i].push_back(temp[1]);
    }

    pthread_mutex_unlock (&mutex);

    pthread_exit(NULL);
}

void* phone_price_prediction(void* args)
{
	long offset = (long)args;

    thread_data_array[offset].train = normalization(thread_data_array[offset].train, thread_data_array[offset].max, thread_data_array[offset].min);

    pthread_mutex_lock(&mutex);

    accuracy_counter += classification(thread_data_array[offset].train, thread_data_array[offset].weights);

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}
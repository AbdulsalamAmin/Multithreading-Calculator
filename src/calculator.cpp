#include <Calculator.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <numeric>
#include <mutex>
#include <thread>


bool Calculator::GetNumbers()
{
    std::string line;

    std::cout << "enter numbers seperate by space(press enter well down): ";
    std::getline(std::cin,line);

    std::stringstream ss(line);
    int64_t number;

    while(ss >> number){

        numbers.push_back(number);
    }

    return true;
}
bool Calculator::GetNumbers(const std::string &file_name)
{
    std::ifstream file(file_name);
    int64_t number;
    if(file.is_open()){
        while(file >> number){
            numbers.push_back(number);
        }

        file.close();
    }else{
        std::cerr << "unable file open!"
                  << std::endl;
    }

    return true;
}

int64_t Calculator::Calculate()
{
    int num_threads;
    unsigned int max_threads = std::thread::hardware_concurrency();
    std::clog << "number of threads cpu: "
              << max_threads
              << std::endl;

    while(true){
        std::clog << "enter the number of threads (1 to :" << max_threads << ")" << '\n';

        std::cin >> num_threads;
        if(std::cin.fail() || num_threads <= 0 || num_threads > max_threads)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cerr << "invalid input num thread" << '\n';
        }else{

            break;

        }

    }
    std::size_t chunk_size = numbers.size()/num_threads;
    std::vector<int64_t> partial_sums(num_threads);

    std::mutex mtx;
    auto sum_chunk = [this,&partial_sums,&mtx](size_t start, size_t end,int64_t thread_id)
    {
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::clog << "creating thread " << thread_id
                      << " to process range [" << start << ", " << end << ")" << std::endl;
        }
        int64_t local_sum = std::accumulate(numbers.begin() + start, numbers.begin() + end,int64_t(0));

        {
            std::lock_guard<std::mutex>lock(mtx);
            std::clog << "thread starting processing range [" << start << ", " << end << ")" << std::endl;

            partial_sums[thread_id] = local_sum;



            std::clog << "thread finished processing range [" << start << ", " << end << ")"
                      << " - partial sum: " << partial_sums[thread_id] << std::endl;
            std::clog << "-------------------------------------------" << std::endl;
        }

    };

    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i){

        size_t start = i * chunk_size;
        size_t end = (i == num_threads - 1) ? numbers.size() : start + chunk_size;


        threads.emplace_back(sum_chunk, start, end,i);
    }

    for (auto& t : threads){
        t.join();
    }

    int64_t total_sum = std::accumulate(partial_sums.begin(), partial_sums.end(), int64_t(0));



    return total_sum;
}



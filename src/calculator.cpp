#include <calculator.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <numeric>
#include <thread>


std::vector<int> Calculator::GetNumbersFromConsole()
{
    std::vector<int> numbers;
    std::string line;

    std::cout << "Enter numbers seperate by space(press enter well down): ";
    std::getline(std::cin,line);

    std::stringstream ss(line);
    int64_t number;

    while(ss >> number){

        numbers.push_back(number);
    }

    return numbers;
}
std::vector<int> Calculator::GetNumbersFromFile(const std::string& filename)
{
    std::vector<int> numbers;
    std::ifstream file(filename);
    int number;
    if(file.is_open()){
        while(file >> number){
            numbers.push_back(number);
        }

        file.close();
    }else{
        std::cout << "Unable file open!"
                  << std::endl;
    }

    return numbers;
}

int Calculator::calculate(const std::vector<int>& numbers)
{
    int num_threads;

    std::cout << "Number of threads cpu "
              << std::thread::hardware_concurrency()
              << std::endl;
    std::cout << "Enter the number of threads: ";
    std::cin >> num_threads;

    std::size_t chunk_size = numbers.size()/num_threads;
    std::vector<int> partial_sums(num_threads,0);

    auto sum_chunk = [&numbers](size_t start, size_t end, int& result)
    {
        result = std::accumulate(numbers.begin() + start, numbers.begin() + end, 0);
    };

    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i){
        size_t start = i * chunk_size;
        size_t end = (i == num_threads - 1) ? numbers.size() : start + chunk_size;

        threads.emplace_back(sum_chunk, start, end, std::ref(partial_sums[i]));
    }

    for (auto& t : threads){
        t.join();
    }

    int total_sum = std::accumulate(partial_sums.begin(), partial_sums.end(), 0);

    return total_sum;
}


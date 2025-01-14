#include <calculator.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>



int main()
{
    Calculator cal;
    int Choice;

    std::cout << "Choose input method:\n1. From Console\n2. From File\n";
    std::cin >> Choice;
    std::cin.ignore();

    std::vector<int> numbers;

    if(Choice == 1){
        numbers = cal.GetNumbersFromConsole();
    }else if(Choice == 2){
        std::string  FileName;
        std::cout << "Enter filename and dir: ";
        std::getline(std::cin,FileName);
        numbers = cal.GetNumbersFromFile(FileName);
    }else{
        std::cout << "Invalid choice.\n";

        return 1;
    }

    int sum;

    sum = cal.calculate(numbers);
    std::cout << "the sum of the numbers is:"
              << sum
              << std::endl;

    return 0;

}

#include <Calculator.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>



int main()
{
    Calculator cal;
    char again;
    do{
        int choice;
        bool valid_input = false;

        while(!valid_input){


            std::cout << "choose input method:\n1. from console\n2. from file\n";

            std::cin >> choice;
            std::cin.ignore(),'\n';

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cerr << "Invalid input. Please enter 1 or 2.\n";

                continue;

            }
            valid_input = true;

            std::vector<int64_t> numbers;

            if(choice == 1){
                cal.GetNumbers();

            }else if(choice == 2){
                std::string  file_name;

                std::cout << "enter file_name and directory: ";
                std::getline(std::cin,file_name);

                cal.GetNumbers(file_name);
            }else{
                std::cerr << "Invalid choice.\n";

                continue;
            }

            int64_t sum;

            sum = cal.Calculate();
            std::cout << "the sum of the numbers is:"
                      << sum
                      << std::endl;

            cal = Calculator();

            std::cout << "do you want to continue? (y/n): ";
            std::cin >> again;


        }
    }while(std::tolower(again) == 'y');

    std::cout<<"goodby👋\n";

    return 0;
}

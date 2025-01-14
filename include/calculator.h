#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <vector>
#include <string>

class Calculator
{
public:
    std::vector<int> GetNumbersFromConsole();
    std::vector<int> GetNumbersFromFile(const std::string& filename);
    int calculate(const std::vector<int>& numbers);
};
#endif // CALCULATOR_H

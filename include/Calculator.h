#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <vector>
#include <string>

class Calculator
{
private:
    std::vector<int64_t> numbers;
public:
    bool GetNumbers();
    bool GetNumbers(const std::string &file_name);
    int64_t Calculate();
};
#endif // CALCULATOR_H

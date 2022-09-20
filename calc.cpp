#include "calc.hpp"

Calculator::Calculator()
{
}

Calculator::~Calculator()
{

}

bool Calculator::isValidExp(){
    for (auto i : Calculator::internalParseBuffer)
    {
        if ((i >= ' ' && i <= '\'')
        || (i == '.')
        || (i == ',')
        || (i >= ':'))
        {
            std::cout << "Weird characters not allowed in expression!" << std::endl;
            return 0;
        }
    }
    return 1;
}

void Calculator::getInput()
{
    do 
    {
        if (Calculator::internalParseBuffer.empty() == true)
        {
            std::getline(std::cin, Calculator::internalParseBuffer);
        }
        else
        {
            Calculator::internalParseBuffer.clear();
            std::getline(std::cin, Calculator::internalParseBuffer);
        }
    } while (!this->isValidExp());
}

void Calculator::parse(){
}
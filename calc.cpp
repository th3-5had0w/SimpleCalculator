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
            std::getline(std::cin, this->internalParseBuffer);
        }
    } while (!this->isValidExp());
    this->parse();
}

void Calculator::parseBrackets()
{
    long long open_bracket_pos;
    long long close_bracket_pos;
    while (1)
    {
        close_bracket_pos = this->internalParseBuffer.find_first_of(")");
        open_bracket_pos = this->internalParseBuffer.find_last_of("(");
        if (open_bracket_pos != -1 && close_bracket_pos != -1){
            std::cout << this->internalParseBuffer.substr(0, open_bracket_pos) << std::endl;
            std::cout << this->internalParseBuffer.substr(close_bracket_pos+1, this->internalParseBuffer.length()) << std::endl;
        }
        break;
    }
}

void Calculator::parse(){
    this->parseBrackets();
}
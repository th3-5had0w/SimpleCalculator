#include <iostream>
#include <string>
#include <vector>
#include <exception>

#define MAX_CALC_LEN 4096

class Calculator
{
    private:
        std::string internalParseBuffer;
        void parse();
        bool isValidExp();
        void parseBrackets();
        bool parseArith(std::string buffer);
    public:
        Calculator();
        void getInput();
        ~Calculator();
        void getData();
};
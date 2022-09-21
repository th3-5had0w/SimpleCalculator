#include <iostream>
#include <string>

#define MAX_CALC_LEN 4096

class Calculator
{
    private:
        std::string internalParseBuffer;
        void parse();
        bool isValidExp();
        void parseBrackets();
    public:
        Calculator();
        void getInput();
        ~Calculator();
        void getData();
};
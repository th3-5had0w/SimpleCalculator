#include <iostream>
#include <string>

#define MAX_CALC_LEN 4096

class Calculator
{
    private:
        std::string internalParseBuffer;
        void parse();
        bool isValidExp();
    public:
        Calculator();
        void getInput();
        ~Calculator();
        void getData();
};
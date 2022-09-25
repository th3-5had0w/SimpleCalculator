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
        bool internalParse(std::vector<unsigned long long> &Arr);
    public:
        Calculator();
        void getInput();
        ~Calculator();
        void getData();
};
#include <iostream>
#include <string>
#include <vector>
#include <exception>

#define MAX_CALC_LEN 4096

class Calculator
{
    private:
        std::string internalParseBuffer;
        void parseExpression();
        bool isValidExp();
        bool parseBrackets(std::string buffer);
        bool parseArith(std::string buffer, unsigned long long &resNum);
        unsigned long long internalParse(std::vector<unsigned long long> &Arr);
    public:
        Calculator();
        void getInput();
        ~Calculator();
};
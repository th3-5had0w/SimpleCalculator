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
        if ((i <= '\'')
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

bool Calculator::parseArith(std::string buffer)
{
    std::vector<unsigned long long> parsedArr;
    std::vector<unsigned long long> operatorPos;
    unsigned long long i = 0;
    unsigned long long tmpFirstPos;
    unsigned long long tmpNum;
    unsigned char tmpLast = buffer[buffer.length()-1];
    if (tmpLast == '*' ||
    tmpLast == '+' ||
    tmpLast == '-' ||
    tmpLast == '/')
    {
        goto ERROR_MATH_SIGN_PLACEMENT;
    }

    while (i < buffer.length())
    {
        tmpFirstPos = i;
        while (buffer[i] != '*' && 
        buffer[i] != '+' && 
        buffer[i] != '-' && 
        buffer[i] != '/' &&
        i < buffer.length()) ++i;
        if (i != 0)
        {
            try{
                tmpNum = std::stoull(buffer.substr(tmpFirstPos, i-tmpFirstPos));
            }
            catch (std::exception &e)
            {
                if (tmpFirstPos != i)
                {
                    std::cout << "[" << e.what() << "] Cannot parse " << buffer.substr(tmpFirstPos, i-tmpFirstPos) << std::endl;
                    return 0;
                }
                else goto ERROR_MATH_SIGN_PLACEMENT;
            }
            parsedArr.push_back(tmpNum);
        }
        else
        {
            parsedArr.push_back(0);
        }

        if (i < buffer.length()) parsedArr.push_back(buffer[i]);

        ++i;
    }
    
    for (int x = 0; x < parsedArr.size(); ++x)
    {
        if (parsedArr[x] == '*')
        {
            operatorPos.push_back(x);
        }
    }

    int tmpPos;
    while (operatorPos.size() > 0)
    {
        tmpPos = operatorPos[operatorPos.size()-1];
        std::cout << "taking " << parsedArr[tmpPos-1] << " and " << parsedArr[tmpPos+1] << std::endl;
        parsedArr.insert(parsedArr.begin()+tmpPos-1, parsedArr[tmpPos-1] * parsedArr[tmpPos+1]);
        parsedArr.erase(parsedArr.begin()+tmpPos,parsedArr.begin()+tmpPos+3);
        operatorPos.pop_back();
    }

    for (auto x : parsedArr)
    {
        std::cout << x << std::endl;
    }
    return 1;
    ERROR_MATH_SIGN_PLACEMENT:
    std::cout << "Error math operator sign placement" << std::endl;
    return 0;
}

void Calculator::parse(){
    parseArith(this->internalParseBuffer);
    //this->parseBrackets();
}
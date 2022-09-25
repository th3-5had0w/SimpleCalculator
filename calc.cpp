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

bool Calculator::internalParse(std::vector<unsigned long long> &Arr)
{
    unsigned long long x = 1, tmpNum, firstPos;
    std::vector<std::pair<unsigned long long, unsigned long long>> rangeList;
    std::pair<unsigned long long, unsigned long long> tmpRange;
    std::vector<unsigned long long> resList;
    while (x < Arr.size())
    {
        tmpNum = 0;
        if (Arr[x] == '*' || Arr[x] == '/'){
            firstPos = x - 1;
            tmpNum += Arr[x-1];
            if (Arr[x] == '*')
            {
                tmpNum *= Arr[x+1];
            }
            else if (Arr[x] == '/')
            {
                tmpNum /= Arr[x+1];
            }
            x+=2;
            while ((Arr[x] == '*' || Arr[x] == '/') &&
            x < Arr.size())
            {
                if (Arr[x] == '*')
                {
                    tmpNum *= Arr[x+1];
                }
                else if (Arr[x] == '/')
                {
                    tmpNum /= Arr[x+1];
                }
                x+=2;
            }
            // == debug perpose
            for (int ok = firstPos; ok < x; ++ok)
            {
                std::cout << Arr[ok] << " ";
            }
            std::cout << std::endl;
            // ==
            rangeList.push_back({firstPos, x});
        }
        x+=2;
        resList.push_back(tmpNum);
        std::cout << tmpNum << std::endl;
    }

    while (rangeList.size() > 0)
    {
        tmpRange = rangeList.back();
        Arr.insert(Arr.begin()+tmpRange.first, resList.back());
        Arr.erase(Arr.begin()+tmpRange.first+1, Arr.begin()+tmpRange.second+1);
        // === debug perpose
        for (int ok = 0; ok < Arr.size(); ++ok)
            {
                std::cout << Arr[ok] << " ";
            }
        // ===
        std::cout << std::endl;
        rangeList.pop_back();
        resList.pop_back();
    }

    x = 1;
    while (x < Arr.size())
    {
        tmpNum = 0;
        if (Arr[x] == '+' || Arr[x] == '-'){
            firstPos = x - 1;
            tmpNum += Arr[x-1];
            if (Arr[x] == '+')
            {
                tmpNum += Arr[x+1];
            }
            else if (Arr[x] == '-')
            {
                tmpNum -= Arr[x+1];
            }
            x+=2;
            while ((Arr[x] == '+' || Arr[x] == '-') &&
            x < Arr.size())
            {
                if (Arr[x] == '+')
                {
                    tmpNum += Arr[x+1];
                }
                else if (Arr[x] == '-')
                {
                    tmpNum -= Arr[x+1];
                }
                x+=2;
            }
            // == debug perpose
            for (int ok = firstPos; ok < x; ++ok)
            {
                std::cout << Arr[ok] << " ";
            }
            std::cout << std::endl;
            // ==
            rangeList.push_back({firstPos, x});
        }
        x+=2;
        resList.push_back(tmpNum);
        std::cout << tmpNum << std::endl;
    }

    while (rangeList.size() > 0)
    {
        tmpRange = rangeList.back();
        Arr.insert(Arr.begin()+tmpRange.first, resList.back());
        Arr.erase(Arr.begin()+tmpRange.first+1, Arr.begin()+tmpRange.second+1);
        // === debug perpose
        for (int ok = 0; ok < Arr.size(); ++ok)
            {
                std::cout << Arr[ok] << " ";
            }
        // ===
        std::cout << std::endl;
        rangeList.pop_back();
        resList.pop_back();
    }    
    return 1;
}

bool Calculator::parseArith(std::string buffer)
{
    std::vector<unsigned long long> parsedArr;
    std::vector<unsigned long long> operatorPos;
    unsigned long long i = 0;
    unsigned long long x;
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

    this->internalParse(parsedArr);
    return 1;
    ERROR_MATH_SIGN_PLACEMENT:
    std::cout << "Error math operator sign placement" << std::endl;
    return 0;
}

void Calculator::parse(){
    parseArith(this->internalParseBuffer);
    //this->parseBrackets();
}   
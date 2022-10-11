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
            std::cout << "[Calculator::isValidExp] Weird characters not allowed in expression" << std::endl;
            return 0;
        }
    }
    return 1;
}

void Calculator::getInput()
{
    do 
    {
        std::cout << ">> ";
        if (Calculator::internalParseBuffer.empty() == true)
        {
            std::getline(std::cin, this->internalParseBuffer);
            if (std::cin.eof()) 
            {
                std::cout << std::endl;
                exit(1);
            }
        }
        else
        {
            this->internalParseBuffer.clear();
            std::getline(std::cin, this->internalParseBuffer);
            if (std::cin.eof()) 
            {
                std::cout << std::endl;
                exit(1);
            }
        }
    } while (!this->isValidExp());
    this->parseExpression();
}

bool Calculator::parseBrackets(std::string buffer)
{
    std::string tmpBufOrigin = buffer;
    std::string tmpBuf1, tmpBuf2, tmpBuf;
    unsigned long long tmpNum;
    long long open_bracket_pos;
    long long close_bracket_pos;

    close_bracket_pos = tmpBufOrigin.find_first_of(")");
    open_bracket_pos = tmpBufOrigin.substr(0, close_bracket_pos).find_last_of("(");

    while (open_bracket_pos != -1 || close_bracket_pos != -1)
    {
        //std::cout << open_bracket_pos << std::endl;
        //std::cout << close_bracket_pos << std::endl;
        if (open_bracket_pos + 1 == close_bracket_pos){
            goto ERROR_BRACKET_PARSE;
        }

        if (open_bracket_pos > close_bracket_pos){
            goto ERROR_BRACKET_PARSE;
        }

        if ((open_bracket_pos != close_bracket_pos) &&
        ((open_bracket_pos | close_bracket_pos) == -1)){
            goto ERROR_BRACKET_PARSE;
        }
        if (this->parseArith(tmpBufOrigin.substr(open_bracket_pos+1, close_bracket_pos-open_bracket_pos-1), tmpNum) == 0)
        {
            return 0;
        }
        tmpBuf1 = tmpBufOrigin.substr(0, open_bracket_pos);
        tmpBuf2 = tmpBufOrigin.substr(close_bracket_pos+1, tmpBufOrigin.size());
        tmpBuf = tmpBuf1;
        if (open_bracket_pos > 0)
        {
            if ((tmpBufOrigin[open_bracket_pos-1] == ')') ||
            ((tmpBufOrigin[open_bracket_pos-1] >= '0') && (tmpBufOrigin[open_bracket_pos-1] <= '9')))
            {
                tmpBuf+='*';
            }
        }
        tmpBuf += std::to_string(tmpNum);
        if ((close_bracket_pos < tmpBufOrigin.size()-1))
        {
            if ((tmpBufOrigin[close_bracket_pos+1] == '(') ||
            ((tmpBufOrigin[close_bracket_pos+1] >= '0') && (tmpBufOrigin[close_bracket_pos+1] <= '9')))
            {
                tmpBuf+='*';
            }
        }
        tmpBuf += tmpBuf2;
        tmpBufOrigin = tmpBuf;
        close_bracket_pos = tmpBufOrigin.find_first_of(")");
        open_bracket_pos = tmpBufOrigin.substr(0, close_bracket_pos).find_last_of("(");
    }
    this->internalParseBuffer = tmpBufOrigin;
    return 1;
ERROR_BRACKET_PARSE:
    std::cout << "[Calculator::parseBrackets] Error" << std::endl;
    return 0;
}

unsigned long long Calculator::internalParse(std::vector<unsigned long long> &Arr)
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
            /*
            for (int ok = firstPos; ok < x; ++ok)
            {
                std::cout << Arr[ok] << " ";
            }
            std::cout << std::endl;
            */
            // ==
            rangeList.push_back({firstPos, x});
        }
        x+=2;
        resList.push_back(tmpNum);
    }

    while (rangeList.size() > 0)
    {
        tmpRange = rangeList.back();
        Arr.insert(Arr.begin()+tmpRange.first, resList.back());
        Arr.erase(Arr.begin()+tmpRange.first+1, Arr.begin()+tmpRange.second+1);
        // === debug perpose
        /*
        for (int ok = 0; ok < Arr.size(); ++ok)
            {
                std::cout << Arr[ok] << " ";
            }
        std::cout << std::endl;
        */
        // ===
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
            /*
            for (int ok = firstPos; ok < x; ++ok)
            {
                std::cout << Arr[ok] << " ";
            }
            std::cout << std::endl;
            */
            // ==
            rangeList.push_back({firstPos, x});
        }
        x+=2;
        resList.push_back(tmpNum);
    }

    while (rangeList.size() > 0)
    {
        tmpRange = rangeList.back();
        Arr.insert(Arr.begin()+tmpRange.first, resList.back());
        Arr.erase(Arr.begin()+tmpRange.first+1, Arr.begin()+tmpRange.second+1);
        // === debug perpose
        /*
        for (int ok = 0; ok < Arr.size(); ++ok)
            {
                std::cout << Arr[ok] << " ";
            }
        std::cout << std::endl;
        */
        // ===
        rangeList.pop_back();
        resList.pop_back();
    }    
    return Arr[0];
}

bool Calculator::parseArith(std::string buffer, unsigned long long &resNum)
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

    resNum = this->internalParse(parsedArr);
    return 1;
    ERROR_MATH_SIGN_PLACEMENT:
    std::cout << "[Calculator::parseArith] Error math operator sign placement" << std::endl;
    return 0;
}

void Calculator::parseExpression(){
    long long resNum;
    if (!this->parseBrackets(this->internalParseBuffer))
    {
        return;
    }
    if (!parseArith(this->internalParseBuffer, resNum))
    {
        return;
    }
    std::cout << resNum << std::endl;
}   

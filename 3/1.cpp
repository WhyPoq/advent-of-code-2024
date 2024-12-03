#include <iostream>
#include <fstream>
#include <string>

int nextPos = 0;
char curChar = 0;
std::string code = "";

void advance()
{
    if (nextPos < code.length())
    {
        curChar = code[nextPos];
        nextPos++;
    }
    else
    {
        curChar = -1;
    }
}

bool eatChar(char c)
{
    return curChar == c;
}

bool isDigit(char c)
{
    return '0' <= c && c <= '9';
}

int getNumber()
{
    int result = 0;
    while (curChar != -1 && isDigit(curChar))
    {
        result = result * 10 + (curChar - '0');
        advance();
    }

    return result;
}

int main()
{
    std::ifstream fin("input.txt");
    std::string line;
    while (std::getline(fin, line))
    {
        code += line;
    }
    fin.close();

    int ans = 0;

    while (curChar != -1)
    {
        if (!eatChar('m'))
        {
            advance();
            continue;
        }
        advance();
        if (!eatChar('u'))
            continue;
        advance();
        if (!eatChar('l'))
            continue;
        advance();
        if (!eatChar('('))
            continue;
        advance();

        if (!isDigit(curChar))
            continue;

        int num1 = getNumber();

        if (!eatChar(','))
            continue;
        advance();

        if (!isDigit(curChar))
            continue;

        int num2 = getNumber();

        if (!eatChar(')'))
            continue;
        advance();

        ans += num1 * num2;
    }

    std::cout << ans << "\n";

    return 0;
}
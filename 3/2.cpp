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

bool hasString(const std::string &str)
{
    int savedPos = nextPos;

    int strPos = 0;
    while (curChar != -1 && strPos < str.length() && curChar == str[strPos])
    {
        strPos++;
        advance();
    }

    // found
    if (strPos == str.length())
        return true;

    // not found, backtrack
    nextPos = savedPos - 1;
    advance();
    return false;
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
    bool isDo = true;
    advance();
    while (curChar != -1)
    {
        if (curChar == '\n')
        {
            isDo = true;
            advance();
        }

        if (hasString("don't()"))
        {
            isDo = false;
            continue;
        }
        if (hasString("do()"))
        {
            isDo = true;
            continue;
        }

        if (!hasString("mul("))
        {
            advance();
            continue;
        }

        if (!isDigit(curChar))
            continue;

        int num1 = getNumber();

        if (!hasString(","))
            continue;

        if (!isDigit(curChar))
            continue;

        int num2 = getNumber();

        if (!hasString(")"))
            continue;

        if (isDo)
            ans += num1 * num2;
    }

    std::cout << ans << "\n";

    return 0;
}
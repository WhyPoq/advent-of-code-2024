#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

int get_sign(int val)
{
    return val < 0 ? -1 : 1;
}

int main()
{
    std::ifstream fin("input.txt");

    int safe_count = 0;

    std::string line;
    while (std::getline(fin, line))
    {
        std::istringstream iss(line);
        int last;
        iss >> last;

        bool is_safe = true;
        int sign = 0;
        int cur;
        while (iss >> cur)
        {
            int diff = cur - last;
            if (sign == 0)
                sign = get_sign(diff);

            if (!(1 <= std::abs(diff) && std::abs(diff) <= 3) || get_sign(diff) != sign)
                is_safe = false;

            last = cur;
        }

        if (is_safe)
            safe_count++;
    }

    fin.close();

    std::cout << safe_count << "\n";

    return 0;
}
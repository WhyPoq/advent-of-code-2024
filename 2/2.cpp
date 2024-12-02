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
        std::vector<int> levels;
        int level;
        while (iss >> level)
        {
            levels.push_back(level);
        }

        bool is_safe = false;
        for (int skip_ind = -1; skip_ind < (int)levels.size(); skip_ind++)
        {
            is_safe = true;
            int sign = 0;
            int last;
            bool has_last = false;
            for (int i = 0; i < levels.size(); i++)
            {
                if (i == skip_ind)
                    continue;

                if (!has_last)
                {
                    last = levels[i];
                    has_last = true;
                    continue;
                }

                int diff = levels[i] - last;
                int cur_abs = std::abs(diff);
                int cur_sign = get_sign(diff);
                if (sign == 0)
                    sign = cur_sign;

                if (!(1 <= cur_abs && cur_abs <= 3) || cur_sign != sign)
                {
                    is_safe = false;
                    break;
                }

                last = levels[i];
            }

            if (is_safe)
                break;
        }

        if (is_safe)
            safe_count++;
    }

    fin.close();

    std::cout << safe_count << "\n";

    return 0;
}
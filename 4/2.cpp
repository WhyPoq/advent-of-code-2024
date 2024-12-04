#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool is_ms(char c1, char c2)
{
    return (c1 == 'M' && c2 == 'S') || (c1 == 'S' && c2 == 'M');
}

int main()
{
    std::ifstream fin("input.txt");

    std::vector<std::string> map;

    std::string line;
    while (getline(fin, line))
    {
        map.push_back(line);
    }

    fin.close();

    int W = map[0].length();
    int H = map.size();

    int count_found = 0;

    for (int i = 1; i < (int)map.size() - 1; i++)
    {
        for (int j = 1; j < (int)map[i].length() - 1; j++)
        {
            if (map[i][j] != 'A')
                continue;

            char l1 = map[i - 1][j - 1];
            char l2 = map[i + 1][j + 1];

            char r1 = map[i - 1][j + 1];
            char r2 = map[i + 1][j - 1];

            if (is_ms(l1, l2) && is_ms(r1, r2))
                count_found++;
        }
    }

    std::cout << count_found << "\n";

    return 0;
}
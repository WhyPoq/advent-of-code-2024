#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct vec2
{
    int x;
    int y;
};

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
    std::string target = "XMAS";

    std::vector<vec2> dirs = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].length(); j++)
        {
            bool success = false;
            for (vec2 dir : dirs)
            {
                success = true;
                int x = j;
                int y = i;
                for (int k = 0; k < target.size(); k++)
                {
                    if (x < 0 || y < 0 || x >= W || y >= H || map[y][x] != target[k])
                    {
                        success = false;
                        break;
                    }
                    x += dir.x;
                    y += dir.y;
                }

                if (success)
                    count_found++;
            }
        }
    }

    std::cout << count_found << "\n";

    return 0;
}
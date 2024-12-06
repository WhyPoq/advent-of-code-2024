#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Vec2
{
    int x;
    int y;
};

void rotate_right(Vec2 &vec)
{
    int tmp = vec.x;
    vec.x = -vec.y;
    vec.y = tmp;
}

int main()
{
    std::vector<std::vector<bool>> map;
    std::vector<std::vector<bool>> visited;
    Vec2 dir = {0, -1};
    Vec2 cur_pos = {0};

    std::fstream fin("input.txt");

    std::string line;
    while (getline(fin, line))
    {
        visited.push_back(std::vector<bool>(line.length(), false));

        std::vector<bool> row;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '#')
            {
                row.push_back(true);
            }
            else if (line[i] == '.')
            {
                row.push_back(false);
            }
            else if (line[i] == '^')
            {
                row.push_back(false);
                cur_pos = {i, (int)map.size()};
            }
        }

        map.push_back(row);
    }

    fin.close();

    int W = map[0].size();
    int H = map.size();

    while (true)
    {
        Vec2 next_pos = {cur_pos.x + dir.x, cur_pos.y + dir.y};

        // if went outside the map
        if (next_pos.x < 0 || next_pos.y < 0 || next_pos.x >= W || next_pos.y >= H)
            break;

        // if there is an obstable in front
        if (map[next_pos.y][next_pos.x] == true)
        {
            rotate_right(dir);
            continue;
        }

        cur_pos = next_pos;
        visited[cur_pos.y][cur_pos.x] = true;
    }

    int ans = 0;
    for (int y = 0; y < H; y++)
    {
        for (int x = 0; x < W; x++)
        {
            if (visited[y][x])
                ans++;
        }
    }

    std::cout << ans << "\n";

    return 0;
}
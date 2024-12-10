#include <iostream>
#include <string>
#include <vector>
#include <fstream>

void reset_visited(int W, int H, std::vector<std::vector<bool>> &visited)
{
    for (int y = 0; y < H; y++)
    {
        for (int x = 0; x < W; x++)
        {
            visited[y][x] = 0;
        }
    }
}

int reach9(int W, int H, std::vector<std::vector<int>> &map, std::vector<std::vector<bool>> &visited, int x, int y, int cur_height)
{
    if (x < 0 || y < 0 || x >= W || y >= H || visited[y][x] || map[y][x] != cur_height)
        return 0;

    visited[y][x] = true;

    if (cur_height == 9)
        return 1;

    return reach9(W, H, map, visited, x + 1, y, cur_height + 1) +
           reach9(W, H, map, visited, x - 1, y, cur_height + 1) +
           reach9(W, H, map, visited, x, y + 1, cur_height + 1) +
           reach9(W, H, map, visited, x, y - 1, cur_height + 1);
}

int main()
{
    std::vector<std::vector<int>> map;
    std::vector<std::vector<bool>> visited;

    std::ifstream fin("input.txt");
    std::string line;
    while (getline(fin, line))
    {
        std::vector<int> row;
        for (int i = 0; i < line.length(); i++)
        {
            row.push_back(line[i] - '0');
        }
        map.push_back(row);

        visited.push_back(std::vector<bool>(line.length(), false));
    }

    int W = map[0].size();
    int H = map.size();

    int ans = 0;
    for (int y = 0; y < H; y++)
    {
        for (int x = 0; x < W; x++)
        {
            if (map[y][x] == 0)
            {
                reset_visited(W, H, visited);
                ans += reach9(W, H, map, visited, x, y, 0);
            }
        }
    }

    std::cout << ans << "\n";

    return 0;
}
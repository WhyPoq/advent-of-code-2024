#include <iostream>
#include <string>
#include <fstream>
#include <vector>

struct Region
{
    int area;
    int perimeter;
};

struct Vec2
{
    int x;
    int y;
};

std::vector<Vec2> dirs = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

Region dfs(std::vector<std::string> &map, std::vector<std::vector<bool>> &visited, int W, int H, int x, int y)
{
    Region region = {1, 0};
    visited[y][x] = true;

    for (int i = 0; i < dirs.size(); i++)
    {
        int next_x = x + dirs[i].x;
        int next_y = y + dirs[i].y;

        // if need to add 1 to perimeter
        if (next_x < 0 || next_y < 0 || next_x >= W || next_y >= H || map[next_y][next_x] != map[y][x])
        {
            region.perimeter++;
        }
        else if (!visited[next_y][next_x])
        {
            Region child_region = dfs(map, visited, W, H, next_x, next_y);
            region.area += child_region.area;
            region.perimeter += child_region.perimeter;
        }
    }

    return region;
}

int main()
{
    std::vector<std::string> map;
    std::vector<std::vector<bool>> visited;

    std::ifstream fin("input.txt");
    std::string line;
    while (getline(fin, line))
    {
        map.push_back(line);
        visited.push_back(std::vector<bool>(line.length(), false));
    }
    fin.close();

    int W = map[0].length();
    int H = map.size();

    int ans = 0;
    for (int y = 0; y < H; y++)
    {
        for (int x = 0; x < W; x++)
        {
            if (!visited[y][x])
            {
                Region region = dfs(map, visited, W, H, x, y);
                ans += region.area * region.perimeter;
            }
        }
    }

    std::cout << ans << "\n";

    return 0;
}
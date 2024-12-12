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

struct Cell_State
{
    int region_id;
    bool fences[4];
};

std::vector<Vec2> dirs = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

int dfs(std::vector<std::string> &map, std::vector<std::vector<Cell_State>> &cell_states, int W, int H, int x, int y, int region_id)
{
    int area = 1;
    cell_states[y][x].region_id = region_id;

    for (int i = 0; i < dirs.size(); i++)
    {
        int next_x = x + dirs[i].x;
        int next_y = y + dirs[i].y;

        if (next_x < 0 || next_y < 0 || next_x >= W || next_y >= H || map[next_y][next_x] != map[y][x])
        {
            cell_states[y][x].fences[i] = true;
        }
        else if (cell_states[next_y][next_x].region_id == -1)
        {
            area += dfs(map, cell_states, W, H, next_x, next_y, region_id);
        }
    }

    return area;
}

void remove_fence(std::vector<std::vector<Cell_State>> &cell_states, int W, int H, int x, int y, int fence_side)
{
    cell_states[y][x].fences[fence_side] = false;

    for (int i = 0; i < dirs.size(); i++)
    {
        int next_x = x + dirs[i].x;
        int next_y = y + dirs[i].y;

        if (next_x >= 0 && next_y >= 0 && next_x < W && next_y < H &&
            cell_states[next_y][next_x].region_id == cell_states[y][x].region_id &&
            cell_states[next_y][next_x].fences[fence_side] == true)
        {
            remove_fence(cell_states, W, H, next_x, next_y, fence_side);
        }
    }
}

int main()
{
    std::vector<std::string> map;
    std::vector<std::vector<Cell_State>> cell_states;

    std::ifstream fin("input.txt");
    std::string line;
    while (getline(fin, line))
    {
        map.push_back(line);
        cell_states.push_back(std::vector<Cell_State>(line.length(), {-1, {false, false, false, false}}));
    }
    fin.close();

    int W = map[0].length();
    int H = map.size();

    std::vector<Region> regions;
    int next_region_id = 0;
    for (int y = 0; y < H; y++)
    {
        for (int x = 0; x < W; x++)
        {
            if (cell_states[y][x].region_id == -1)
            {
                regions.push_back({dfs(map, cell_states, W, H, x, y, next_region_id), 0});
                next_region_id++;
            }
        }
    }

    for (int y = 0; y < H; y++)
    {
        for (int x = 0; x < W; x++)
        {
            for (int i = 0; i < 4; i++)
            {
                if (cell_states[y][x].fences[i])
                {
                    remove_fence(cell_states, W, H, x, y, i);
                    regions[cell_states[y][x].region_id].perimeter++;
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < regions.size(); i++)
    {
        ans += regions[i].area * regions[i].perimeter;
    }

    std::cout << ans;

    return 0;
}
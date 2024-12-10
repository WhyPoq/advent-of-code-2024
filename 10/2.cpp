#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>

struct Pos
{
    int x;
    int y;
    int height;
    int from_x;
    int from_y;
};

void reset_num_ways(int W, int H, std::vector<std::vector<int>> &num_ways)
{
    for (int y = 0; y < H; y++)
    {
        for (int x = 0; x < W; x++)
        {
            num_ways[y][x] = 0;
        }
    }
}

int main()
{
    std::vector<std::vector<int>> map;
    std::vector<std::vector<int>> num_ways;

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

        num_ways.push_back(std::vector<int>(line.length(), 0));
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
                reset_num_ways(W, H, num_ways);
                std::queue<Pos> q;
                q.push({x, y, 0, -1, -1});
                num_ways[y][x] = 0;

                while (!q.empty())
                {
                    Pos pos = q.front();
                    q.pop();
                    if (pos.x >= 0 && pos.y >= 0 && pos.x < W && pos.y < H && map[pos.y][pos.x] == pos.height)
                    {
                        int add_ways = pos.from_y == -1 ? 1 : num_ways[pos.from_y][pos.from_x];
                        num_ways[pos.y][pos.x] += add_ways;
                        if (num_ways[pos.y][pos.x] == add_ways)
                        {
                            q.push({pos.x + 1, pos.y, pos.height + 1, pos.x, pos.y});
                            q.push({pos.x - 1, pos.y, pos.height + 1, pos.x, pos.y});
                            q.push({pos.x, pos.y + 1, pos.height + 1, pos.x, pos.y});
                            q.push({pos.x, pos.y - 1, pos.height + 1, pos.x, pos.y});
                        }
                    }
                }

                for (int i = 0; i < H; i++)
                {
                    for (int j = 0; j < W; j++)
                    {
                        if (map[i][j] == 9)
                            ans += num_ways[i][j];
                    }
                }
            }
        }
    }

    std::cout << ans << "\n";

    return 0;
}
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

struct Pos
{
    int x;
    int y;
};

bool is_inbounds(int W, int H, const Pos &pos)
{
    return pos.x >= 0 && pos.y >= 0 && pos.x < W && pos.y < H;
}

void mark_pos(std::vector<std::string> &map, int W, int H, const Pos &pos, int &ans)
{
    if (is_inbounds(W, H, pos) && map[pos.y][pos.x] != '#')
    {
        map[pos.y][pos.x] = '#';
        ans++;
    }
}

int main()
{
    std::vector<std::string> map;

    std::ifstream fin("input.txt");

    std::string line;
    while (getline(fin, line))
    {
        map.push_back(line);
    }

    fin.close();

    int W = map[0].length();
    int H = map.size();

    std::unordered_map<char, std::vector<Pos>> sameFreqs;
    for (int y = 0; y < H; y++)
    {
        for (int x = 0; x < W; x++)
        {
            if (map[y][x] != '.')
                sameFreqs[map[y][x]].push_back({x, y});
        }
    }

    int ans = 0;
    for (auto &item : sameFreqs)
    {
        std::vector<Pos> &poses = item.second;
        for (int i = 0; i < poses.size(); i++)
        {
            Pos pos1 = poses[i];
            for (int j = i + 1; j < poses.size(); j++)
            {
                Pos pos2 = poses[j];
                int xdiff = pos2.x - pos1.x;
                int ydiff = pos2.y - pos1.y;

                Pos cur_pos = pos2;
                while (is_inbounds(W, H, cur_pos))
                {
                    mark_pos(map, W, H, cur_pos, ans);
                    cur_pos.x += xdiff;
                    cur_pos.y += ydiff;
                }

                cur_pos = pos1;
                while (is_inbounds(W, H, cur_pos))
                {
                    mark_pos(map, W, H, cur_pos, ans);
                    cur_pos.x -= xdiff;
                    cur_pos.y -= ydiff;
                }
            }
        }
    }

    std::cout << ans << "\n";

    return 0;
}
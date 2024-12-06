#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Vec2
{
    int x;
    int y;
};

struct Visited_State
{
    bool up;
    bool down;
    bool left;
    bool right;
};

void rotate_right(Vec2 &vec)
{
    int tmp = vec.x;
    vec.x = -vec.y;
    vec.y = tmp;
}

void mark_visited(std::vector<std::vector<Visited_State>> &visited, const Vec2 &pos, const Vec2 &dir)
{
    if (dir.x == 0 && dir.y == -1)
        visited[pos.y][pos.x].up = true;
    else if (dir.x == 0 && dir.y == 1)
        visited[pos.y][pos.x].down = true;
    else if (dir.x == -1 && dir.y == 0)
        visited[pos.y][pos.x].left = true;
    else if (dir.x == 1 && dir.y == 0)
        visited[pos.y][pos.x].right = true;
}

bool is_visited(const std::vector<std::vector<Visited_State>> &visited, const Vec2 &pos, const Vec2 &dir)
{
    if (dir.x == 0 && dir.y == -1)
        return visited[pos.y][pos.x].up == true;
    else if (dir.x == 0 && dir.y == 1)
        return visited[pos.y][pos.x].down == true;
    else if (dir.x == -1 && dir.y == 0)
        return visited[pos.y][pos.x].left == true;
    else if (dir.x == 1 && dir.y == 0)
        return visited[pos.y][pos.x].right == true;

    return false;
}

void reset_visited(std::vector<std::vector<Visited_State>> &visited)
{
    for (int y = 0; y < visited.size(); y++)
    {
        for (int x = 0; x < visited[y].size(); x++)
        {
            visited[y][x] = {false, false, false, false};
        }
    }
}

int main()
{
    std::vector<std::vector<bool>> map;
    std::vector<std::vector<Visited_State>> visited;
    Vec2 guard_pos = {0};

    std::fstream fin("input.txt");

    std::string line;
    while (getline(fin, line))
    {
        std::vector<Visited_State> visited_row;
        std::vector<bool> row;
        for (int i = 0; i < line.length(); i++)
        {
            visited_row.push_back({false, false, false});

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
                guard_pos = {i, (int)map.size()};
            }
        }

        visited.push_back(visited_row);
        map.push_back(row);
    }

    fin.close();

    int W = map[0].size();
    int H = map.size();

    int ans = 0;
    Vec2 dir = {0, -1};
    Vec2 cur_pos = guard_pos;
    for (int ob_y = 0; ob_y < H; ob_y++)
    {
        for (int ob_x = 0; ob_x < W; ob_x++)
        {
            if (map[ob_y][ob_x] == true || (guard_pos.x == ob_x && guard_pos.y == ob_y))
                continue;

            map[ob_y][ob_x] = true;
            reset_visited(visited);

            dir = {0, -1};
            cur_pos = guard_pos;
            mark_visited(visited, cur_pos, dir);

            bool looped = false;

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
                if (is_visited(visited, cur_pos, dir))
                {
                    looped = true;
                    break;
                }
                mark_visited(visited, cur_pos, dir);
            }

            if (looped)
                ans++;

            map[ob_y][ob_x] = false;
        }
    }

    std::cout << ans << "\n";

    return 0;
}
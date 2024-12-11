#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef long long int ll;

std::vector<std::string> split(const std::string &str, char delimiter)
{
    std::vector<std::string> res;
    res.push_back("");
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == delimiter)
        {
            res.push_back("");
        }
        else
        {
            res[res.size() - 1] += str[i];
        }
    }
    return res;
}

int main()
{
    std::string line;
    std::ifstream fin("input.txt");
    getline(fin, line);
    fin.close();

    std::vector<ll> stones;
    std::vector<std::string> stones_str = split(line, ' ');
    for (int i = 0; i < stones_str.size(); i++)
    {
        stones.push_back(stoll(stones_str[i]));
    }

    int blinks = 75;

    ll precalcs[10][blinks + 1];

    for (int i = 0; i < blinks + 1; i++)
    {
        for (int digit = 0; digit <= 9; digit++)
        {
            precalcs[digit][i] = 0;
        }
    }

    for (int digit = 0; digit <= 9; digit++)
    {
        precalcs[digit][0] = 1;
    }

    for (int blinks_count = 1; blinks_count <= blinks; blinks_count++)
    {
        for (int digit = 0; digit <= 9; digit++)
        {
            std::vector<ll> cur;
            cur.push_back(digit);
            std::vector<ll> next;
            ll ans = 0;
            for (int t = 0; t < blinks_count; t++)
            {
                int blinks_left = blinks_count - t;
                for (int i = 0; i < cur.size(); i++)
                {
                    if (0 <= cur[i] && cur[i] <= 9 && precalcs[cur[i]][blinks_left] != 0)
                    {
                        ans += precalcs[cur[i]][blinks_left];
                    }
                    else if (cur[i] == 0)
                    {
                        next.push_back(1);
                    }
                    else
                    {
                        std::string stone_str = std::to_string(cur[i]);
                        if (stone_str.length() % 2 == 0)
                        {
                            ll left_stone = std::stoll(stone_str.substr(0, stone_str.length() / 2));
                            ll right_stone = std::stoll(stone_str.substr(stone_str.length() / 2, stone_str.length() / 2));
                            next.push_back(left_stone);
                            next.push_back(right_stone);
                        }
                        else
                        {
                            next.push_back(cur[i] * 2024);
                        }
                    }
                }
                cur = next;
                next.clear();
            }
            precalcs[digit][blinks_count] = ans + cur.size();
        }
    }

    // for (int i = 0; i < blinks + 1; i++)
    // {
    //     for (int j = 0; j <= 9; j++)
    //     {
    //         std::cout << precalcs[j][i] << "\t";
    //     }
    //     std::cout << "\n";
    // }

    std::vector<ll> next_stones;
    ll ans = 0;
    for (int t = 0; t < blinks; t++)
    {
        int blinks_left = blinks - t;
        for (int i = 0; i < stones.size(); i++)
        {
            if (0 <= stones[i] && stones[i] <= 9 && precalcs[stones[i]][blinks_left] != 0)
            {
                ans += precalcs[stones[i]][blinks_left];
            }
            else if (stones[i] == 0)
            {
                next_stones.push_back(1);
            }
            else
            {
                std::string stone_str = std::to_string(stones[i]);
                if (stone_str.length() % 2 == 0)
                {
                    ll left_stone = std::stoll(stone_str.substr(0, stone_str.length() / 2));
                    ll right_stone = std::stoll(stone_str.substr(stone_str.length() / 2, stone_str.length() / 2));
                    next_stones.push_back(left_stone);
                    next_stones.push_back(right_stone);
                }
                else
                {
                    next_stones.push_back(stones[i] * 2024);
                }
            }
        }

        stones = next_stones;
        next_stones.clear();
        std::cout << t << ") " << ans + stones.size() << " " << ans << "...\n";
    }
    ans += stones.size();
    std::cout << ans << "\n";

    return 0;
}
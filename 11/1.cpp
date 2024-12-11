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
    std::ifstream fin("test.txt");
    getline(fin, line);
    fin.close();

    std::vector<ll> stones;
    std::vector<std::string> stones_str = split(line, ' ');
    for (int i = 0; i < stones_str.size(); i++)
    {
        stones.push_back(stoll(stones_str[i]));
    }

    int blinks = 25;
    std::vector<ll> next_stones;
    for (int t = 0; t < blinks; t++)
    {
        for (int i = 0; i < stones.size(); i++)
        {
            if (stones[i] == 0)
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
    }

    std::cout << stones.size() << "\n";

    return 0;
}
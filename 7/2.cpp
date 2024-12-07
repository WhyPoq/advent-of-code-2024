#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

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
    std::ifstream fin("input.txt");

    ll ans = 0;
    std::string line;
    while (getline(fin, line))
    {
        std::vector<std::string> parts = split(line, ':');

        ll target = std::stoll(parts[0]);

        std::string nums_str_raw = parts[1];
        nums_str_raw.erase(0, 1);
        std::vector<std::string> nums_str = split(nums_str_raw, ' ');

        std::vector<ll> nums;
        for (int i = 0; i < nums_str.size(); i++)
        {
            nums.push_back(std::stoll(nums_str[i]));
        }

        int ops_count = nums.size() - 1;
        ll max_state = std::pow(3, ops_count);
        bool possible = false;
        for (ll state = 0; state < max_state; state++)
        {
            ll cur_state = state;
            ll cur_res = nums[0];
            for (int i = 0; i < ops_count; i++)
            {
                int rem = cur_state % 3;
                if (rem == 0)
                    cur_res += nums[i + 1];
                else if (rem == 1)
                    cur_res *= nums[i + 1];
                else
                {
                    ll tmp = nums[i + 1];
                    while (tmp > 0)
                    {
                        tmp = tmp / 10;
                        cur_res = cur_res * 10;
                    }

                    cur_res += nums[i + 1];
                }

                cur_state = cur_state / 3;
            }

            if (cur_res == target)
            {
                possible = true;
                break;
            }
        }

        if (possible)
            ans += target;
    }

    fin.close();
    std::cout << ans << "\n";

    return 0;
}
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

typedef long long int ll;

int main()
{
    std::string line;

    std::ifstream fin("input.txt");
    fin >> line;
    fin.close();

    std::vector<int> disk;
    int cur_id = 0;
    for (int i = 0; i < line.length(); i++)
    {
        int val = -1;
        // if reading file
        if (i % 2 == 0)
        {
            val = cur_id;
            cur_id++;
        }

        int len = line[i] - '0';
        for (int k = 0; k < len; k++)
            disk.push_back(val);
    }

    int left = 0;
    int right = disk.size() - 1;
    while (right > left)
    {
        if (disk[left] != -1)
        {
            left++;
        }
        else if (disk[right] == -1)
        {
            right--;
        }
        else
        {
            disk[left] = disk[right];
            left++;
            right--;
        }
    }

    int final_len = right + 1;

    // for (int i = 0; i < final_len; i++)
    // {
    //     if (disk[i] == -1)
    //         std::cout << '.';
    //     else
    //         std::cout << disk[i];
    // }
    // std::cout << "\n";

    ll ans = 0;
    for (int i = 0; i < final_len; i++)
    {
        if (disk[i] != -1)
            ans += i * disk[i];
    }

    std::cout << ans << "\n";

    return 0;
}
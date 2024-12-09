#include <iostream>
#include <string>
#include <fstream>
#include <vector>

typedef long long int ll;

struct FileInfo
{
    int file_pos;
    int file_size;
};

int main()
{
    std::string line;

    std::ifstream fin("input.txt");
    fin >> line;
    fin.close();

    std::vector<int> disk;
    std::vector<FileInfo> file_infos;
    int cur_id = 0;
    for (int i = 0; i < line.length(); i++)
    {
        int val = -1;
        // if reading file
        if (i % 2 == 0)
        {
            val = cur_id;
            file_infos.push_back((FileInfo){(int)disk.size(), line[i] - '0'});
            cur_id++;
        }

        int len = line[i] - '0';
        for (int k = 0; k < len; k++)
            disk.push_back(val);
    }

    for (int i = (int)file_infos.size() - 1; i >= 0; i--)
    {
        for (int start_pos = 0; start_pos < file_infos[i].file_pos; start_pos++)
        {
            bool is_free = true;
            for (int k = 0; k < file_infos[i].file_size; k++)
            {
                if (start_pos + k >= disk.size() || disk[start_pos + k] != -1)
                {
                    is_free = false;
                    break;
                }
            }

            if (is_free)
            {
                for (int k = 0; k < file_infos[i].file_size; k++)
                {
                    disk[file_infos[i].file_pos + k] = -1;
                    disk[start_pos + k] = i;
                }
                break;
            }
        }
    }

    // for (int i = 0; i < disk.size(); i++)
    // {
    //     if (disk[i] == -1)
    //         std::cout << '.';
    //     else
    //         std::cout << disk[i];
    // }
    // std::cout << "\n";

    ll ans = 0;
    for (int i = 0; i < disk.size(); i++)
    {
        if (disk[i] != -1)
            ans += i * disk[i];
    }

    std::cout << ans << "\n";

    return 0;
}
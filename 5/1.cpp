#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

std::vector<std::string> split(const std::string &s, const std::string &delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

int main()
{
    std::ifstream fin("input.txt");

    std::unordered_map<int, std::vector<int>> page_requirements;

    std::string line;
    bool reading_requirements = true;

    int ans = 0;

    while (getline(fin, line))
    {
        if (reading_requirements)
        {
            if (line.length() == 0)
            {
                reading_requirements = false;
            }
            else
            {
                std::vector<std::string> reqs = split(line, "|");
                int page_needed = std::stoi(reqs[0]);
                int page_to_print = std::stoi(reqs[1]);
                page_requirements[page_to_print].push_back(page_needed);
            }
        }
        else
        {
            std::vector<std::string> print_order_str = split(line, ",");
            std::vector<int> print_order;

            for (int i = 0; i < print_order_str.size(); i++)
                print_order.push_back(std::stoi(print_order_str[i]));

            std::unordered_set<int> has_pages;
            for (int i = 0; i < print_order.size(); i++)
                has_pages.insert(print_order[i]);

            bool good = true;
            std::unordered_set<int> already_printed;

            for (int i = 0; i < print_order.size(); i++)
            {
                int page_to_print = print_order[i];
                if (page_requirements.find(page_to_print) != page_requirements.end())
                {
                    for (int page_needed : page_requirements[page_to_print])
                    {
                        // if needed page in print order and we have not already printed it
                        if (has_pages.find(page_needed) != has_pages.end() && already_printed.find(page_needed) == already_printed.end())
                        {
                            good = false;
                            break;
                        }
                    }
                }
                already_printed.insert(page_to_print);

                if (!good)
                    break;
            }

            if (good)
            {
                ans += print_order[print_order.size() / 2];
            }
        }
    }

    fin.close();

    std::cout << ans << "\n";

    return 0;
}
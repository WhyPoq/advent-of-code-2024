#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

typedef long long int ll;

int main()
{
    std::ifstream fin("input.txt");

    std::vector<int> list1;
    std::vector<int> list2;

    int a, b;
    while (fin >> a)
    {
        fin >> b;
        list1.push_back(a);
        list2.push_back(b);
    }
    fin.close();

    std::unordered_map<int, int> occurrences;

    for (int i = 0; i < list2.size(); i++)
    {
        int num = list2[i];
        if (occurrences.find(num) == occurrences.end())
            occurrences[num] = 1;
        else
            occurrences[num]++;
    }

    ll similarity = 0;
    for (int i = 0; i < list1.size(); i++)
    {
        int num = list1[i];
        if (occurrences.find(num) != occurrences.end())
            similarity += num * occurrences[num];
    }

    std::cout << similarity << "\n";

    return 0;
}
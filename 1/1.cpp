#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

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

    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());

    ll distSum = 0;
    for (int i = 0; i < list1.size(); i++)
    {
        distSum += std::abs(list1[i] - list2[i]);
    }

    std::cout << distSum << "\n";

    return 0;
}
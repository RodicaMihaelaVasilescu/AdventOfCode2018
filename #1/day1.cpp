#include <bits/stdc++.h>
using namespace std;

int Part2(vector<int> input)
{
    unordered_map<int, int> frequency;
    int sum = 0, index = -1;
    while(true)
    {
        ++index %= input.size();
        sum += input[index];
        frequency[sum]++;

        if(frequency[sum] == 2)
        {
            return sum;
        }
    }
}
int main ()
{
    ifstream cin("in.txt");
    ofstream cout("out.txt");

    vector <int> input;
    string inputLine;
    while(getline (cin, inputLine))
    {
        input.push_back(stoi(inputLine));
    }

    cout << "Part1: " << accumulate(input.begin(), input.end(), 0) << endl;
    cout << "Part2: " << Part2(input) << endl;

    return 0;
}

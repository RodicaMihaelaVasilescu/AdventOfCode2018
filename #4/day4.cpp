#include <bits/stdc++.h>
using namespace std;

set<string> ReadInput()
{
    set<string> input;
    ifstream cin("in.txt");
    string inputLine;
    while(getline(cin, inputLine))
    {
        input.insert(inputLine);
    }
    return input;
}

void Solve(set <string> input)
{
    map<int, int> Id_Sleep, Id_Minutes;
    map<int, map<int,int>> Id_MinutesFrequency;
    int ID, Max = 0, solutionPart2;

    for_each(input.begin(), input.end(), [&](string s)
    {
        int minutes = stoi(s.substr(15, 2));
        if(s.substr(19, 5) == "Guard")
        {
            ID = stoi(s.substr(26, s.find(' ', 27)));
        }
        else if(s.substr(19, 5) == "falls")
        {
            Id_Minutes[ID] = minutes;
        }
        else
        {
            Id_Sleep[ID] += minutes - Id_Minutes[ID];
            for(int i = Id_Minutes[ID]; i <= minutes; i++)
            {
                Id_MinutesFrequency[ID][i]++;

                if(Id_MinutesFrequency[ID][i] > Max)
                {
                    Max = Id_MinutesFrequency[ID][i];
                    solutionPart2 = ID * i;
                }
            }
        }
    });

    ///Part 1
    auto IDMax = max_element(Id_Sleep.begin(),Id_Sleep.end(),[](pair<int, int> a, pair<int, int> b)
    {
        return a.second < b.second;
    });

    auto MinutesMax = max_element(Id_MinutesFrequency[get<0>(*IDMax)].begin(),Id_MinutesFrequency[get<0>(*IDMax)].end(),[]( pair<int, int> a, pair<int, int> b)
    {
        return a.second < b.second;
    });
    cout <<"Part1: " << get<0>(*IDMax) * get<0> (*MinutesMax) << endl;

    ///Part 2
    cout << "Part2: " <<solutionPart2 << endl;
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    Solve(ReadInput());

    return 0;
}

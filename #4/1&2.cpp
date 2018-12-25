#include <bits/stdc++.h>

using namespace std;

set<string> input;
map<int, int> Id_Sleep, Id_Minutes;
map<int, map<int,int>>frequency;

int solutionPart2;

int main()
{
    ifstream cin("in.txt");
    ofstream cout("out.txt");

    string inputLine;
    while(getline(cin, inputLine))
    {
        if(inputLine != "")
            input.insert(inputLine);
    }

    int ID, Max = 0;

    for(auto &s : input)
    {
        istringstream iss(s);
        vector<string> results((istream_iterator<string>(iss)),istream_iterator<string>());

        int id = 0, minutes = (results[1][3]-'0') * 10 + results[1][4]-'0' ;
        if(results[2] == "Guard")
        {
            for(int i = 1; results[3][i] >= '0' && results[3][i] <= '9'; i++ )
                id = id*10 +results[3][i]-'0';
            ID = id;
        }
        else if(results[2] == "falls")
        {
            Id_Minutes[ID] = minutes;
        }
        else
        {
            Id_Sleep[ID] += minutes - Id_Minutes[ID];
            for(int i = Id_Minutes[ID]; i <= minutes; i++)
            {
                frequency[ID][i]++;

                if(frequency[ID][i] > Max)
                {
                    Max = frequency[ID][i];
                    solutionPart2 = ID * i;
                }
            }
        }
    }

    auto IDMax = max_element(Id_Sleep.begin(),Id_Sleep.end(),[](pair<int, int> a, pair<int, int> b)
    {
        return a.second < b.second;
    });

    auto MinutesMax = max_element(frequency[get<0>(*IDMax)].begin(),frequency[get<0>(*IDMax)].end(),[]( pair<int, int> a, pair<int, int> b)
    {
        return a.second < b.second;
    });

    ///Part 1
    cout << get<0>(*IDMax) * get<0> (*MinutesMax) <<endl;

    ///Part 2
    cout << solutionPart2;

    return 0;
}


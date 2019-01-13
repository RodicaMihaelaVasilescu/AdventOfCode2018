#include <bits/stdc++.h>
using namespace std;

vector<string> ReadInput()
{
    vector<string> input;
    string inputLine;
    while((getline (cin, inputLine)))
    {
        input.push_back(inputLine);
    }
    return input;
}

void solutionPart1(vector<string> input)
{
    int noOfWordsWith2Letters = 0, noOfWordsWith3Letters = 0;

    for_each(input.begin(), input.end(), [&](string inputLine)
    {
        unordered_map<char, int> letterFrequency;

        for_each(inputLine.begin(), inputLine.end(), [&](char letter)
        {
            letterFrequency[letter]++;
        });

        noOfWordsWith2Letters += find_if(letterFrequency.begin(),letterFrequency.end(), [](pair<char, int> fr)
        {
            return fr.second == 2;
        }) != letterFrequency.end();

        noOfWordsWith3Letters += find_if(letterFrequency.begin(),letterFrequency.end(), [](pair<char, int> fr)
        {
            return fr.second == 3;
        }) != letterFrequency.end();
    });

    cout <<"Part1: "<< noOfWordsWith2Letters * noOfWordsWith3Letters << endl;
}

void solutionPart2(vector<string> input)
{
    cout <<"Part2: ";

    for(int i = 0; i < input.size(); i++)
    {
        for(int j = i+1; j < input.size(); j++)
        {
            int noOfDifferentLetters = 0;
            for(int letter = 0; letter < input[i].size(); letter++)
            {
                if( input[i][letter] != input[j][letter])
                {
                    noOfDifferentLetters++;
                }
            }

            if(noOfDifferentLetters == 1)
            {
                for(int letter = 0 ; letter < input[i].size(); letter++)
                {
                    if(input[i][letter] == input[j][letter])
                    {
                        cout << input[i][letter];
                    }
                }
                return;
            }
        }
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    vector<string> input = ReadInput();
    solutionPart1(input);
    solutionPart2(input);

    return 0;
}

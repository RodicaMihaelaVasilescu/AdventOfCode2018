#include <bits/stdc++.h>
using namespace std;

vector<string> input;

void solutionPart1()
{
    int noOfWordsWith2Letters = 0, noOfWordsWith3Letters = 0;
    string inputLine;

    while(getline (cin, inputLine))
    {
        input.push_back(inputLine);
        map<char, int> letterFrequency;

        for_each(inputLine.begin(), inputLine.end(), [&](char letter)
        {
            letterFrequency[letter]++;
        });

        bool isThereALetterWith2Apparitions = 0, isThereALetterWith3Apparitions = 0;
        for_each(letterFrequency.begin(), letterFrequency.end(), [&](pair<char, int> x)
        {
            if(x.second == 2 && !isThereALetterWith2Apparitions)
            {
                isThereALetterWith2Apparitions = true;
                noOfWordsWith2Letters ++;
            }
            else if(x.second == 3 && !isThereALetterWith3Apparitions)
            {
                isThereALetterWith3Apparitions = true;
                noOfWordsWith3Letters++;
            }
        });

        letterFrequency.clear();
    }
    cout << noOfWordsWith2Letters * noOfWordsWith3Letters << endl;
}

void solutionPart2()
{
    for(int i = 0; i < input.size()-1; i++)
    {
        for(int j = i+1; j < input.size(); j++)
        {
            int noOfDifferentLetters = 0;

            for(int letter = 0; letter < input[i].size(); letter++)
            {
                input[i][letter] == input[j][letter] ? : noOfDifferentLetters++;
            }

            if(noOfDifferentLetters == 1)
            {
                for(int letter = 0 ; letter < input[i].size(); letter++)
                {
                    input[i][letter] != input[j][letter] ? : printf("%c", input[i][letter]);
                }
                break;
            }
        }
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    solutionPart1();
    solutionPart2();

    return 0;
}

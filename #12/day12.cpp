#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream cin("in.txt");
    ofstream cout("out.txt");
    string input;

    cin >> input >> input >> input;

    input = string (1000, '.') + input + string (1000, '.');
    int index = input.find('#');

    set<string> states;
    string a, b, c;
    while(cin >> a >> b >> c )
    {
        if(c == "#")
        {
            states.insert(a);
        }
    }

    int counter = 0, randomNumberOfGenerations = 300;
    while(counter++ != randomNumberOfGenerations)
    {
        string generation;

        for(int i = 2; input[i+2] != 0; i++)
        {
            string state;
            for(int j = i-2; j <= i+2; j++)
                state += input[j];
            generation += states.find(state) != states.end() ? "#" : ".";
        }

        input = ".." + generation + "..";

        /// Part 1
        int plants = 0;
        for(int i = 0; input[i]!= 0 && counter == 20; i++)
        {
            if(input[i] == '#')
            {
                plants += i-index;
            }
        }
        if(counter == 20)
        {
            cout <<"Part1: " << plants << endl;
        }
    }

    /// Part 2
    unsigned long long int sum = 0;
    for(int i = 0; input[i] != 0; i++)
    {
        if(input[i] == '#')
            sum += 1ll*i + 50000000000 - randomNumberOfGenerations - index;
    }
    cout << "Part2: " << sum;

    return 0;
}

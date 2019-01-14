#include <bits/stdc++.h>
using namespace std;

int Part1(string s)
{
    for(int i = 0; s[i] != 0; i++)
    {
        while(abs(s[i]-s[i+1]) == 32)
        {
            s.erase(i,2);
            i--;
        }
    }
    return s.size();
}

int Part2(string s)
{
    int Min = INT_MAX;

    for(char letter= 'a'; letter <= 'z' ; letter++)
    {
        string aux = s;
        aux.erase( remove(aux.begin(), aux.end(), letter), aux.end() );
        aux.erase( remove(aux.begin(), aux.end(), letter-32), aux.end() );

        Min = min(Min,Part1(aux));
    }
    return Min;
}

int main()
{
    ifstream cin("in.txt");
    ofstream cout("out.txt");

    string s;
    cin >> s;

    cout << "Part1: " << Part1(s) << endl;
    cout << "Part2: " << Part2(s) <<endl;

    return 0;
}

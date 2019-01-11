#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream cin("in.txt");
    ofstream cout("out.txt");

    long depth, x, y;
    string ignore;
    cin >>ignore >> depth >> ignore >> x >> ignore[0] >> y;

    vector <vector <long>> cave(x+1, vector<long>(y+1));

    long sum = 0;
    for(long i = 1; i <= max(x, y); i++)
    {
        if(i <= y)
        {
            cave[0][i] = (i * 48271 + depth) % 20183;
            sum += cave[0][i] % 3;
        }

        if(i <= x)
        {
            cave[i][0] = (i * 16807 + depth) % 20183;
            sum +=  cave[i][0] % 3;
        }
    }

    for(int i = 1; i <= x; i++ )
    {
        for(int j = 1; j <= y; j++)
        {
            cave[i][j] = (cave[i-1][j] * cave[i][j-1] + depth) %20183;
            sum += cave[i][j]%3;
        }
    }

    cout << sum <<endl;

    return 0;
}

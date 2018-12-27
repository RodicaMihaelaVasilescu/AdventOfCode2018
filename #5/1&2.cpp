#include <bits/stdc++.h>

using namespace std;

int Compute(string s)
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

int main()
{
    ifstream cin("in.txt");
    ofstream cout("out.txt");

    string s;
    cin >> s;

    cout << Compute(s) << endl;

    int Min = INT_MAX;

    for(char letter= 'a'; letter <= 'z' ; letter++)
    {
        string aux = s;
        aux.erase( remove(aux.begin(), aux.end(), letter), aux.end() );
        aux.erase( remove(aux.begin(), aux.end(), letter-32), aux.end() );

        Min = min(Min,Compute(aux));
    }

    cout << Min <<endl;

    return 0;
}

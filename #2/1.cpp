#include <bits/stdc++.h>

using namespace std;

int NR1, NR2;
int main()
{
    ifstream cin("in.txt");
    ofstream cout("out.txt");

    string s;

    while(getline (cin, s))
    {
        map<char, int> m;

        bool nrWith2Letters = 0, nrWith3Letters = 0;

        for(int i = 0; s[i]!= 0; i++)
            m[s[i]]++;

        for(auto &i: m)
            if(i.second == 2)
                nrWith2Letters = true;
            else if(i.second == 3)
                nrWith3Letters = true;

        if(nrWith2Letters)
            NR1 ++;

        if(nrWith3Letters)
            NR2++;

        m.clear();
    }
    cout << NR1 * NR2;

    return 0;
}

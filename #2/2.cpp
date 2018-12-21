#include <bits/stdc++.h>

using namespace std;

int main()
{
    ifstream cin("in.txt");
    ofstream cout("out.txt");

    string s;
    vector<string> v;

    while(getline (cin, s))
        v.push_back(s);

    for(int i = 0; i <= v.size(); i++)
        for(int j = i+1; j < v.size(); j++)
        {
            int nr = 0;
            for(int k = 0; k < v[i].size(); k++)
                if(v[i][k] != v[j][k])
                    nr++;
            if(nr == 1)
            {
                for(int k = 0 ; k < v[i].size(); k++)
                    if(v[i][k] == v[j][k])
                        cout << v[i][k];
                break;
            }
        }
    return 0;
}

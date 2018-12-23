#include <bits/stdc++.h>
using namespace std;

int a[1001][1001];
set<int> validId;

int main()
{
    ifstream cin("in.txt");
    ofstream cout("out.txt");

    char s[50];
    while(cin.getline(s, 50))
    {
        int id = 0, leftPadding = 0, topPadding = 0, width = 0, height = 0;
        char *p = strtok(s, "# @,:x");

        int nrCase = 0;
        while (p != 0)
        {
            nrCase++;
            for(int i = 0; p[i] != 0; i++)
            {
                switch(nrCase)
                {
                case 1:
                    id = id *10 + p[i]-'0';
                    break;
                case 2:
                    leftPadding = leftPadding *10 + p[i]-'0';
                    break;
                case 3:
                    topPadding = topPadding *10 + p[i]-'0';
                    break;
                case 4:
                    width = width *10 + p[i]-'0';
                    break;
                case 5:
                    height = height *10 + p[i]-'0';
                    break;
                }
            }
            p = strtok(NULL,  "# @,:x");
        }

        bool isValid = true;
        for (int i = leftPadding; i < width + leftPadding; i++)
        {
            for (int j = topPadding; j < height + topPadding; j++)
            {
                if (a[i][j] == 0)
                {
                    a[i][j] = id;
                }
                else
                {
                    validId.erase(a[i][j]);
                    isValid = false;
                }
            }
        }

        if(isValid)
            validId.insert(id);
    }

    cout << *validId.begin() << endl;
    return 0;
}

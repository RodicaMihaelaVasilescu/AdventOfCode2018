#include <bits/stdc++.h>
using namespace std;

int sum;
unordered_map<int, int> fr;
vector<string> input;

bool ComputeSum ( string str)
{
    fr[sum]++;
    int n = 0, sign = 0;
    for(int i = 0; str[i] != 0; i++)
    {
        if(str[i] == '+' || str[i] == '-')
        {
            sum += sign * n;
            fr[sum]++;
            if(i && fr[sum] == 2)
            {
                cout << sum;
                return true;
            }
            sign = str[i] == '+' ? 1 : -1;
            n = 0;
        }
        else if(str[i] >= '0' && str[i] <= '9')
        {
            n = n*10 + str[i] - '0';
        }
    }

    sum += sign * n;

    if(fr[sum] == 2)
    {
        cout << sum;
        return true;
    }
    return false;
}
int main ()
{
    ifstream cin("in.txt");
    string str;
    while(getline (cin, str))
    {
        input.push_back(str);
        if(ComputeSum(str))
            return 0;
    }

    while(true)
    {
        for(auto &str: input)
        {
            if(ComputeSum(str))
                return 0;
        }
    }
    return 0;
}

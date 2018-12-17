#include <bits/stdc++.h>
using namespace std;

int sum;

void ComputeSum ( string str)
{
    int n = 0, sign = 0;

    for(int i = 0; str[i] != 0; i++)
    {
        if(str[i] == '+' || str[i] == '-')
        {
            sum += sign * n;
            sign = str[i] == '+' ? 1 : -1;
            n = 0;
        }
        else if(str[i] >= '0' && str[i] <= '9')
        {
            n = n*10 + str[i] - '0';
        }
    }
    sum += sign * n;
}

int main ()
{
    ifstream cin("in.txt");

    string str;
    while(getline (cin, str))
    {
        ComputeSum(str);
    }

    cout << sum;

    return 0;
}

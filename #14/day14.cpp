#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream cin("in.txt");
    ofstream cout("out.txt");

    string input, str ="37";
    cin >> input;
    vector<int> myVector {3, 7};
    int i = 0, j = 1;

    while(myVector.size() <= 100000000)
    {
        int sum = myVector[i] + myVector[j];
        int index = myVector.size();
        do
        {
            myVector.insert(myVector.begin() + index, sum%10);
            str.insert(str.begin() + index, sum%10+'10');
            sum /= 10;
        }
        while(sum);

        i = ( i + myVector[i] + 1) % myVector.size();
        j = ( j + myVector[j] + 1) % myVector.size();

        ///Part1
        if(myVector.size() == 550000)
        {
            cout << "Part1 : ";
            for(int x = stoi(input); x < stoi(input)+10 ; x++ )
                cout << myVector[x];
            cout << endl;
        }
    }

    ///Part2
    cout << "Part2 : " << str.find(input);

    return 0;
}

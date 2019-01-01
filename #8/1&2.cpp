#include <bits/stdc++.h>
using namespace std;

vector <int> input;
deque<int> childrenQueue;
map<int, int> node_noOfChildren, noOfMetadata, node_metaDataSum;
map<int, vector<int>> parent_IndexesOfChildren;
int index, currentChildren, currentParent, metaDataSum;

void Compute()
{
    while(node_noOfChildren[childrenQueue.back()] == 0 && currentChildren != 0)
    {
        metaDataSum = accumulate(input.begin() + index, input.begin()+ index + noOfMetadata[childrenQueue.back()], metaDataSum);

        int sum = 0;
        if(parent_IndexesOfChildren[childrenQueue.back()].size() == 0)
        {
            sum = accumulate(input.begin() + index, input.begin()+ index + noOfMetadata[childrenQueue.back()], 0);
        }
        else
        {
            sum = accumulate(input.begin() + index, input.begin()+ index + noOfMetadata[childrenQueue.back()], 0, [](int currentSum, int x)
            {
                return x <= parent_IndexesOfChildren[childrenQueue.back()].size() ? currentSum + node_metaDataSum[parent_IndexesOfChildren[childrenQueue.back()][x-1]] : currentSum;
            });
        }

        index += noOfMetadata[childrenQueue.back()];
        node_metaDataSum[childrenQueue.back()] = sum;
        childrenQueue.pop_back();
        node_noOfChildren[childrenQueue.back()]--;
    }

    if(index >= input.size() )
        return;

    currentChildren++;
    if(currentParent)
    {
        parent_IndexesOfChildren[childrenQueue.back()].push_back(currentChildren);
    }
    node_noOfChildren[currentChildren] = input[index++];
    noOfMetadata[currentChildren] = input[index++];
    currentParent = currentChildren;
    childrenQueue.push_back(currentChildren);
    Compute();
}

int main()
{
    ifstream cin("in.txt");
    ofstream cout("out.txt");

    int n;
    while(cin >> n)
    {
        input.push_back(n);
    }

    childrenQueue.push_back(1);
    Compute();

    cout<< metaDataSum << '\n' << node_metaDataSum[1] ;
    return 0;
}

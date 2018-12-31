#include <bits/stdc++.h>
using namespace std;
#define numberOfWorkers 5
#define numberOfSeconds 61

int main()
{
    ifstream cin("in.txt");
    ofstream cout("out.txt");

    set<char> allNodes;
    map<char, set<char>> edges;
    map<char, int> frequency;
    string inputLine;

    while(getline(cin, inputLine))
    {
        char x = inputLine[5];
        char y = inputLine[36];
        allNodes.insert(x);
        allNodes.insert(y);
        edges[x].insert(y);
        frequency[y]++;
    }

    map<char, int> frequency2 = frequency;

    priority_queue<char, vector<int>, greater<int>> PriorityQueueOfTasks;
    vector<char> currentTasks;
    for(auto &i: allNodes)
    {
        if(frequency[i] == 0)
        {
            PriorityQueueOfTasks.push(i);
            currentTasks.push_back(i);
        }
    }

    ///Part 1
    while(!PriorityQueueOfTasks.empty())
    {
        char x = PriorityQueueOfTasks.top();
        cout << x ;
        PriorityQueueOfTasks.pop();
        for(auto &i: edges[x])
        {
            if(--frequency[i] == 0)
            {
                PriorityQueueOfTasks.push(i);
            }
        }
    }
    cout << endl;

    ///Part 2
    int counter = 0, currentNumberOfWorkers = numberOfWorkers, worker[numberOfWorkers]{};
    set<char> tasksInProgress;
    map<int, char> worker_task;

    while(!currentTasks.empty())
    {
        counter++;
        sort(currentTasks.begin(),currentTasks.end());
        auto tempCurrentTasks = currentTasks;

        for(int i = 0; i < numberOfWorkers && !tempCurrentTasks.empty(); i++)
        {
            vector<char>::iterator it = find_if (tempCurrentTasks.begin(), tempCurrentTasks.end(),[&](char x)
            {
                return tasksInProgress.find(x) == tasksInProgress.end();
            });

            char task = it != tempCurrentTasks.end() ? *it : 0;

            if(worker[i] == 0 && task != 0)
            {
                currentNumberOfWorkers--;
                worker[i] = (task - 'A' ) + numberOfSeconds;
                worker_task[i] = task;
                tasksInProgress.insert(task);
                tempCurrentTasks.erase(it);
            }
        }

        for(int i = 0; i < numberOfWorkers; i++)
        {
            if(worker[i] == 1)
            {
                currentNumberOfWorkers++;
                currentTasks.erase(find(currentTasks.begin(), currentTasks.end(), worker_task[i]));
                for(auto &j: edges[worker_task[i]])
                {
                    if(--frequency2[j] == 0)
                    {
                        currentTasks.push_back(j);
                    }
                }
            }
            worker[i] == 0 ? : worker[i]--;
        }
    }
    cout << counter;
    return 0;
}

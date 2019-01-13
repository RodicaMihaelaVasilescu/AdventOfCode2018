#include <bits/stdc++.h>
#define INFINITE INT_MAX
using namespace std;

int N, M, HP = 3;
vector <string> input;

struct Unit
{
    string type;
    int index = -1, hp, x = 0, y = 0;

    bool operator < (const Unit &otherUnit)
    {
        return (x < otherUnit.x) || (x == otherUnit.x && y < otherUnit.y);
    }
    void operator = (const Unit &otherUnit)
    {
        index = otherUnit.index;
        hp = otherUnit.hp;
        type = otherUnit.type;
        x = otherUnit.x;
        y = otherUnit.y;
    }
};

int r[] = { -1, 0, 0, 1 };
int c[] = { 0, -1, 1, 0 };

vector<Unit> allElvesAndGoblins;

void ReadInput()
{
    string inputLine;
    int index = 0;
    while(getline(cin, inputLine))
    {
        for(int i = 0; inputLine[i] != 0; i++)
        {
            if(inputLine[i] == 'G' || inputLine[i] == 'E')
            {
                Unit unit{string(1, inputLine[i]), index++, 200, input.size(), i };
                allElvesAndGoblins.push_back(unit);
                inputLine[i] = '.';
            }
        }
        input.push_back(inputLine);

    }
    N = input.size();
    M = input[0].size();
}

bool gameOver(vector<Unit> elvesAndGoblins)
{
    bool thereAreGoblins = find_if(elvesAndGoblins.begin(), elvesAndGoblins.end(), [](Unit u)
    {
        return u.type == "G";

    }) == elvesAndGoblins.end() ? false : true;

    bool thereAreElves = find_if(elvesAndGoblins.begin(), elvesAndGoblins.end(), [](Unit u)
    {
        return u.type == "E";

    }) == elvesAndGoblins.end() ? false : true;

    return !(thereAreElves && thereAreGoblins);
}

vector<vector<int>> initializeDistancesMatrix( vector<Unit> elvesAndGoblins )
{
    vector<vector<int>> distance (N, vector<int> (M));
    for(int i = 0; i != N; i++)
    {
        for(int j = 0; j != M; j++)
        {
            if(input[i][j] == '#')
            {
                distance[i][j] = INFINITE;
            }
        }
    }
    for(auto unit: elvesAndGoblins)
    {
        if(unit.hp > 0)
        {
            distance[unit.x][unit.y] = INFINITE;
        }
    }
    return distance;
}

vector<vector<int>> generateDistancesFromAPoint( Unit start, vector <Unit> elvesAndGoblins)
{
    auto distances = initializeDistancesMatrix(elvesAndGoblins);

    queue<pair<int, int>> queueOfCoordinates;

    queueOfCoordinates.push(make_pair(start.x, start.y));
    distances[start.x][start.y] = 1;

    while(!queueOfCoordinates.empty())
    {
        int x = get<0>(queueOfCoordinates.front());
        int y = get<1>(queueOfCoordinates.front());

        for(int i = 0; i < 4; i++)
        {
            int row = x + r[i];
            int col = y + c[i];

            if((row > 0) && (row < N) && (col > 0) && (col < M) && distances[row][col] == 0)
            {
                distances[row][col] = distances[x][y]+1;
                queueOfCoordinates.push(make_pair(row, col));
            }
        }
        queueOfCoordinates.pop();
    }
    return distances;
}

Unit getClosestNeighbourOfUnit( Unit unit, vector<vector<int>> distancesMatrix)
{
    Unit closestNegihbour;
    int MinDistance = INFINITE;

    for(int i = 0; i < 4; i++)
    {
        int row = unit.x + r[i];
        int col = unit.y + c[i];

        if(distancesMatrix[row][col] > 0 && distancesMatrix[row][col] < MinDistance)
        {
            MinDistance = distancesMatrix[row][col];
            closestNegihbour = unit;
            closestNegihbour.x = row;
            closestNegihbour.y = col;
        }
    }
    return closestNegihbour;
}

void Move(Unit &unit, vector<Unit> elvesAndGoblins)
{
    if(unit.hp <= 0)
        return;

    int MinDistance = INFINITE;
    auto distanceFromUnit = generateDistancesFromAPoint(unit, elvesAndGoblins);

    Unit enemyNeighbour ;

    for(auto possibleEnemy: elvesAndGoblins)
    {
        if(possibleEnemy.type != unit.type && possibleEnemy.hp > 0)
        {
            if(abs(unit.x - possibleEnemy.x) + abs(unit.y - possibleEnemy.y) == 1)
                return;

            Unit possibleEnemyNeighbour = getClosestNeighbourOfUnit(possibleEnemy, distanceFromUnit);
            if(distanceFromUnit[possibleEnemyNeighbour.x][possibleEnemyNeighbour.y] > 0 &&
                    distanceFromUnit[possibleEnemyNeighbour.x][possibleEnemyNeighbour.y] < MinDistance)
            {
                enemyNeighbour = possibleEnemyNeighbour;
                MinDistance =  distanceFromUnit[possibleEnemyNeighbour.x][possibleEnemyNeighbour.y];
            }
        }
    }

    if(enemyNeighbour.index == -1)
        return;

    unit = getClosestNeighbourOfUnit(unit, generateDistancesFromAPoint(enemyNeighbour, elvesAndGoblins));
}

set<int> indexesOfUnitsToRemove;
bool doElvesLose;
void Attack(Unit unit, vector<Unit> &elvesAndGoblins)
{
    if(unit.hp <= 0)
        return;

    Unit enemy;
    enemy.hp = INFINITE;
    for(auto possibleEnemy: elvesAndGoblins)
    {
        if(possibleEnemy.type != unit.type && possibleEnemy.hp > 0 &&possibleEnemy.hp < enemy.hp && abs(unit.x- possibleEnemy.x) + abs(unit.y - possibleEnemy.y) == 1)
        {
            enemy = possibleEnemy;
        }
    }

    if(enemy.index == -1 || enemy.hp == INFINITE)
        return;

    for(auto &u: elvesAndGoblins)
    {
        if(enemy.index == u.index)
        {
            u.type == "E" ? u.hp -= 3 : u.hp -= HP;

            if(u.hp <= 0)
            {
                indexesOfUnitsToRemove.insert(u.index);

                if(u.type == "E")
                {
                    doElvesLose = true; ///Part2
                }
            }
            break;
        }
    }
}

void SolvePart1()
{
    auto elvesAndGoblins = allElvesAndGoblins;
    int round = -1;
    while(!gameOver(elvesAndGoblins))
    {
        round++;
        sort(elvesAndGoblins.begin(), elvesAndGoblins.end());
        for(auto &unit: elvesAndGoblins)
        {
            Move(unit, elvesAndGoblins);
            Attack(unit, elvesAndGoblins );
        }

        for(auto i = indexesOfUnitsToRemove.rbegin(); i != indexesOfUnitsToRemove.rend(); i++)
        {
            elvesAndGoblins.erase(remove_if(elvesAndGoblins.begin(), elvesAndGoblins.end(), [&](Unit const & a)
            {
                return a.index == *i;
            }),
            elvesAndGoblins.end());
        }
        indexesOfUnitsToRemove.clear();
    }

    ///Part1
    cout << "Part1: " << round * accumulate(elvesAndGoblins.begin(), elvesAndGoblins.end(), 0, [](int sum, Unit unit)
    {
        return sum + unit.hp;
    })<<endl;

}
void SolvePart2()
{
    while(true)
    {
        ++HP;
        doElvesLose = false;
        int round = -1;
        auto elvesAndGoblins = allElvesAndGoblins;
        for(auto u: elvesAndGoblins)
            u.hp = HP;
        while(!gameOver(elvesAndGoblins) && !doElvesLose)
        {
            round++;
            sort(elvesAndGoblins.begin(), elvesAndGoblins.end());
            for(auto &unit: elvesAndGoblins)
            {
                Move(unit, elvesAndGoblins);
                Attack(unit, elvesAndGoblins );
                if(doElvesLose)
                    break;
            }

            for(auto i = indexesOfUnitsToRemove.rbegin(); i != indexesOfUnitsToRemove.rend(); i++)
            {
                elvesAndGoblins.erase(remove_if(elvesAndGoblins.begin(), elvesAndGoblins.end(), [&](Unit const & a)
                {
                    return a.index == *i;
                }),elvesAndGoblins.end());
            }
            indexesOfUnitsToRemove.clear();
        }
        if(!doElvesLose)
        {
            ///Part2
            cout <<"Part2: " << round * accumulate(elvesAndGoblins.begin(), elvesAndGoblins.end(), 0, [](int sum, Unit elf)
            {
                return elf.type == "E" ? sum + elf.hp : sum;
            });
            return;
        }
    }
}

int main()
{
    freopen ("in.txt", "r", stdin);
    freopen ("out.txt", "w", stdout);

    ReadInput();
    SolvePart1();
    SolvePart2();

    return 0;
}

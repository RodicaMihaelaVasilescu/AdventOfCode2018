#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

map<char, int> directionsToInteger = { {'N', 0}, {'S', 1}, {'E', 2}, {'W', 3} };
int row[] = { -1, 1, 0, 0 };
int col[] = { 0, 0, 1,-1 };

int index, MaximumNumberOfDoors;
map<pair<int, int>, int> CoordonatesOfRooms;
set<pair<int, int>> CoordinatesOfRoomsWithAtLeast1000Doors;

void generateMap(string regex, pair<int, int> coordinates = make_pair(0, 0))
{
	auto currentCoordinates = coordinates;
	for (index++; regex[index] != 0; index++)
	{
		if (directionsToInteger.find(regex[index]) != directionsToInteger.end())
		{
			int x = currentCoordinates.first + row[directionsToInteger[regex[index]]];
			int y = currentCoordinates.second + col[directionsToInteger[regex[index]]];
			if (CoordonatesOfRooms[make_pair(x, y)] == 0)
			{
				CoordonatesOfRooms[make_pair(x, y)] = CoordonatesOfRooms[currentCoordinates] + 1;
			}
			MaximumNumberOfDoors = max(CoordonatesOfRooms[make_pair(x, y)], MaximumNumberOfDoors);
			if (CoordonatesOfRooms[make_pair(x, y)] >= 1000)
			{
				CoordinatesOfRoomsWithAtLeast1000Doors.insert(make_pair(x, y));
			}
			currentCoordinates = make_pair(x, y);
		}
		else if (regex[index] == '(')
		{
			generateMap(regex, currentCoordinates);
		}
		else if (regex[index] == '|')
		{
			currentCoordinates = coordinates;
		}
		else
		{
			return;
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	string input;
	cin >> input;
	generateMap(input);
	cout << "Part1: " << MaximumNumberOfDoors << endl;
	cout << "Part2: " << CoordinatesOfRoomsWithAtLeast1000Doors.size() << endl;
	return 0;
}

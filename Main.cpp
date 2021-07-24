#include <iostream>
#include <vector>
#include <string>

#include <stdlib.h>
#include <crtdbg.h>

#include "MapManager.h"

using namespace std;

// check memoty leak
struct AtExit
{
	~AtExit()
	{
		_CrtDumpMemoryLeaks();
	}
} doAtExit;

int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF || _CRTDBG_LEAK_CHECK_DF);

	vector<vector<char>> worldMap(10, vector<char>(10, 0));

	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
			cin >> worldMap[i][j];

	MapManager mm(worldMap);

	vector<pair<int, int>> path = mm.AStar(worldMap, 0, 0, 9, 9);

	vector<vector<char>> printMap = worldMap;

	for (const auto& e : path)
		printMap[e.first][e.second] = '0';

	cout << endl;
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
			cout << printMap[i][j];
		cout << "\n";
	}

	return 0;
}

/*

L : land, W : wall

LWLLLLLLLW
LWLLLWWWLW
LWLLLWWWLW
LWLLLLWWLW
LWWWWLWWLL
LLLLWLWWWL
LLWLWLWWWL
LLWLWLWWWL
LLWWWLWWWL
LLLLLLWWWL

*/
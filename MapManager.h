#pragma once

#ifndef __MapManager_H__
#define __MapManager_H__

#include <vector>
#include <string>

using std::vector;
using std::string;
using std::pair;

class MapManager
{
private:

	const int nextX[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
	const int nextY[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

	// �� ����
	vector<vector<char>> worldMap;

	// �� ũ��
	int MAP_SIZE_X;
	int MAP_SIZE_Y;

	// �Ÿ� ���ϱ�
	int GetDistance(int sx, int sy, int dx, int dy);

	// closed ��带 ������ Ű ���� �Ԥ�
	string GetKey(int x, int y);

	// �ε��� üũ
	bool CheckIndex(int x, int y);

public:

	MapManager(vector<vector<char>> _worldMap);

	vector<pair<int, int>> AStar(const vector<vector<char>>& worldMap, int sx, int sy, int dx, int dy);
};

#endif // !__MapManager_H__


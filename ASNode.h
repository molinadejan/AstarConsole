#pragma once

#ifndef __ASNODE_H__
#define __ASNODE_H__

#include <memory>

using std::shared_ptr;
using std::weak_ptr;

// A Star 알고리즘에 사용될 노드 구조체 정의
struct ASNode
{
	int x, y;		// 좌표
	int g, h;		// 비용
	shared_ptr<ASNode> parent;     // 부모노드의 좌표

	ASNode(int _x, int _y, int _g, int _h);
};

bool operator==(const shared_ptr<ASNode> n1, const shared_ptr<ASNode> n2);
bool compare(const shared_ptr<ASNode> n1, const shared_ptr<ASNode> n2);

#endif // !__ASNODE_H__


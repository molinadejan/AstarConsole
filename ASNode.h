#pragma once

#ifndef __ASNODE_H__
#define __ASNODE_H__

#include <memory>

using std::shared_ptr;
using std::weak_ptr;

// A Star �˰��� ���� ��� ����ü ����
struct ASNode
{
	int x, y;		// ��ǥ
	int g, h;		// ���
	shared_ptr<ASNode> parent;     // �θ����� ��ǥ

	ASNode(int _x, int _y, int _g, int _h);
};

bool operator==(const shared_ptr<ASNode> n1, const shared_ptr<ASNode> n2);
bool compare(const shared_ptr<ASNode> n1, const shared_ptr<ASNode> n2);

#endif // !__ASNODE_H__


#include "ASNode.h"

ASNode::ASNode(int _x, int _y, int _g, int _h)
	:x(_x), y(_y), g(_g), h(_h), parent(NULL) { }

bool operator==(const shared_ptr<ASNode> n1, const shared_ptr<ASNode> n2)
{
	return n1->x == n2->x && n1->y == n2->y;
}

bool compare(const shared_ptr<ASNode> n1, const shared_ptr<ASNode> n2)
{
	return n1->g + n1->h < n2->g + n2->h;
}
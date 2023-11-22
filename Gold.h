#pragma once
#include"Search.h"

class GoldSearch
	:public OneDimensionSearch
{

	ld eps;
public:
	GoldSearch(int _dim);
	virtual void search();
	void init(ld _a, ld _b, OneDimensionSearchFunc _target, ld eps);
	virtual void reSet(ANS _x0, ANS direction, SearchFunc _target);
};
#pragma once
#include"Search.h"

class GoldSearch
	:public OneDimensionSearch
{
public:
	GoldSearch(int _dim);
	void search();
	void init(ANS& _a, ANS& _b, SearchFunc _target, ld eps);
};
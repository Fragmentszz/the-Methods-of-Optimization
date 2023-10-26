#pragma once
#include"Search.h"

class WolfePowell
	:public OneDimensionSearch
{
	ld alpha;
	ld f0;
	ANS fp0;
	bool upperBound();
	bool lowerBound();
public:
	WolfePowell(int _dim);
	void init(ANS& _a, ANS& _b, SearchFunc _target, ld _alpha);
	void search();
};
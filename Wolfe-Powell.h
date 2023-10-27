#pragma once
#include"Search.h"

class WolfePowell
	:public OneDimensionSearch
{
	ld alpha, miu, sigma;
	ld left, right;
	ld f0;
	ld fp0;
	ANS direction;
	bool upperBound();
	bool lowerBound();
public:
	WolfePowell(int _dim);
	void init(ANS& _a, ANS& _b, SearchFunc _target, ld _alpha,ld _miu, ld _sigma);
	void search();
};
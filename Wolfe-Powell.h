#pragma once
#include"Search.h"

class WolfePowell
	:public OneDimensionSearch
{
	ANS a;
	SearchFunc targetfunc;
	ld miu, sigma;
	ld left, right;
	ld f0;
	ld fp0;
	ANS direction;
	bool upperBound();
	bool lowerBound();
public:
	WolfePowell(int _dim);
	void init(ANS& _a, ANS& _direction,ld _right, SearchFunc _target, ld _alpha,ld _miu, ld _sigma);
	virtual void reSet(ANS _x0, ANS direction, SearchFunc _target);
	void search();
	ld fmin;
};

namespace WP {
	void solve(SearchFunc);
}
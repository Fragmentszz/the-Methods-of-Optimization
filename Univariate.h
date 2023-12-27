#pragma once
#include"DerivativeMethod.h"


class Univariate
	: public DerivativeMethod
{
protected:
	int now;
	bool flag;
	void getDirection();
	ANS xn;
public:
	Univariate(int _dim, OneDimensionSearch& _Search, ANS _x0, SearchFunc _target, ld _eps);
	virtual void search();
};
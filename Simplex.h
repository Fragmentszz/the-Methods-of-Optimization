#pragma once
#include"Univariate.h"

class Simplex
	: public Univariate
{
	std::vector<ANS> X;
	std::vector<ld> fx;
public:
	Simplex(int _dim, OneDimensionSearch& _Search, ANS _x0, SearchFunc _target, ld _eps);
	void search();
};

#pragma once
#include"DerivativeMethod.h"

class ConjugateGradient
	:public DerivativeMethod
{
protected:
	ANS preDirection;
	void getDirection();
public:
	ConjugateGradient(int _dim, OneDimensionSearch& _Search, ANS _x0, SearchFunc _target, ld _eps);
};
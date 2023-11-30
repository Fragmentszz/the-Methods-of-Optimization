#pragma once
#include"ANS.h"

#include"DerivativeMethod.h"


class Newton
	:public DerivativeMethod
{
protected:
	MLDD Giv;
	void getDirection();
public:
	Newton(int _dim, OneDimensionSearch& _Search, ANS _x0, SearchFunc _target, ld _eps,MLDD Giv0);

};


#pragma once
#include"Newton.h"

class QuasiNewton
	:public Newton
{
protected:
	MLDD Giv, H;
	MLDD s, gama;
	void getDirection();
	ANS prex0;
public:
	QuasiNewton(int _dim, OneDimensionSearch& _Search, ANS _x0, SearchFunc _target, ld _eps, MLDD Giv0);
};


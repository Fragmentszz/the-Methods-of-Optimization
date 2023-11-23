#pragma once
#include"ANS.h"

class Solver
{
	ANS X0;
	ANS direction;
	SearchFunc target;
public:
	Solver(ANS _x0, ANS _direction, SearchFunc _target);
	Solver(int _dim);
	ld solve(ld _alpha);
	void set(ANS _x0, ANS _direction, SearchFunc _target);
	ANS derivative(ANS tmp);
	ANS derivative(ld _a);
};
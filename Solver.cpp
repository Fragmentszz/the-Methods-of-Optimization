#include"Solver.h"

Solver::Solver(ANS _x0, ANS _direction, SearchFunc _target)
	:X0(_x0),direction(_direction),target(_target)
{

}

Solver::Solver(int _dim)
	:X0(_dim), direction(_dim), target(nullptr)
{

}
ld Solver::solve(ld _alpha)
{
	ANS tmp = X0 + direction.Numdot(_alpha);
	return target(tmp);
}

void Solver::set(ANS _x0, ANS _direction, SearchFunc _target)
{
	X0 = _x0; direction = _direction;
	target = _target;
}

ANS Solver::derivative(ANS tmp)
{
	return _derivative(target, tmp);
}

ANS Solver::derivative(ld _a)
{
	ANS tmp = X0 + direction.Numdot(_a);
	return _derivative(target, tmp);
}
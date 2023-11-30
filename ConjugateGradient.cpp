#include"ConjugateGradient.h"

#include"Wolfe-Powell.h"

ConjugateGradient::ConjugateGradient(int _dim, OneDimensionSearch& _Search, ANS _x0, SearchFunc _target, ld _eps):
	DerivativeMethod(_dim,_Search,_x0,_target,_eps),preDirection(0)
{
	eps = _eps;
}

void ConjugateGradient::getDirection()
{
	if (nowDirection.dim == 0)
	{
		nowDerivative = _derivative(targetfunc, x0);
		nowDirection = -nowDerivative;
		return;
	}
	preDirection = nowDirection;
	ANS preDerivative = nowDerivative;
	nowDerivative = _derivative(targetfunc, x0);
	ld tmp = (nowDerivative * nowDerivative) / (preDerivative * preDerivative);
	nowDirection = -nowDerivative + preDirection.Numdot(tmp);
}


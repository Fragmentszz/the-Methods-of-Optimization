#include"DerivativeMethod.h"

#include"Wolfe-Powell.h"


			
DerivativeMethod::DerivativeMethod(int _dim, OneDimensionSearch& _Search, ANS _x0, SearchFunc _target,ld _eps) :
	dim(_dim), Search(_Search), x0(_x0), targetfunc(_target),nowDerivative(derivative(_target,_x0)),ans(_dim),nowDirection(0)
{
	eps = _eps;
	//getNewFunc();
}

//并发的时候可能会出问题
void DerivativeMethod::getNewFunc()
{
	Search.reSet(x0,nowDirection ,targetfunc);
}


void DerivativeMethod::getDirection()
{
	nowDerivative = derivative(targetfunc, x0);
	nowDirection = -nowDerivative;
}

void DerivativeMethod::search()
{
	getDirection();
	int cnt = 0;
	while (nowDerivative.norm2() > eps)
	{
		cnt++;
		fmin = targetfunc(x0);
		printf("fmin = %.6Lf  ", fmin);
		x0.print();
		getNewFunc();
		Search.search();
		x0 = Search.getAns();
		getDirection();
		if (cnt % 100 == 0)	printf("%d\n", cnt);
	}
	fmin = Search.fmin;
	printf("fmin = %.6Lf  ", fmin);
	x0.print();
	ans = x0;
}


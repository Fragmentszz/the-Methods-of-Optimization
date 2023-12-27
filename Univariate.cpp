#include"Univariate.h"
#include"XlsxWriter.h"

void Univariate::getDirection()
{
	now = (now + 1) % dim;
	for (int i = 0; i < dim; i++)
	{
		if (now == i)	nowDirection[i] = 1;
		else nowDirection[i] = 0;
	}
}

Univariate::Univariate(int _dim, OneDimensionSearch& _Search, ANS _x0, SearchFunc _target, ld _eps)
	:DerivativeMethod(_dim,_Search,_x0,_target,_eps),xn(dim)
{
	now = -1;
	flag = 0;
	nowDirection = ANS(dim);
}

void Univariate::search()
{
	XlsxWriter writer("./baogao/DerivativeMethods.xlsx", "CyclicCordinate2", Wmode::Cover);
	getDirection();
	int cnt = 0;
	while (1)
	{
		cnt++;
		fmin = targetfunc(x0);
		printf("fmin = %.6Lf  ", fmin);
		x0.print();
		writer.writeAns(x0);
		writer.write(fmin);
		nowDerivative = _derivative(targetfunc, x0);
		writer.write(nowDerivative.norm2() * nowDerivative.norm2());
		writer.nextRow();
		getNewFunc();
		Search.search();
		x0 = Search.getAns();
		if (now == dim - 1)
		{
			if (dis(xn, x0) <= eps)	break;
			xn = x0;
		}
		getDirection();
	}
	fmin = Search.fmin;
	printf("fmin = %.6Lf  ", fmin);
	x0.print();
	writer.writeAns(x0);
	writer.write(fmin);
	writer.write(nowDerivative.norm2() * nowDerivative.norm2());
	ans = x0;
}
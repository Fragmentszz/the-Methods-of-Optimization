#include"DerivativeMethod.h"

#include"Wolfe-Powell.h"
#include"XlsxWriter.h"


DerivativeMethod::DerivativeMethod(int _dim, OneDimensionSearch& _Search, ANS _x0, SearchFunc _target,ld _eps) :
	dim(_dim), Search(_Search), x0(_x0), targetfunc(_target),nowDerivative(_derivative(_target,_x0)),ans(_dim),nowDirection(0)
{
	eps = _eps;
	//getNewFunc();
}

//并发的时候可能会出问题
void DerivativeMethod::getNewFunc()
{
	ld len = nowDirection.norm2();
	//for (int i = 0; i < dim; i++)	nowDirection[i] = nowDirection[i] / len * 4;
	
	Search.reSet(x0,nowDirection ,targetfunc);
}


void DerivativeMethod::getDirection()
{
	nowDerivative = _derivative(targetfunc, x0);
	nowDirection = -nowDerivative;
}


void DerivativeMethod::search()
{
	XlsxWriter writer("./baogao/zy5.xlsx", "QuasiNewton3",Wmode::Cover);
	getDirection();
	int cnt = 0;
	while (nowDerivative.norm2() > eps)
	{
		cnt++;
		fmin = targetfunc(x0);
		printf("fmin = %.6Lf  ", fmin); x0.print();
		writer.writeAns(x0);
		writer.write(fmin);
		writer.write(nowDerivative.norm2() * nowDerivative.norm2());
		writer.nextRow();
		getNewFunc();
		Search.search();
		x0 = Search.getAns();
		getDirection();
		//printf("%.12Lf\n", nowDerivative.norm2());
	}
	
	fmin = Search.fmin;
	printf("fmin = %.6Lf  ", fmin); x0.print();
	writer.writeAns(x0);
	writer.write(fmin);
	writer.write(nowDerivative.norm2() * nowDerivative.norm2());
	ans = x0;
}


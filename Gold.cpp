#include"Gold.h"
#include"XlsxWriter.h"
const ld lamda1 = 0.5L * (3 - sqrtl(5.0L));
const ld lamda2 = 0.5L * (sqrtl(5.0L) - 1);
void GoldSearch::init(ld _a, ld _b, OneDimensionSearchFunc _target, ld _eps)
{
	eps = _eps;
	a = _a;
	b = _b;
	targetfunc = _target;
	//OneDimensionSearch::init(_a, _b, _target);
	ld mi = lamda2;
	ld d = b - a;
	for (max_iteroation = 1; mi > eps / d; max_iteroation++)
	{
		mi *= lamda2;
	}
	//printf("初始区间长d  = %.5Lf ,eps = %.5Lf ,max_iteration = %d,需要迭代 %d 轮\n", d, eps, max_iteroation, max_iteroation);
	x1 = a + (b - a) * 1.0L * lamda1, x2 = a + (b - a) * 1.0L * lamda2;
}
GoldSearch::GoldSearch(int _dim):OneDimensionSearch(_dim)
{
	
}

void GoldSearch::reSet(ANS _x0, ANS direction, SearchFunc _target)
{
	OneDimensionSearch::reSet(_x0, direction, _target);
	init(a, b, targetfunc, eps);
}

void GoldSearch::search()
{
#define targetfunc solver.solve
	fx1 = targetfunc(x1), fx2 = targetfunc(x2);
	ld tmp = 0;
	for (now_iteration = 1; now_iteration <= max_iteroation; now_iteration++)
	{
		ld tmp2 = 0;
		tmp2 = x2 - x1;
		if (tmp2 < 1e-20) {																	//防止x1和x2由于误差原因相距过近，重新算一次x1和x2
			x1 = a + (b - a) * 1.0L * lamda1, x2 = a + (b - a) * 1.0L * lamda2;
			fx1 = targetfunc(x1), fx2 = targetfunc(x2);
		}
		//printf("%d %.6Lf %.6Lf %.6Lf %.6Lf %.6Lf %.6Lf\n", now_iteration, a.alpha[0], b.alpha[0],x1.alpha[0],x2.alpha[0], fx1, fx2);
		if (fx1 < fx2) {
			b = x2;
			x2 = x1;
			fx2 = fx1;
			x1 = a + b - x2;
			fx1 = targetfunc(x1);
		}
		else {
			a = x1;
			x1 = x2;
			fx1 = fx2;
			x2 = a + b - x1;
			fx2 = targetfunc(x2);
		}
	}
	if (fx1 < fx2) {									//最后根据
		alpha = (a + x2) * 0.5;
	}
	else if (fx1 == fx2) {
		alpha = (x1 + x2) * 0.5;
	}
	else {
		alpha = (x1 + b) * 0.5;
	}
	fmin = targetfunc(alpha);
}



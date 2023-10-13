#include"Gold.h"
const ld lamda1 = 0.5L * (3 - sqrtl(5.0L));
const ld lamda2 = 0.5L * (sqrtl(5.0L) - 1);
void GoldSearch::init(ANS& _a, ANS& _b, SearchFunc _target, ld eps)
{
	OneDimensionSearch::init(_a, _b, _target);
	ld mi = lamda2;
	ld d = dis(a, b);
	for (max_iteroation = 1; mi > eps / d; max_iteroation++)
	{
		mi *= lamda2;
	}
	printf("初始区间长d  = %.5Lf ,eps = %.5Lf ,max_iteration = %d,需要迭代 %d 轮\n", d, eps, max_iteroation, max_iteroation);
	x1 = a + (b - a).Numdot(1.0L * lamda1), x2 = a + (b - a).Numdot(1.0L * lamda2);
}
GoldSearch::GoldSearch(int _dim):OneDimensionSearch(_dim)
{

}
void GoldSearch::search()
{
	fx1 = targetfunc(x1), fx2 = targetfunc(x2);
	ANS tmp(x2.dim);
	for (now_iteration = 1; now_iteration <= max_iteroation; now_iteration++)
	{
		ANS tmp2(x2.dim);
		tmp2 = x2 - x1;
		if (tmp2.ans[0] < 1e-20) {
			x1 = a + (b - a).Numdot(1.0L * lamda1), x2 = a + (b - a).Numdot(1.0L * lamda2);
			fx1 = targetfunc(x1), fx2 = targetfunc(x2);
		}
		printf("%d %.6Lf %.6Lf %.6Lf %.6Lf %.6Lf %.6Lf\n", now_iteration, a.ans[0], b.ans[0],x1.ans[0],x2.ans[0], fx1, fx2);
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
	if (fx1 < fx2) {
		ans = (a + x2).Numdot(0.5);
	}
	else if (fx1 == fx2) {
		ans = (x1 + x2).Numdot(0.5);
	}
	else {
		ans = (x1 + b).Numdot(0.5);
	}
	fmin = targetfunc(ans);
	printf("fmin = %.6Lf\n", fmin);
}
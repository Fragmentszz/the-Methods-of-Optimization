#include"parabola.h"
ANS ParabolaSearch_easy::findxb(ANS& x1,ANS& x0,ANS& x2)
{
	ANS res(1);
	res.ans[0] = (
		(fx2 * (x0.ans[0] * x0.ans[0] - x1.ans[0] * x1.ans[0]) + fx0 * (x1.ans[0] * x1.ans[0] - x2.ans[0] * x2.ans[0]) + fx1 * (x2.ans[0] * x2.ans[0] - x0.ans[0] * x0.ans[0])) / (fx2 * (x0.ans[0] - x1.ans[0]) + fx0 * (x1.ans[0] - x2.ans[0]) + fx1 * (x2.ans[0] - x0.ans[0]))
	);
	return res;
}
ParabolaSearch_easy::ParabolaSearch_easy(int _dim) :OneDimensionSearch(_dim),x0(_dim)
{

}

void ParabolaSearch_easy::init(ANS& _a, ANS& _b, SearchFunc _target,ld _eps, ANS _x0)
{
	x1 = _a; x2 = _b;
	targetfunc = _target;
	eps = _eps;
	x0 = _x0;
}
void ParabolaSearch_easy::search()
{
	fx0 = targetfunc(x0), fx1 = targetfunc(x1), fx2 = targetfunc(x2);
	ANS xb = findxb(x1, x0, x2); ld fxb = targetfunc(xb);
	while (abs(fx1 - fx2) > eps)
	{
		xb = findxb(x1, x0, x2); ld fxb = targetfunc(xb);
		printf("%.6Lf %.6Lf %.6Lf %.6Lf\n", x1, x0, x2, xb);
		if (fx0 < fxb) {
			if (x0 < xb) {
				x2 = xb; fx2 = fxb;
			}
			else {
				x1 = xb; fx1 = fxb;
			}
		}
		else {
			if (x0 < xb) {
				x1 = x0; fx1 = fx0;
				x0 = xb; fx0 = fxb;
			}
			else {
				x2 = x0; fx2 = fx0;
				x0 = xb; fx0 = fxb;
			}
		}
	}
	ans = x0; fmin = fx0;
	printf("%.6f", fmin); ans.print();
}




/*============================================= */

ANS ParabolaSearch_hard::findxb(ANS& x1, ANS& x0, ANS& x2)
{
	ANS res(1);
	res.ans[0] = (
		(fx2 * (x0.ans[0] * x0.ans[0] - x1.ans[0] * x1.ans[0]) + fx0 * (x1.ans[0] * x1.ans[0] - x2.ans[0] * x2.ans[0]) + fx1 * (x2.ans[0] * x2.ans[0] - x0.ans[0] * x0.ans[0])) / (fx2 * (x0.ans[0] - x1.ans[0]) + fx0 * (x1.ans[0] - x2.ans[0]) + fx1 * (x2.ans[0] - x0.ans[0]))
		);
	return res;
}

ParabolaSearch_hard::ParabolaSearch_hard(int _dim) :OneDimensionSearch(_dim), x0(_dim)
{

}

void ParabolaSearch_hard::init(ANS& _a, ANS& _b, SearchFunc _target, ld _eps1, ld _eps2, ANS _x0)
{
	x1 = _a; x2 = _b;
	targetfunc = _target;
	eps1 = _eps1, eps2 = _eps2;
	x0 = _x0;
}


void ParabolaSearch_hard::operatoion(ANS& xb, ld& fxb)
{
	if (abs(fx0 - fxb) < 1e-10) {
		if (x0 < xb) {
			x1 = x0; fx1 = fx0;
			x2 = xb; fx2 = fxb;
			x0 = (x1 + x2).Numdot(0.5);
			fx0 = targetfunc(x0);
		}
		else if (x0 > xb) {
			x1 = xb; fx1 = fxb;
			x2 = x0; fx2 = fx0;
			x0 = (x1 + x2).Numdot(0.5);
			fx0 = targetfunc(x0);

		}
	}
	else if (fx0 > fxb) {
		if (x0 < xb) {
			x1 = x0; fx1 = fx0;
			x0 = xb; fx0 = fxb;
		}
		else {
			x2 = x0; fx2 = fx0;
			x0 = xb; fx0 = fxb;
		}
	}
	else {
		if (x0 < xb) {
			x2 = xb; fx2 = fxb;
		}
		else {
			x1 = xb; fx1 = fxb;
		}
	}
}

void ParabolaSearch_hard::search()
{
	fx0 = targetfunc(x0), fx1 = targetfunc(x1), fx2 = targetfunc(x2);
	ANS xb = findxb(x1, x0, x2); ld fxb = targetfunc(xb);
	std::vector<ld> le1 = { eps1 }, le2 = { eps2 };
	ANS aeps1 = ANS(1, le1), aeps2 = ANS(1, le2);
	while (abs(x1 - x2) > aeps1)
	{
		if ((fx2 * (x0.ans[0] - x1.ans[0]) + fx0 * (x1.ans[0] - x2.ans[0]) + fx1 * (x2.ans[0] - x0.ans[0])) < eps2) {
			break;
		}
		xb = findxb(x1, x0, x2); fxb = targetfunc(xb);
		if (!(xb != x0))
		{
			xb = (x0 + x1).Numdot(0.5);
			fxb = targetfunc(xb);
		}
		operatoion(xb, fxb);
	}
	ans = x0, fmin = fx0;
	printf("fmin = %.6Lf  ", fmin); ans.print();
}
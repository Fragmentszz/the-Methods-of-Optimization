#include"Wolfe-Powell.h"
WolfePowell::WolfePowell(int _dim):OneDimensionSearch(_dim),fp0(_dim),direction(_dim)
{

}

bool WolfePowell::lowerBound()
{
	ANS tmp = (a + direction.Numdot(alpha));
	ld fp1 = derivative(targetfunc, tmp) * direction;
	using namespace std;
	
	cout << alpha << " " << fp0 << " " << fp1 << endl;
	if (fp1 >= fp0 * sigma)	return 1;
	return 0;
}

bool WolfePowell::upperBound()
{
	ANS tmp = (a + direction.Numdot(alpha));
	ld f1 = targetfunc(tmp);
	using namespace std;
	cout << alpha << " " << f0 << " " << f1 << " " << fp0 << endl;
	if (f0 - f1 >= -fp0 * miu * alpha)	return 1;
	return 0;
}

void WolfePowell::init(ANS& _a, ANS& _b, SearchFunc _target, ld _alpha, ld _miu, ld _sigma)
{
	OneDimensionSearch::init(_a, _b, _target);
	a = _a, b = _b, targetfunc = _target;
	alpha = _alpha;
	f0 = targetfunc(a);
	direction = (b - a).Numdot(1.0L / (b - a).norm2());
	left = 0, right = (b - a).norm2() / direction.norm2();
	fp0 = derivative(targetfunc, a) * direction;
	miu = _miu, sigma = _sigma;
}

void WolfePowell::search()
{
	while (1)
	{
		if (!upperBound()) {
			right = alpha;
			alpha = 0.5 * (left + right);
			continue;
		}
		else if (!lowerBound()) {
			left = alpha;
			alpha = std::min(0.5 * (left + right), 2 * left);
			continue;
		}
		break;
	}
	printf("%.6Lf\n", alpha);
	ans = a + direction.Numdot(alpha);
	fmin = targetfunc(ans);
	printf("fmin = %.6Lf, ",fmin); ans.print();
}
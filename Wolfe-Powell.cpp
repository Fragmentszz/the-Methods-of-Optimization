#include"Wolfe-Powell.h"
#include"XlsxWriter.h"
WolfePowell::WolfePowell(int _dim):fp0(_dim),direction(_dim),a(_dim),OneDimensionSearch(_dim)
{

}


void WolfePowell::reSet(ANS _x0, ANS direction, SearchFunc _target)
{
	OneDimensionSearch::reSet(_x0, direction, _target);
	init(_x0, direction, 100, _target, 1.0L, miu, sigma);
}
void WolfePowell::init(ANS& _a, ANS& _direction, ld _right, SearchFunc _target, ld _alpha, ld _miu, ld _sigma)
{
	left = 0, right = _right;
	direction = _direction;
	a = _a;
	targetfunc = _target;
	alpha = _alpha;
	solver.set(_a, _direction, _target);
	if (targetfunc) {
		f0 = solver.solve(0);
		fp0 = solver.derivative(a) * direction;
	}
	miu = _miu, sigma = _sigma;
}

bool WolfePowell::lowerBound()
{
	ANS tmp = (a + direction.Numdot(alpha));
	ld fp1 = solver.derivative(tmp) * direction;
	if (fp1 >= fp0 * sigma)	return 1;
	return 0;
}

bool WolfePowell::upperBound()
{
	ANS tmp = (a + direction.Numdot(alpha));
	ld f1 = solver.solve(alpha);
	using namespace std;


	if (f0 - f1 >= -fp0 * miu * alpha)	return 1;
	return 0;
}


void WolfePowell::search()
{
	//XlsxWriter xl("./baogao/third/Ans.xlsx", "WolfePowell");
	//xl.nextRow();
	//xl.write(f0); xl.write(fp0);
	using namespace std;
	direction.print();
	while (alpha > 1e-30)
	{
		//
		ANS tmp = (a + direction.Numdot(alpha));
		if (!upperBound()) {						//еп╤ой╫1
			right = alpha;
			alpha = 0.5 * (left + alpha);
			continue;
		}
		else if (!lowerBound()) {					//еп╤ой╫2
			left = alpha;
			alpha = std::min(0.5 * (alpha + right), 2 * alpha);
			continue;
		}
		break;
	}
	Ans = a + direction.Numdot(alpha);
	fmin = targetfunc(Ans);
	OneDimensionSearch::alpha = alpha;
}


void WP::solve(SearchFunc F)
{
	std::vector<ld> left = { 0.0L}, direction = {1.0L,0.0L};
	WolfePowell wp(1);
	ANS l(left), d(direction);
	ANS x0(2); x0[0] = 0, x0[1] = 0;
	wp.init(x0, d, INF, F, 1, 0.1L, 0.5L);
	wp.search();
}
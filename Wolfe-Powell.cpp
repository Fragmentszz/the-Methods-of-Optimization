#include"Wolfe-Powell.h"
WolfePowell::WolfePowell(int _dim):OneDimensionSearch(_dim)
{

}

void WolfePowell::init(ANS& _a, ANS& _b, SearchFunc _target, ld _alpha)
{
	OneDimensionSearch::init(_a, _b, _target);
	alpha = _alpha;
	f0 = targetfunc(a);
	fp0 = derivative(targetfunc, a);
}

void WolfePowell::search()
{

}
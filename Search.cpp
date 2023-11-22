#include"Search.h"


SearchFunc tmpFunc;
ANS nowDirection(1);
ANS X0(1);

/**************************/
OneDimensionSearch::OneDimensionSearch(int _dim) 
	:a(0),b(0),x1(0),x2(0),Ans(_dim),solver(_dim)
{
	dim = _dim;
}


void OneDimensionSearch::setIteroation(int _maxit)
{
	now_iteration = 0;
	max_iteroation = _maxit;
}


void OneDimensionSearch::reSet(ANS _x0, ANS direction, SearchFunc _target)
{
	tmpFunc = _target;
	X0 = _x0;
	nowDirection = direction;
	solver.set(_x0, direction, _target);
	auto cacu = [](ld _alpha) ->ld {
		ANS nowans = X0 + nowDirection.Numdot(_alpha);
		return tmpFunc(nowans);
		};
	targetfunc = cacu;
	AREA area = SearchArea(targetfunc, 0, 0.1);
	a = area[0], b = area[2];
}

ld OneDimensionSearch::getAlpha()
{
	return alpha;
}

ANS OneDimensionSearch::getAns()
{
	Ans = X0 + nowDirection.Numdot(alpha);
	return Ans;
}
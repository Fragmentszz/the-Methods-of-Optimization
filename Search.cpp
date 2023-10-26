#include"Search.h"


/**************************/
OneDimensionSearch::OneDimensionSearch(int _dim) :a(_dim),b(_dim),x1(_dim),x2(_dim),ans(_dim)
{
	dim = _dim;
}


void OneDimensionSearch::init(ANS& _a, ANS& _b,SearchFunc _target)
{
	a = _a; b = _b;
	targetfunc = _target;
}

void OneDimensionSearch::setIteroation(int _maxit)
{
	now_iteration = 0;
	max_iteroation = _maxit;
}

#pragma once
#include"df.h"
#include"Search.h"

class DerivativeMethod
{
protected:
	int dim; //解向量维度
	SearchFunc targetfunc;
	OneDimensionSearch& Search;
	ld eps;
	virtual void getDirection();
	void getNewFunc();
	ANS x0;
	ANS nowDerivative;				//当前导数
	ANS nowDirection;

public:
	DerivativeMethod(int _dim,OneDimensionSearch& _Search,ANS _x0, SearchFunc _target,ld _eps);
	//精确的
	void search();
	ANS ans;
	ld fmin;
};

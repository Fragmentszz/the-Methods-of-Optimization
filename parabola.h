#pragma once
#include"Search.h"
/// @brief 简化版抛物线二次插值求最值
class ParabolaSearch_easy
	:public OneDimensionSearch
{
protected:
	ld eps;
	ANS x0;
	ld fx0;
	ANS findxb(ANS& x1, ANS& x0, ANS& x2);
public:
	ParabolaSearch_easy(int _dim);
	void init(ANS& _a, ANS& _b, SearchFunc _target,ld _eps,ANS _x0);
	void search();
};


/// @brief 抛物线二次插值求最值
class ParabolaSearch_hard
	:public OneDimensionSearch
{
protected:
	ld eps1, eps2;
	ANS x0;
	ld fx0;
	ANS findxb(ANS& x1, ANS& x0, ANS& x2);
	void operatoion(ANS& xb,ld& fxb);
public:
	ParabolaSearch_hard(int _dim);
	void init(ANS& _a, ANS& _b, SearchFunc _target, ld _eps1,ld _eps2, ANS _x0);
	virtual void search();
};
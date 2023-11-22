#pragma once
#include"ANS.h"
#include"SearchArea.h"
#include"Solver.h"


class OneDimensionSearch
{
protected:
	int dim; //解向量维度
	OneDimensionSearchFunc targetfunc;
	int max_iteroation;		//最大迭代次数
	int now_iteration;		//当前迭代次数
	ld a, b;				//当前范围
	ld x1, x2;
	ld fx1, fx2;
	ld alpha;
	ANS Ans;
	Solver solver;
public:
	OneDimensionSearch(int _dim);
	/// @brief 初始化一维搜索
	/// @param _a :搜索起始左区间
	/// @param _b :搜索起始右区间
	/// @param _target :搜索单目标函数
	/// @ret void
	//virtual void init(ld _a, ld _b, OneDimensionSearchFunc _target);
	virtual void reSet(ANS _x0, ANS direction, SearchFunc _target);
	/// @brief 设置最大迭代次数
	/// @param _maxit 最大迭代次数
	virtual void setIteroation(int _maxit);
	ld getAlpha();
	ANS getAns();
	/// @brief 开始搜索
	virtual void search() = 0;
	ld fmin;
};




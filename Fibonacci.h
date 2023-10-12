#pragma once
#include"Search.h"
/// @brief 使用Fibonacci法求解一维搜索，最小化min
class FibonacciSearch
	:public OneDimensionSearch
{
	int nowk;
	long long fn, fn2, fn1;
public:
	FibonacciSearch(int _dim);
	/// @brief 初始化一维搜索
	/// @param _a :搜索起始左区间
	/// @param _b :搜索起始右区间
	/// @param _target :搜索单目标函数
	/// @param eps :最终区间最大长度
	/// @ret void
	void init(ANS& _a, ANS& _b, SearchFunc _target,ld eps);
	void setIteration(ld eps);

	void search();
};
#pragma once
#include"df.h"

class ANS
{
public:
	std::vector<ld> ans;
	int dim;		//解向量维度
	ANS(int _dim);
	ANS(int _dim, std::vector<ld>&);
	ANS(std::vector<ld>&);
	ANS(ANS&);
	/// @brief 计算向量的线性倍数
	/// @param k 倍数
	/// @return 
	ANS Numdot(ld k);
	ANS& operator=(const std::vector<ld>&);
	ANS& operator=(const ANS&);
	ANS operator+(const ANS&);
	ANS operator-(const ANS& b);
	friend ld dis(ANS&, ANS&);
	void print() const;
	
};

typedef ld(*SearchFunc)(const ANS&);



/// @brief 计算长度相同的向量的欧氏距离
/// @param a 
/// @param b 
/// @return 距离
ld dis(ANS& a, ANS& b);







class OneDimensionSearch
{
protected:
	int dim; //解向量维度
	SearchFunc targetfunc;
	int max_iteroation;		//最大迭代次数
	int now_iteration;		//当前迭代次数
	ANS a, b;				//当前范围
	ANS x1, x2;
	ld fx1, fx2;
	ANS ans;
	ld fmin;
public:
	OneDimensionSearch(int _dim);
	/// @brief 初始化一维搜索
	/// @param _a :搜索起始左区间
	/// @param _b :搜索起始右区间
	/// @param _target :搜索单目标函数
	/// @ret void
	virtual void init(ANS& _a, ANS& _b, SearchFunc _target);
	/// @brief 设置最大迭代次数
	/// @param _maxit 最大迭代次数
	virtual void setIteroation(int _maxit);
	/// @brief 开始搜索
	virtual void search() = 0;
};




#pragma once
#include"ANS.h"

#include"DerivativeMethod.h"


class Newton
	:public DerivativeMethod
{
protected:
	MLDD Giv;
	virtual void getDirection();
public:
	/// @brief 
	/// @param _dim 
	/// @param _Search 
	/// @param _x0 
	/// @param _target 
	/// @param _eps 
	/// @param Giv0	初始给定G的逆矩阵！
	Newton(int _dim, OneDimensionSearch& _Search, ANS _x0, SearchFunc _target, ld _eps,MLDD Giv0);

};


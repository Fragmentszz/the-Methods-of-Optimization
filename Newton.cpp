#include"Newton.h"

void Newton::getDirection()
{
	auto Rosenbrock_de = [](const ANS& x)->ANS {
		ld sum = 0;
		//if (x.dim != 10) {
		//	cout << "维数不为10!" << endl;
		//	return 0;
		//}
		ANS res(x.dim);
		for (int i = 0; i < x.dim - 1; i++)
		{
			sum += 100 * (x[i + 1] - x[i] * x[i]) * (x[i + 1] - x[i] * x[i]) + (1 - x[i]) * (1 - x[i]);
			res[i + 1] += 200 * (x[i + 1] - x[i] * x[i]);
			res[i] += -200 * x[i] * 2 * (x[i + 1] - x[i] * x[i]) + 2 * (x[i] - 1);
		}
		return res;
		};
	nowDerivative = _derivative(targetfunc, x0);
	//nowDerivative.print();
	MLDD tmp = _Hessian(targetfunc, x0);
	Giv = tmp.inverse();
	using namespace std;
	ANS tmp2 = -nowDerivative;
	nowDirection = tmp2 * Giv;
}

Newton::Newton(int _dim, OneDimensionSearch& _Search, ANS _x0, SearchFunc _target, ld _eps,MLDD Giv0)
	:DerivativeMethod(_dim,_Search,_x0,_target,_eps)
{
	Giv.resize(_dim, _dim);
	if (Giv.size() != Giv0.size())
	{
		printf("给定初始G阵大小不正确!!初始矩阵变为单位阵!\n");
		for (int i = 0; i < _dim; i++)
		{
			for (int j = 0; j < i; j++)	Giv(i, j) = 0;
			Giv(i, i) = 1;
			for (int j = i + 1; j < _dim; j++)	Giv(i, j) = 0;
		}
	}
	else 
	{
		Giv = Giv0;
	}

}
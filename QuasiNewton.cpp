#include"QuasiNewton.h"


void QuasiNewton::getDirection()
{
	auto Rosenbrock_de = [](const ANS& x)->ANS {
		ld sum = 0;

		ANS res(x.dim);
		for (int i = 0; i < x.dim - 1; i++)
		{
			sum += 100 * (x[i + 1] - x[i] * x[i]) * (x[i + 1] - x[i] * x[i]) + (1 - x[i]) * (1 - x[i]);
			res[i + 1] += 200 * (x[i + 1] - x[i] * x[i]);
			res[i] += -200 * x[i] * 2 * (x[i + 1] - x[i] * x[i]) + 2 * (x[i] - 1);
		}
		return res;
		};
	if (prex0.dim == 0)
	{
		nowDerivative = Rosenbrock_de(x0);
		nowDirection = (-nowDerivative) * H;
		prex0 = x0;
	}
	else 
	{
		ANS tmp = nowDerivative;
		nowDerivative = Rosenbrock_de(x0);
		for (int i = 0; i < dim; i++)
		{
			s(i) = x0[i] - prex0[i];
			gama(i) = nowDerivative[i] - tmp[i];
		}
		
		using namespace std;
		MLDD cof1 = gama.transpose() * H * gama, cof2 = gama.transpose() * s;
		MLDD omega;
		omega = sqrtl((gama.transpose() * H * gama)(0)) * (s / ((gama.transpose() * s)(0)) - (H * gama) / ((gama.transpose() * H * gama)(0)));

		if (cof1(0) < 1e-12 || cof2(0) < 1e-12) {
			H = Giv;
		}
		else {
			ld co1 = 1 / cof1(0), co2 = 1 / cof2(0);
			H = H - co1 * (H * gama * gama.transpose() * H.transpose()) - co2 * (s * s.transpose()) + omega * omega.transpose();
			
		}
		nowDirection = (-nowDerivative) * H;
		prex0 = x0;
		printf("%Lf\n", nowDerivative.norm2());
	}
	//nowDirection = nowDirection.Numdot(1 / nowDirection.norm2());
}

QuasiNewton::QuasiNewton(int _dim, OneDimensionSearch& _Search, ANS _x0, SearchFunc _target, ld _eps, MLDD Giv0)
	:Newton(_dim,_Search,_x0,_target,_eps,Giv0),prex0(0)
{
	s.resize(_dim, 1);
	gama.resize(_dim, 1);
	H.resize(_dim, _dim);
	H = Giv0;
	Giv = Giv0;
}
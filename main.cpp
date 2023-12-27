#include"SearchArea.h"
#include"Gold.h"

#include"XlsxWriter.h"
#include"Wolfe-Powell.h"
#include"parabola.h"
#include"DerivativeMethod.h"
#include"ConjugateGradient.h"

#include"Newton.h"
#include"QuasiNewton.h"


#include"Univariate.h"
#include"Simplex.h"
using namespace std;
vector<vector<ld>> Points;
ld func1(ld x)
{
	return x * x - 2 * x + 1;
}
ld func2(ld x)
{
	return expl(-x) + x * x;
}
ld func3(ld x)
{
	return x * x * x * x + 2 * x + 4;
}
ld func_sk(ld x)
{
	return 0;
}

int main()
{
	auto Func1 = [](const ANS& x) ->ld {
		if (x.dim != 1)
		{
			printf("输入向量长度不为1!\n");
			return 0;
		}
		return func2(x.ans[0]);
	};
	Points.push_back({ 1,1 });
	Points.push_back({ 3,4 });
	//Points.push_back({ 7,2 });
	//Points.push_back({ 6,3 });
	auto Rosenbroke = [](const ANS& x) -> ld {
		if (x.dim != 2)
		{
			printf("输入向量长度不为2!\n");
			return 0;
		}
		return 100 * (x[1] - x[0] * x[0]) * (x[1] - x[0] * x[0]) + (1 - x[0]) * (1 - x[0]);
	};

	auto dis = [](const ANS& x) ->ld {
		if (x.dim != 2)
		{
			printf("输入向量长度不为2!\n");
			return 0;
		}
		ld res = 0;
		for (int i = 0; i < Points.size(); i++)
		{
			res += (x[0] - Points[i][0]) * (x[0] - Points[i][0]) + (x[1] - Points[i][1]) * (x[1] - Points[i][1]);
		}
		return res;
	};
	auto dis2 = [](const ANS& x) ->ld {
		if (x.dim != 2)
		{
			printf("输入向量长度不为2!\n");
			return 0;
		}
		ld res = 0;
		for (int i = 0; i < Points.size(); i++)
		{
			res += sqrtl((x[0] - Points[i][0]) * (x[0] - Points[i][0]) + (x[1] - Points[i][1]) * (x[1] - Points[i][1]));
		}
		return res;
		};
	auto p1 = [](const ANS& x) -> ld {
		if (x.dim != 2)
		{
			printf("输入向量长度不为2!\n");
			return 0;
		}
		return (x[0]-2) * (x[0] - 2) * (x[0] - 2) * (x[0] - 2) + (x[0] - 2) * (x[0] - 2) * x[1]*x[1] + (x[1] + 1) * (x[1] + 1);
		};
	ANS p1x0(2);	p1x0[0] = 1, p1x0[1] = 1;
	auto p2 = [](const ANS& x) -> ld {
		if (x.dim != 2)
		{
			printf("输入向量长度不为2!\n");
			return 0;
		}
		return powl((x[1] - x[0] * x[0]), 2) + powl(x[1] - 2 * x[0] + 1, 2) + powl(x[0] + x[1] - 2, 2);
		};
	ANS p2x0(2);	p2x0[0] = -3, p2x0[1] = -3;

	GoldSearch gs(1);
	gs.init(0, 0, nullptr, 1e-8);
	//gs.search();
	//WP::solve(Func1);
	ANS x0(2);
	x0[0] = -1, x0[1] = -1;
	WolfePowell wp(2);
	wp.init(x0, x0, INF, nullptr, 1, 0.1L, 0.5L);
	DerivativeMethod dm(2, gs, x0, p2, 1e-10);
	DerivativeMethod dm2(2, wp, x0, p2, 1e-10); 
	ConjugateGradient cg1(2, gs, x0, p2, 1e-10);
	ConjugateGradient cg2(2, wp, x0, p2, 1e-10);
	auto Fuc = [](const ANS& x) -> ld{
		return x[0] * x[0] + x[1] * x[1];
	};
	MLDD G0;
	G0.resize(2,2);
	G0 << 1, 0,0,1;
	auto Rosenbrock10 = [](const ANS& x)->ld {
		ld sum = 0;
		if (x.dim != 10) {
			cout << "维数不为10!" << endl;
			return 0;
		}
		for (int i = 0; i < x.dim - 1; i++)
		{
			sum += 100 * (x[i+1] - x[i] * x[i]) * (x[i+1] - x[i] * x[i]) + (1 - x[i]) * (1 - x[i]);
		}
		return sum;
	};

	//dm2.search();
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

	
	int len = 10;
	ANS ro10x0 = ANS(len);
	
	MLDD G1;
	G1.resize(len, len);
	for (int i = 0; i < len; i++)	for (int j = 0; j < len; j++)	G1(i, j) = 0;
	for (int i = 0; i < len; i++)	G1(i, i) = 1;
	for (int i = 1; i < len; i++)	ro10x0[i] = -1;
	ro10x0[0] = -1;
	ANS test(len);
	//test[0]= 
	Newton nt(len, wp, ro10x0, Rosenbrock10, 1e-8, G1);
	QuasiNewton qnt(len, wp, ro10x0, Rosenbrock10, 1e-6, G1);
	Univariate uni(len, gs, ro10x0, Rosenbrock10, 1e-6);
	Simplex simplex(len, gs, ro10x0,Rosenbrock10, 1e-8);
	qnt.search();
	
	//ANS t = Rosenbrock_de(nt.ans);
	//t.print();
	return 0;
}
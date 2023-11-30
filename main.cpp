#include"SearchArea.h"
#include"Gold.h"

#include"XlsxWriter.h"
#include"Wolfe-Powell.h"
#include"parabola.h"
#include"DerivativeMethod.h"
#include"ConjugateGradient.h"
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
	auto p2 = [](const ANS& x) -> ld {
		if (x.dim != 2)
		{
			printf("输入向量长度不为2!\n");
			return 0;
		}
		return (x[1] - x[0] * x[0]) * (x[1] - x[0] * x[0]) + (x[1] - 2 * x[0] + 1) * (x[1] - 2 * x[0] + 1) + (x[0] + x[1] - 2) * (x[0] + x[1] - 2);
		};
	//ANS a(1, left), b(1, right), c(1, mid);
	////ParabolaSearch_easy gs(1);
	////gs.init(a, b, Func1,1e-4,c);
	////gs.search();
	////ParabolaSearch_hard gs2(1);
	////gs2.init(a, b, Func1, 1e-4, 1e-30, c);
	////gs2.search();
	GoldSearch gs(1);
	gs.init(0, 0, nullptr, 1e-4);
	//gs.search();
	//WP::solve(Func1);
	ANS x0(2);
	x0[0] = -3, x0[1] = -3;
	WolfePowell wp(2);
	wp.init(x0, x0, INF, nullptr, 1, 0.3L, 0.4L);
	DerivativeMethod dm(2, gs, x0, p2, 1e-10);
	DerivativeMethod dm2(2, wp, x0, p2, 1e-10);
	ConjugateGradient cg1(2, gs, x0, p2, 1e-10);
	ConjugateGradient cg2(2, wp, x0, p2, 1e-10);
	auto Fuc = [](const ANS& x) -> ld{
		return x[0] * x[0] + x[1] * x[1];
	};
	cout << _Hessian(Fuc, x0) << endl;
	Eigen::Vector<ld, Eigen::Dynamic> v;
	v.resize(2);
	v << 1, 2;
	cout << v << endl;
	//(x0 * _Hessian(Fuc, x0)).print();
	//dm2.search();
	//dm2.search();
	
	//cg1.search();
	//cg2.search();
	//cout << cg1.fmin << " "; cg1.ans.print();
	//cout << cg2.fmin << " "; cg2.ans.print();
	return 0;
}
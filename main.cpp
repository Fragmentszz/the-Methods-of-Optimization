#include"SearchArea.h"
#include"Gold.h"

#include"XlsxWriter.h"
#include"Wolfe-Powell.h"
#include"parabola.h"
using namespace std;
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
	//std::vector<ld> left = { -1.0L}, right = { 0.0L }, mid = {-0.0L};
	auto Func1 = [](const ANS& x) ->ld {
		if (x.dim != 1)
		{
			printf("输入向量长度不为1!\n");
			return 0;
		}
		return func2(x.ans[0]);
	};
	//auto Rosenbroke = [](const ANS& x) -> ld {
	//	if (x.dim != 2)
	//	{
	//		printf("输入向量长度不为2!\n");
	//		return 0;
	//	}
	//	return 100 * (x[1] - x[0] * x[0]) * (x[1] - x[0] * x[0]) + (1 - x[0]) * (1 - x[0]);
	//};
	//ANS a(1, left), b(1, right), c(1, mid);
	////ParabolaSearch_easy gs(1);
	////gs.init(a, b, Func1,1e-4,c);
	////gs.search();
	////ParabolaSearch_hard gs2(1);
	////gs2.init(a, b, Func1, 1e-4, 1e-30, c);
	////gs2.search();
	//GoldSearch gs(1);
	//gs.init(a, b, Func1, 1e-4);
	//gs.search();
	WP::solve(Func1);
	return 0;
}
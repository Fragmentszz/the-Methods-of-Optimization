#include"SearchArea.h"
#include"Gold.h"

#include"XlsxWriter.h"
#include"Wolfe-Powell.h"
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
	std::vector<ld> left = { 0.0L,0.0L }, right = { 3.0L,0.0L }, mid = {-0.5L};
	auto Func1 = [](const ANS& x) ->ld {
		if (x.dim != 1)
		{
			printf("输入向量长度不为1!\n");
			return 0;
		}
		return func1(x.ans[0]);
		};
	auto Rosenbroke = [](const ANS& x) -> ld {
		if (x.dim != 2)
		{
			printf("输入向量长度不为2!\n");
			return 0;
		}
		return 100 * (x[1] - x[0] * x[0]) * (x[1] - x[0] * x[0]) + (1 - x[0]) * (1 - x[0]);
		};
	ANS a(2, left), b(2, right), c(1, mid);
	WolfePowell gs(2);
	gs.init(a, b, Rosenbroke, 1,0.1,0.5);
	gs.search();
	return 0;
}
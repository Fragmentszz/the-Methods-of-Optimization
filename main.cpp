#include"SearchArea.h"
#include"Gold.h"
#include"parabola.h"

#include"XlsxWriter.h"
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
	AREA res = SearchArea(func1, 0, 0.1); 
	cout << res[0] << " " << res[1] << " " << res[2] << endl;
	std::vector<ld> left = { -1.0L }, right = { 0.0L }, mid = {-0.5L};
	auto Func1 = [](const ANS& x) ->ld {
		if (x.dim != 1)
		{
			printf("输入向量长度不为1!\n");
			return 0;
		}
		return func3(x.ans[0]);
		};
	ANS a(1, left), b(1, right), c(1, mid);
	ParabolaSearch_easy gs(1);
	gs.init(a, b, Func1, 1E-4,c);
	gs.search();
	//XlsxWriter xl("a.xlsx", "Sheet1");
	//xl(2, 3) = 1;
	//xl(6, 6) = 7.2;
	//xl(4, 3) = "11";
	return 0;
}
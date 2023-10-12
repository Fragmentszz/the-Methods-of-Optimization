#include"Fibonacci.h"

#include<OpenXLSX/OpenXLSX.hpp>
FibonacciSearch::FibonacciSearch(int _dim):OneDimensionSearch(_dim)
{

}
void FibonacciSearch::init(ANS& _a, ANS& _b, SearchFunc _target, ld eps)
{
	OneDimensionSearch::init(_a, _b, _target);
	long long fpre = 1, fnow = 1;
	ld d = dis(a, b);
	long long tmp = 0;
	for (nowk = 1; fnow < d / eps; nowk++)
	{
		tmp = fpre;
		fpre = fnow;
		fnow = tmp + fnow;
	}
	printf("初始区间长d  = %.5Lf ,eps = %.5Lf ,nowk = %d,需要迭代 %d 轮\n", d,eps,nowk, nowk - 1);
	fn = fnow, fn1 = fpre, fn2 = fnow - fpre;
	x1 = a + (b - a).Numdot(1.0L * fn2 / fn), x2 = a + (b - a).Numdot(1.0L * fn1 / fn);
}

void FibonacciSearch::search()
{
	using namespace std;
	using namespace OpenXLSX;
	auto doc = XLDocument();
	doc.open("data.xlsx");
	int cnt = 1;
	auto sheet = doc.workbook().worksheet("Sheet3");
	sheet.cell(cnt, 1).value() = "k";
	sheet.cell(cnt, 2).value() = "a";
	sheet.cell(cnt, 3).value() = "b";
	sheet.cell(cnt, 4).value() = "x1";
	sheet.cell(cnt, 5).value() = "x2";
	sheet.cell(cnt, 6).value() = "fx1";
	sheet.cell(cnt, 7).value() = "fx2";
	fx1 = targetfunc(x1), fx2 = targetfunc(x2);
	long long tmp = 0;
	
	while (nowk > 2)
	{
		++cnt;
		printf("%d %.6Lf %.6Lf %.6Lf %.6Lf %.6Lf %.6Lf\n",cnt, a.ans[0],b.ans[0],x1.ans[0],x2.ans[0],fx1, fx2);
		sheet.cell(cnt, 1).value() = cnt-1;
		sheet.cell(cnt, 2).value() = a.ans[0];
		sheet.cell(cnt, 3).value() = b.ans[0];
		sheet.cell(cnt, 4).value() = x1.ans[0];
		sheet.cell(cnt, 5).value() = x2.ans[0];
		sheet.cell(cnt, 6).value() = fx1;
		sheet.cell(cnt, 7).value() = fx2;
		fn = fn1;
		fn1 = fn2;
		fn2 = fn - fn1;
		if (fx1 < fx2) {
			b = x2;
			x2 = x1;
			fx2 = fx1;
			x1 = a + (b - a).Numdot(1.0L * fn2 / fn);
			fx1 = targetfunc(x1);
		}
		else {
			a = x1;
			x1 = x2;
			fx1 = fx2;
			x2 = a + (b - a).Numdot(1.0L * fn1 / fn);
			fx2 = targetfunc(x2);
		}
		nowk--;
	}
	++cnt;
	printf("%d %.6Lf %.6Lf %.6Lf %.6Lf %.6Lf %.6Lf\n", cnt, a.ans[0], b.ans[0], x1.ans[0], x2.ans[0], fx1, fx2);
	sheet.cell(cnt, 1).value() = cnt-1;
	sheet.cell(cnt, 2).value() = a.ans[0];
	sheet.cell(cnt, 3).value() = b.ans[0];
	sheet.cell(cnt, 4).value() = x1.ans[0];
	sheet.cell(cnt, 5).value() = x2.ans[0];
	sheet.cell(cnt, 6).value() = fx1;
	sheet.cell(cnt, 7).value() = fx2;
	if (fx1 < fx2) {
		b = x2;
		x2 = x1;
		fx2 = fx1;
	}
	else {
		a = x1;
	}
	x1 = x2 - (b - a).Numdot(0.1);
	//a.print(); x1.print(); x2.print(); b.print();
	fx1 = targetfunc(x1);
	if (fx1 < fx2) {
		ans = (a + x2).Numdot(0.5);
	}
	else if (fx1 == fx2) {
		ans = (x1 + x2).Numdot(0.5);
	}
	else {
		ans = (x1 + b).Numdot(0.5);
	}
	++cnt;
	sheet.cell(cnt, 1).value() = "Final:";
	sheet.cell(cnt, 2).value() = a.ans[0];
	sheet.cell(cnt, 3).value() = b.ans[0];
	sheet.cell(cnt, 4).value() = x1.ans[0];
	sheet.cell(cnt, 5).value() = x2.ans[0];
	sheet.cell(cnt, 6).value() = fx1;
	sheet.cell(cnt, 7).value() = fx2;
	fmin = targetfunc(ans);
	
	printf("%.5Lf ", fmin); ans.print();
	doc.save();
	doc.close();
}
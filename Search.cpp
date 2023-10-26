#include"Search.h"

ANS::ANS(int _dim)
{
	dim = _dim;
	for (int i = 0; i < dim; i++) {
		ans.push_back(0);
	}
}

ANS::ANS(int _dim, std::vector<ld>& _ans)
{
	dim = _dim;
	for (int i = 0; i < dim; i++) {
		ans.push_back(_ans[i]);
	}
}

ANS& ANS::operator=(const std::vector<ld>& _ans)
{
	if (dim != _ans.size()) {
		printf("操作失败，赋值向量和解向量大小不一致\n");
		return *this;
	}
	for (int i = 0; i < dim; i++)
	{
		ans[i] = _ans[i];
	}
	return *this;
}
ANS::ANS(std::vector<ld>& _ans):ANS(_ans.size(),_ans)
{}
ANS::ANS(const ANS& _ans)
{
	ans.clear();
	dim = _ans.dim;
	for (int i = 0; i < dim; i++) {
		ans.push_back(_ans.ans[i]);
	}
}
ANS& ANS::operator=(const ANS& _ans)
{
	return this->operator=(_ans.ans);
}


ANS ANS::operator+(const ANS& b)
{
	if (dim != b.dim) {
		printf("长度不一致的向量不能相加\n");
		return *this;
	}
	ANS tmp(dim);
	for (int i = 0; i < dim; i++)
	{
		tmp.ans[i] = ans[i] + b.ans[i];
	}
	return tmp;
}

ANS ANS::operator-(const ANS& b)
{
	if (dim != b.dim) {
		printf("长度不一致的向量不能相减\n");
		return *this;
	}
	ANS tmp(dim);
	for (int i = 0; i < dim; i++)
	{
		tmp.ans[i] = ans[i] - b.ans[i];
	}
	return tmp;
}

bool ANS::operator<(const ANS& b)
{
	if (dim != b.dim) {
		printf("不同长度的向量不能比较大小\n");
		return 0;
	}
	for (int i = 0; i < dim; i++)
	{
		if (ans[i] >= b.ans[i]) {
			return 0;
		}
	}
	return 1;
}

bool ANS::operator>(const ANS& b)
{
	if (dim != b.dim) {
		printf("不同长度的向量不能比较大小\n");
		return 0;
	}
	for (int i = 0; i < dim; i++)
	{
		if (ans[i] < b.ans[i] || fabsl(ans[i] - b.ans[i]) < INS ) {
			return 0;
		}
	}
	return 1;
}

bool ANS::operator>=(const ANS& b)
{
	if (dim != b.dim) {
		printf("不同长度的向量不能比较大小\n");
		return 0;
	}
	for (int i = 0; i < dim; i++)
	{
		if (ans[i] < b.ans[i]) {
			return 0;
		}
	}
	return 1;
}
bool ANS::operator<=(const ANS& b)
{
	if (dim != b.dim) {
		printf("不同长度的向量不能比较大小\n");
		return 0;
	}
	for (int i = 0; i < dim; i++)
	{
		if (ans[i] > b.ans[i]) {
			return 0;
		}
	}
	return 1;
}

bool ANS::operator!=(const ANS& b)
{
	if (dim != b.dim) {
		printf("不同长度的向量不能比较大小\n");
		return 1;
	}
	for (int i = 0; i < dim; i++)
	{
		if (fabsl(ans[i] - b.ans[i]) > INS) {
			return 1;
		}
	}
	return 0;
}

ld& ANS::operator[](int index)
{
	return ans[index];
}

ANS abs(ANS a)
{
	ANS tmp(a.dim);
	for (int i = 0; i < a.dim; i++)
		tmp[i] = abs(a[i]);
	return tmp;
}


ANS ANS::Numdot(ld k)
{
	ANS tmp(dim);
	for (int i = 0; i < dim; i++) {
		tmp.ans[i] = ans[i] * k;
	}
	return tmp;
}

ld dis(ANS& a, ANS& b)
{
	if (a.dim != b.dim) {
		printf("两向量长度不一致，不能计算距离\n");
		return INFINITY;
	}
	ld res = 0;
	for (int i = 0; i < a.dim; i++) {
		res += (a.ans[i] - b.ans[i]) * (a.ans[i] - b.ans[i]);
	}
	return sqrtl(res);
}


void ANS::print() const
{
	printf("(");
	for (int i = 0; i < dim -1; i++) {
		printf("%.6Lf,", ans[i]);
	}
	printf("%.6Lf)\n", ans[dim - 1]);
}

/**************************/
OneDimensionSearch::OneDimensionSearch(int _dim) :a(_dim),b(_dim),x1(_dim),x2(_dim),ans(_dim)
{
	dim = _dim;
}


void OneDimensionSearch::init(ANS& _a, ANS& _b,SearchFunc _target)
{
	a = _a; b = _b;
	targetfunc = _target;
}

void OneDimensionSearch::setIteroation(int _maxit)
{
	now_iteration = 0;
	max_iteroation = _maxit;
}

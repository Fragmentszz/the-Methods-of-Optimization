#include"ANS.h"

ANS::ANS(int _dim)
{
	dim = _dim;
	for (int i = 0; i < dim; i++) {
		ans.push_back(0);
	}
}

ld ANS::norm2()
{
	ld res = 0;
	for (int i = 0; i < dim; i++) {
		res += ans[i] * ans[i];
	}
	return sqrtl(res);
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
	dim = _ans.size();
	ans.resize(dim);
	for (int i = 0; i < dim; i++)
	{
		ans[i] = _ans[i];
	}
	return *this;
}
ANS::ANS(std::vector<ld>& _ans) :ANS(_ans.size(), _ans)
{}

ld ANS::operator*(const ANS& b)
{
	ld res = 0;
	if (b.dim != dim) {
		printf("长度不一样的向量不能内积！\n");
		return res;
	}
	for (int i = 0; i < dim; i++)
	{
		res += ans[i] * b.ans[i];
	}
}
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

ANS ANS::operator-()
{
	ANS tmp(dim);
	for (int i = 0; i < dim; i++)
	{
		tmp.ans[i] = -ans[i];
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
		if (ans[i] < b.ans[i] || fabsl(ans[i] - b.ans[i]) < INS) {
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
ld ANS::operator[](int index) const
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
	for (int i = 0; i < dim - 1; i++) {
		printf("%.6Lf,", ans[i]);
	}
	printf("%.6Lf)\n", ans[dim - 1]);
}




ANS _derivative(SearchFunc target, ANS& x)
{
	ANS res(x.dim);
	for (int i = 0; i < x.dim; i++)
	{
		ANS tmp1(x), tmp2(x);
		tmp1[i] += delta / 2; tmp2[i] -= delta / 2;
		res[i] = (target(tmp1) - target(tmp2)) / delta;
	}
	return res;
}


MLDD _Hessian(SearchFunc target, ANS& x)
{
	MLDD m;
	m.resize(x.dim, x.dim);
	ANS tmp(x.dim);
	for (int i = 0; i < x.dim; i++)
	{
		ANS tmp1(x), tmp2(x);
		tmp1[i] = x[i] + delta;
		tmp2[i] = x[i] + delta;
		for (int j = 0; j < i; j++)
		{
			tmp1[j] = x[j] + delta;
			ANS tmp3(x), tmp4(x);
			tmp3[j] = x[j] + delta;
			m(i, j) = (target(tmp1) - target(tmp2) - target(tmp3) + target(tmp4)) / delta / delta;
			tmp1[j] = x[j];
		}
		tmp2[i] = x[i] - delta;
		m(i, i) = (target(tmp1) + target(tmp2) - 2 * target(x)) / delta / delta;
		tmp2[i] = x[i] + delta;
		for (int j = i + 1; j < x.dim; j++)
		{
			tmp1[j] = x[j] + delta;
			ANS tmp3(x), tmp4(x);
			tmp3[j] = x[j] + delta;
			m(i, j) = (target(tmp1) - target(tmp2) - target(tmp3) + target(tmp4)) / delta / delta;
			tmp1[j] = x[j];
		}
	}
	return m;
}


ANS operator* (const ANS& x,const MLDD& m)
{
	if (m.cols() != x.dim) {
		printf("相乘时矩阵列和向量行大小不一致");
		return ANS(x.dim);
	}
	Eigen::Vector<ld, Eigen::Dynamic> v,ans;
	v.resize(x.dim);
	for (int i = 0; i < x.dim; i++)	v(i) = x[i];
	ANS res(x.dim);
	ans = m * v;
	for (int i = 0; i < x.dim; i++)	res[i] = ans(i);
	return res;
}

MLDD operator*(ld bs, const MLDD& m)
{
	MLDD tmp;
	tmp.resize(m.rows(), m.cols());
	for (int i = 0; i < m.rows(); i++)
	{
		for (int j = 0; j < m.cols(); j++)
		{
			tmp(i, j) = m(i, j) * bs;
		}
	}
	return tmp;
}
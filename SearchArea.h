#pragma once
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>
typedef long double ld;
typedef std::pair<ld, ld> PLL;
typedef std::vector<ld> ANS;
#define MAXDELTA 1e8
typedef ld(*FUNC)(ld);

ANS SearchArea(FUNC f,ld _x0,ld _deltax0ccdx);
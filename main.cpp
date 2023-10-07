#include"SearchArea.h"
#include<iostream>
using namespace std;
int main()
{
	auto func1 = [](ld x) ->ld {return x * x - 2 * x + 1; };
	auto func2 = [](ld x) ->ld {return expl(-x) + x * x; };
	auto func3 = [](ld x) ->ld {return x * x * x * x + 2 * x + 4; };
	ANS res = SearchArea(func3, 0, 0.1);
	cout << res[0] << " " << res[1] << " " << res[2] << endl;
	return 0;
}
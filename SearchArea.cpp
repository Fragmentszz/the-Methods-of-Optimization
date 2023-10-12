#include"SearchArea.h"
AREA SearchArea(FUNC f, ld _x0, ld _deltax0)
{
	ld x0 = _x0, x1 = _x0 + _deltax0, x2 = 0, deltax = _deltax0;
	ld fx0 = f(x0), fx1 = f(x1), fx2 = 0;
	if (fx0 > fx1){
		while (deltax < MAXDELTA)
		{
			deltax *= 2;
			x2 = x1 + deltax;
			fx2 = f(x2);
			if (fx2 > fx1) {
				return { x0,x1,x2};
			}
			x0 = x1; x1 = x2;
			fx0 = fx1; fx1 = fx2;
		}
	}else {
		while (deltax < MAXDELTA)
		{
			deltax *= 2;
			x2 = x0 - deltax;
			fx2 = f(x2);
			if (fx2 > fx0) {
				return { x2,x0,x1 };
				break;
			}
			x1 = x0; x0 = x2;
			fx1 = fx0; fx0 = fx2;
		}
	}
	return { };
}
#include"Simplex.h"
#include"XlsxWriter.h"
Simplex::Simplex(int _dim, OneDimensionSearch& _Search, ANS _x0, SearchFunc _target, ld _eps)
	:Univariate(_dim, _Search, _x0,_target,_eps)
{
	X.push_back(_x0);
	fx.resize(_dim + 1);
	for (int i = 1; i <= _dim; i++)
	{
		ANS tmp(dim);
		tmp[i - 1] = 1;
		X.push_back(tmp + _x0);
		
	}
}


void Simplex::search()
{
	ANS tmp(dim);
	ld Fav = 0;
	XlsxWriter writer("./baogao/zy5.xlsx", "Simplex", Wmode::Cover);
	while (1) 
	{
		ld Fmin = INF, Fmax1 = -INF, Fmax2 = -INF;
		int idmin = -1, idmax1 = -1, idmax2 = -1;
		for (int i = 0; i < dim; i++)	tmp[i] = 0;
		for (int i = 0; i <= dim; i++)
		{
			fx[i] = targetfunc(X[i]);
			if (fx[i] < Fmin) {
				Fmin = fx[i];
				idmin = i;
			}
			if (fx[i] >= Fmax1)	
			{
				Fmax2 = Fmax1; idmax2 = idmax1;
				Fmax1 = fx[i]; idmax1 = i;
			}
			else if (fx[i] >= Fmax2)
			{
				Fmax2 = fx[i];
				idmax2 = i;
			}
			tmp = tmp + X[i];
		}
		fmin = Fmin;
		ans = X[idmin];
		tmp = tmp - X[idmax1];
		tmp = tmp.Numdot(1.0L / (dim));
		Fav = targetfunc(tmp);
		printf("fmin = %.6Lf  ", fmin);
		x0.print();
		writer.writeAns(x0);
		writer.write(fmin);
		writer.write(nowDerivative.norm2() * nowDerivative.norm2());
		writer.nextRow();
		if (idmin == idmax1 || idmin == idmax2 || idmax1 == idmax2)	printf("?\n");
		ld error = 0;
		for (int i = 0; i <= dim; i++)
		{
			error += (Fav - fx[i]) * (Fav - fx[i]);
		}
		error = sqrtl(error / (dim + 1));
		//printf("%.6Lf\n", error);
		if (error < eps)	break;
		ANS Xm(dim);
		Xm = tmp.Numdot(2) - X[idmax1];
		ld FXm = targetfunc(Xm);
		bool flag = 0;
		if (FXm < Fmin)
		{
			ANS Xe = Xm.Numdot(2) - tmp;
			ld FXe = targetfunc(Xe);
			if (FXe < Fmin) {
				Xm = Xe;
				FXm = FXe;
			}
		}
		else {
			if (FXm < Fmax2) {
				;
			}
			else 
			{
				if (FXm < Fmax1)
				{
					ANS Xc = (Xm - tmp).Numdot(0.5) + tmp;
					ld FXc = targetfunc(Xc);
					if (FXc < Fmax1)
					{
						Xm = Xc;
						FXm = FXc;
					}
					else {
						flag = 1;
					}
				}
				else 
				{
					ANS Xc = (X[idmax1] - tmp).Numdot(0.5) + tmp;
					ld FXc = targetfunc(Xc);
					if (FXc < Fmax1)
					{
						Xm = Xc;
						FXm = FXc;
					}
					else {
						flag = 1;
					}
				}
			}
		}
		if (flag)
		{
			//printf("o\n");
			for (int i = 0; i <= dim; i++)
			{
				if (i == idmin)	continue;
				X[i] = (X[i] + X[idmin]).Numdot(0.5);
			}
		}
		else 
		{
			X[idmax1] = Xm;
			fx[idmax1] = FXm;
		}
		if (fx[idmax1] < fmin)
		{
			fmin = fx[idmax1];
			ans = X[idmax1];
		}
	}
	printf("fmin = %.6Lf  ", fmin);
	x0.print();
	writer.writeAns(x0);
	writer.write(fmin);
	writer.write(nowDerivative.norm2()* nowDerivative.norm2());
}
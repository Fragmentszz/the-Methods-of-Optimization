#include"DerivativeMethod.h"

DerivativeMethod::DerivativeMethod(int _dim, OneDimensionSearch& _Search, ANS _x0, SearchFunc _target) :dim(_dim), Search(_Search), x0(_x0), targetfunc(_target)
{

}
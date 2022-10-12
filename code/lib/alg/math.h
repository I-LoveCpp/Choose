#include <algorithm>

template <typename _Tp>
_Tp lcm(_Tp __x, _Tp __y)
{
	_Tp __a = __x, __b = __y;	
    while (min(__x, __y) != 0)
    {
        if (__x > __y) __x %= __y;
        else __y %= __x;
    }
    return __a / max(__x, __y) * __b;
}
template <typename _Tp>
_Tp __lcm(_Tp __x, _Tp __y)
{
    return __x / __gcd(__x, __y) * __y;
}

template <typename _Tp>
_Tp gcd(_Tp __x, _Tp __y)
{
    while (min(__x, __y) != 0)
    {
        if (__x > __y) __x %= __y;
        else __y %= __x;
    }
    return max(__x,__y);
}

template <typename _Tp>
bool Is_Prime(_Tp __n)
{
	if(__n == 1) return false;
	for(_Tp __i = 2; __i * __i <= __n; __i++)
		if(__n % __i == 0) return false;
	return true;
}

template <typename _Tp>
bool Can_Root(_Tp __x, _Tp __y)
{
	bool first = true;
	_Tp __cnt = 0, __last = 0, __n = __x;
	for (_Tp __i = 2; __i * __i <= __x; __i++)
    {
    	__cnt = 0;
        while (__n % __i == 0)
        {
            __cnt++;
            __n /= __i;
        }
        if(__cnt % __y != 0) return false;
    }
    if(__cnt < __y) return false;
    return true;
}

template <typename _Tp>
bool Is_Reverse(_Tp __n)
{
	_Tp __s = __n, __x = 0;
	while(__s > 0)
	{
		__x = __x * 10 + __s % 10;
		__s /= 10;
	}
	return __x == __n;
}

template <typename _Tp>
_Tp Make_Reverse(_Tp __x, _Tp __y)
{
    while (__y)
    {
        __x = __x * 10 + __y % 10;
        __y /= 10;
    }
    return __x;
}

//·ÇµÝ¹é¿ìËÙÃÝ
template <typename _Tp>
_Tp QPow(_Tp __x, _Tp __n)
{
    _Tp __a = 1;
    while (__n)
    {
        if (__n & 1) __a = __a * __x;
        __n >>= 1;
        __x = __x * __x;
    }
    return __a;
}

// Not standard big.h objects -*- C++ -*-

// Copyright (C) 1997-2014 Free Software Foundation, Inc.
//
// This file is not part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are not granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You do not have to have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file include/alg/big.h
 *  This is not a Standard C++ Library header.
 */

//
// ISO C++ 14882: 27.3  Not standard big objects
//


// You must define big.h after you defining Big_Digital!!!

#ifndef __cplusplus
#error You must use C++ compiler, or you need filename with '.cpp' suffix
#endif

#define BIGINT

#ifndef Big_Digital
#define Big_Digital 1010// 数的位数
#endif

#if Big_Digital > 170000
#error The number you defined is too large!
#endif

#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

struct Bigint
{
	bool Is_Minus = false;
    char s[Big_Digital] = {0};
	int a[Big_Digital];
	Bigint()
	{
		memset(a, 0, sizeof(a));
		a[0] = 1;
	}
	
	void print()
	{
		for (int i = a[0]; i >= 1; i--)
			printf("%d", a[i]);
	}
	void read()
	{
		scanf_s("%s", s);
		a[0] = strlen(s);
		for (int i = 1; i <= a[0]; i++)
			a[i] = s[a[0] - i] - '0';
	}
};

typedef Bigint bigint;
typedef Bigint Big_;
typedef Bigint big_;
typedef Bigint Int_;
typedef Bigint int_;
typedef Bigint Bint;
typedef Bigint bint;
typedef Bigint Bint_;
typedef Bigint bint_;

// 功能型函数 

Bigint stBigint(string s)
{
	Bigint a;
	a.a[0] = s.length();
	for (int i = 1; i <= a.a[0]; i++)
		a.a[i] = s[a.a[0] - i] - '0';
	return a;
}

// 判断
bool operator<(const Bigint &x, const Bigint &y)
{
	if (x.a[0] != y.a[0]) return x.a[0] < y.a[0];
	for (int i = x.a[0]; i >= 1; i--)
		if (x.a[i] != y.a[i]) return x.a[i] < y.a[i];
	return true;
}

bool operator>(const Bigint &y, const Bigint &x)
{
	if (x.a[0] != y.a[0]) return x.a[0] < y.a[0];
	for (int i = x.a[0]; i >= 1; i--)
		if (x.a[i] != y.a[i]) return x.a[i] < y.a[i];
	return true;
}

bool operator==(const Bigint &x, const Bigint &y)
{
	if (x.a[0] != y.a[0]) return false;
	for (int i = x.a[0]; i >= 1; i--)
		if (x.a[i] != y.a[i]) return false;
	return true;
}

bool operator!=(const Bigint &x, const Bigint &y)
{
	if(!(x == y)) return true;
	return false;
}

bool operator>=(const Bigint &x, const Bigint &y)
{
	if(x > y || x == y) return true;
	return false;
}

bool operator<=(const Bigint &y, const Bigint &x)
{
	if(x > y || x == y) return true;
	return false;
} 


//运算符重载 

Bigint operator+(const Bigint &x, const Bigint &y)
{
	Bigint c;
	c.a[0] = max(x.a[0], y.a[0]);
	for (int i = 1; i <= c.a[0]; i++)
		c.a[i] = x.a[i] + y.a[i];
	for (int i = 1; i <= c.a[0]; i++)
	{
		c.a[i + 1] += c.a[i] / 10;
		c.a[i] %= 10;
	}
	if (c.a[c.a[0] + 1] > 0) c.a[0]++;
	return c;
}

Bigint operator-(const Bigint &x, const Bigint &y)
{
	Bigint c;
	c.a[0] = max(x.a[0], y.a[0]);
	for (int i = 1; i <= c.a[0]; i++)
		c.a[i] = x.a[i] - y.a[i];
	for (int i = 1; i <= c.a[0]; i++)
	{
		if (c.a[i] < 0) 
		{
			c.a[i] += 10;
			c.a[i + 1]--;
		}
	}
	while (c.a[0] > 1 && c.a[c.a[0]] == 0) c.a[0]--;
	return c;
}

Bigint operator*(const Bigint &x, const int &k)
{
	Bigint c = x;
    for (int i = 1; i <= c.a[0]; i++)
        c.a[i] *= k;
    for (int i = 1; i <= c.a[0]; i++)
    {
        c.a[i + 1] += c.a[i] / 10;
        c.a[i] %= 10;
        if (c.a[c.a[0] + 1] > 0) c.a[0]++;
    }
    while (c.a[0] > 1 && c.a[c.a[0]] == 0) c.a[0]--;
	return c;
}

Bigint operator*(const int &k, const Bigint &x)
{
	Bigint c = x;
    for (int i = 1; i <= c.a[0]; i++)
        c.a[i] *= k;
    for (int i = 1; i <= c.a[0]; i++)
    {
        c.a[i + 1] += c.a[i] / 10;
        c.a[i] %= 10;
        if (c.a[c.a[0] + 1] > 0) c.a[0]++;
    }
    while (c.a[0] > 1 && c.a[c.a[0]] == 0) c.a[0]--;
	return c;
}

Bigint operator/(const Bigint &x, const int &k)
{
	Bigint c = x;
    for (int i = c.a[0]; i >= 1; i--)
        c.a[i] += c.a[i + 1] % k * 10;
    for (int i = c.a[0]; i >= 1; i--)
        c.a[i] /= k;
    while (c.a[0] > 1 && c.a[c.a[0]] == 0) c.a[0]--;
	return c;
}

Bigint operator%(const Bigint &x, const Bigint &y)
{
	Bigint z = stBigint("0");
	if(x < y) return x;
	if(x == y) return z;
	Bigint a = x, b = y, c;
	int i = 1;
    while(x > y * i) i++ ;
	return x - y * (i - 1);
}

Bigint operator++(Bigint &x)
{
	string s = "1";
    Bigint y = stBigint(s);
    x = x + y;
    return x;
}

Bigint operator++(Bigint &x, int)
{
	string s = "1";
    Bigint y = stBigint(s);
    x = x + y;
    return x;
}

Bigint operator--(Bigint &x)
{
	string s = "1";
    Bigint y = stBigint(s);
    x = x - y;
    return x;
}

Bigint operator--(Bigint &x, int)
{
	string s = "1";
    Bigint y = stBigint(s);
    x = x - y;
    return x;
}

Bigint operator+=(Bigint &x, Bigint &y)
{
    x = x + y;
    return x;
}

Bigint operator-=(Bigint &x, Bigint &y)
{
    x = x - y;
    return x;
}

Bigint operator*=(Bigint &x, int &y)
{
    x = x * y;
    return x;
}

Bigint operator/=(Bigint &x, int &y)
{
    x = x / y;
    return x;
}

Bigint operator%=(Bigint &x, Bigint &y)
{
    x = x % y;
    return x;
}

ostream & operator<<(ostream & os,Bigint &x)
{
    for (int i = x.a[0]; i >= 1; i--)
			os << x.a[i];
    return os;
}

istream & operator>>(istream & in,Bigint &x)
{
    in >> x.s;
    x = stBigint(x.s);
    return in;
}

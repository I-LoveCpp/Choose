#include <iostream>
#include <cmath>

using namespace std;


template <typename T>
string a_to_string(T x)
{
	T n = abs(x);
	string s = "", r = "";
	while(n > 0)
	{
		s += n % 10 + '0';
		n /= 10;
	}
	if(x < 0) s += "-";
	for(long long i = s.length() - 1; i >= 0; i--)
	{
		r += s[i];
	}
	return r;
}

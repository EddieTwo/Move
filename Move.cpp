#include <iostream>
#include <vector>

using namespace std;

vector<int> doubleValues(const vector<int>& v)
{
	vector<int> vd;
	for (auto& foo : v)
		vd.push_back(2 * foo);

	return vd;
}

int main()
{
	vector<int> v = { 1, 4, 9, -2, -12, 11, };
	vector<int> vd = doubleValues(v);

	return 0;
}
#include <iostream>
#include <vector>

using namespace std;

class TestClass
{
	int _i;
	string _str;
public:
	TestClass(int i, const string& str): _i(i), _str(str) {}
	
	TestClass(const TestClass& tc): _i(tc._i), _str(tc._str) 
	{
		cout << "copy constructor" << endl;
	}

	TestClass(TestClass&& tc): _i(tc._i), _str(move(tc._str)) 
	{
		cout << "move constructor" << endl;
	}

	TestClass& operator=(const TestClass& tc)
	{
		_i = tc._i;
		_str = tc._str;
		cout << "copy assignment operator" << endl;

		return *this;
	}

	TestClass& operator=(TestClass&& tc)
	{
		_i = tc._i;
		_str = move(tc._str);
		cout << "move assignment operator" << endl;

		return *this;
	}

};

vector<int> doubleValues(const vector<int>& v)
{
	vector<int> vd;
	for (auto& foo : v)
		vd.push_back(2 * foo);

	return vd;
}

int main()
{
	// 
	vector<int> v = { 1, 4, 9, -2, -12, 11, };
	vector<int> vd = doubleValues(v);

	vd = v;
	vd = ref(v);

	// bespoke class
	TestClass tc(1, "test");
	TestClass tc2 = tc;

	return 0;
}
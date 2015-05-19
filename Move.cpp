#include <iostream>
#include <vector>

#include <type_traits>

using namespace std;

vector<int> doubleValues(const vector<int>& v)
{
	vector<int> vd;
	for (auto& foo : v)
		vd.push_back(2 * foo);

	return vd;
}

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

	void increment()
	{
		++_i;
	}

};

TestClass modifyTestClass(const TestClass& tc)
{
	TestClass tc1 = tc;
	tc1.increment();
	//cout << "-------a2------\n";
	return tc1;
}

class SmallClass
{
	int _i;
public:
	SmallClass(int i) noexcept : _i(i) {}
	SmallClass(const SmallClass& sc) noexcept : _i(sc._i)
	{

	}

	SmallClass(SmallClass&& sc) noexcept : _i(sc._i)
	{

	}

	SmallClass& operator=(const SmallClass& sc) noexcept
	{
		_i = sc._i;
		return *this;
	}

	SmallClass& operator=(SmallClass&& sc) noexcept
	{
		_i = sc._i;
		return *this;
	}
};

int main()
{
	// vector of int's
	vector<int> v = { 1, 4, 9, -2, -12, 11, };
	vector<int> vd = doubleValues(v);

	vd = v;
	vd = ref(v);

	// noexcept
	cout << v._Mylast() << "\t" << v._Myend() << "\t" << v._Myend() - v._Mylast()  << endl;
	v.push_back(10);
	cout << v._Mylast() << "\t" << v._Myend() << "\t" << v._Myend() - v._Mylast()  << endl;
	v.push_back(11);
	cout << v._Mylast() << "\t" << v._Myend() << "\t" << v._Myend() - v._Mylast()  << endl;

	// bespoke class with move syntax
	TestClass tc(1, "test");
	TestClass tc2 = tc;
	TestClass tc3 = ref(tc);
	TestClass tc4 = move(tc);

	tc3 = tc;
	tc3 = ref(tc);
	tc4 = move(tc);

	cout << "-------a1------\n";
	tc2 = modifyTestClass(tc);

	// type traits
	int i = 56;
	int* pi = &i;
	//pointer_traits<pi>::element_type j = 66;

	return 0;
}
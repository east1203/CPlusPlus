#include<iostream>
#include<stdlib.h>


using namespace std;
using std::cout;
using std::endl;
#include "../../../mycase/cases.h"
using namespace COUNT;
class test {
public:
	test(int a):n(a){}
	test(test& t):n(t.n){}
	test(){}
	void set(int n) { this->n = n; }
	int get() { return n; }
	test& operator= (test& m)
	{
		n = m.n;
		return *this;
	}
	friend ostream& operator<<(ostream& os, test& t)
	{
		return os << t.n;
		
	}

	
private:
	int n;
};
int main(void)
{
	test t1(1), t2(2);
	cout << t1.get() << "   " << t2.get() << endl;
	
	SmPt<test> s1(test(1));
	SmPt<test> s2 (s1);
	s1.get()->set(10);
	cout << *s1.get() << endl;
	cout << *s2.get() << endl;

	system("pause");
	return 0;
}
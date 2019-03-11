
#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;
#include "../../../mycase/cases.h"
using namespace My_Code;
using namespace IO;
/*如果定义在cases.h中出错，识别不了My_String 类型*/
template<class T> T& operator<<(T& io, const My_String& str)
{
	sendstr(io, str.c_str(), str.size());
	return io;
}
//IOStream& operator <<(IOStream& io, const My_String& str)
//{
//	sendstr(io, str.c_str(), str.size());
//	return io;
//}
void test1()
{
	static My_String str("this is a test!");
	OStream Out;
	Out << str;
	/*测试iostream输出My_String*/
	cout << str << endl;;
	/*测试输出到文件*/
	FileOStream Fout("1.txt","w+");
	Fout << str;
	Fout.close();
	/*测试打印自定义类型MInt*/
	MInt m(0);
	cout << m << endl;
	cout << "enter a integer :" << endl;
	cin >> m;
	cout << m << endl;
	writetofile1();
	writetofile2();
	writefromfile1();
}

void testFILE()
{
	ofstream fp("1.txt");
	char* ch = "this is a test !";

}




int main(void)
{
	test1();
	system("pause");
	return 0;
}


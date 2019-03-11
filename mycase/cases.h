#pragma once

// **** 2019 - 03 - 10 ******//
//******** 这个文件中的内容是在学习中遇到的小例子 ********//

#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#include<stdio.h>
using namespace std;


/* 打印菱形 */
void PrintRhombus();
/*输入时针数和分针数，输出时针和分针之间的度数
	24小时计时方式
*/
void CalculateAngle();
/* 用类来实现计算度数，体现OO思想*/
namespace Clock {
	class clock {
	public:
		clock();
		~clock();
		clock& seth(int);
		clock& setm(int);
		int geth();
		int getm();
		void cal();  //计算角度
		void show();
		void run();
	private:
		int m_h;
		int m_m;
		double diff;

	};
}


/*自定义的明明空间*/
/* ***** 包括 *********/
/*SpreadSheetCell单元格类*/
namespace My_Code {
	/* 一个单元格的类 */
	class SpreadSheetCell
	{
	public:
		SpreadSheetCell();
		SpreadSheetCell(string str);
		SpreadSheetCell(double initvalue);
		SpreadSheetCell(const SpreadSheetCell&);
		~SpreadSheetCell();
		SpreadSheetCell& operator=(const SpreadSheetCell&);
		SpreadSheetCell& operator+(const SpreadSheetCell&);
		void SetDoubleValue(const double doublevalue);
		void SetStringValue(const string stringvlaue);
		double GetDoubleValue();
		string& GetStringValue();
		
	protected:
		double stringtodouble(const string str);
		string doubletostring(double value);
		double m_value;
		string m_Str;
	};
	/* 电子表格类 */
	class SpreadSheetData
	{
	public:
		static const int defaultwidth = 100;
		static const int defaulthigh = 100;
		SpreadSheetData(int width, int high);
		SpreadSheetData(SpreadSheetData &Data);
		virtual ~SpreadSheetData();
		SpreadSheetData& operator=(const SpreadSheetData &Data);
		void SetCellAt(int x, int y, const SpreadSheetCell& Cell);
		SpreadSheetCell GetCell(int x, int y);
		void test();
	protected:
		bool inRang(int val, int upper);
		void CopyFrom(const SpreadSheetData & Data);
		int m_width, m_high;
		SpreadSheetCell **m_Cell;
	};
	class SpreadSheet
	{
	public:
		SpreadSheet(int width, int high);
		SpreadSheet(const SpreadSheet &Data);
		virtual ~SpreadSheet();
		SpreadSheet& operator=(const SpreadSheet &Data);
		void SetCellAt(int x, int y, const SpreadSheetCell& Cell);
		SpreadSheetCell GetCelld(int x, int y);
		void test();
	protected:
		SpreadSheetData *m_Data;
	};
	class My_String {
	public:
		My_String();
		My_String(const char* str);
		My_String(const My_String&);
		~My_String();
		int length()const
		{
			return m_len;
		}
		My_String& operator=(const My_String&);
		My_String& operator=(const char*);
		char& operator[](int i);
		const char& operator[](int i) const;
		friend bool operator<(const My_String& str1, const My_String& str2);
		friend bool operator>(const My_String& str1, const My_String& str2);
		friend bool operator==(const My_String& str1, const My_String& str2);
		friend ostream& operator<<(ostream &os, const My_String &str);
		friend istream& operator >> (istream &is, My_String &str);
		int size () const{ return strlen(m_str); }   //const成员函数，不会改变对象
		char* c_str() const { return m_str; }
	private:
		char* m_str;
		int m_len;
	};
}
/* 自定义IO流 */
namespace IO {
	class MyStrIobase {
	public:
		virtual ~MyStrIobase() {}
		virtual void send(const char* ptr, int n) {}
	};
	void sendstr(MyStrIobase& strio, const char* ptr, int n);

	/*输出到控制台 ，stdout是标准C的控制台，std::cout是C++流对象，也是指向控制台的*/
	class OStream :public MyStrIobase{
	public:
		void send(const char* ptr, int n)
		{
			for (int i = 0; i < n; ++i)
				putc(*ptr++, stdout);
			putc('\n', stdout);
		}
	};
	/* 标准iostream也可以输出*/
	void sendstr(ostream& os, const char* ptr, int n);
	/*自定义流对象输出到文件*/
	class FileOStream :public MyStrIobase {
	public:
		FileOStream(const char* filename, char* mode)
		{
			m_File = fopen(filename, mode);
		}
		void send(const char* str, int len)
		{
			if (m_File == nullptr || len < 0)
				return;
			for (int i = 0; i < len; ++i)
				putc(*str++, m_File);
		}
		void close()
		{
			fclose(m_File);
			m_File = nullptr;
		}
	private:
		FILE* m_File{ nullptr };
	};

	/*打印自定义类型  MInt*/
	class MInt {
	public:
		MInt(int val) :mVal(val) {}
		MInt(const MInt& other) :mVal(other.mVal) {}
		friend ostream& operator<<(ostream& os, const MInt& other);
		friend istream& operator >> (istream& is, MInt& out);
	private:
		int mVal;
	};
	ostream& operator<<(ostream& os, const MInt& other);
	istream& operator >> (istream& is, MInt& out);
	
	/* 用标准库fstream来对文件进行读写*/
	void writetofile1();
	void writetofile2();
	void writefromfile1();

	//template<class T> T& operator<<(T& io, const My_String& str)
	//{
	//	sendstr(io, str.c_str(), str.size());
	//	return io;
	//}

	
}

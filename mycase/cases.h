#pragma once

// **** 2019 - 03 - 10 ******//
//******** ����ļ��е���������ѧϰ��������С���� ********//

#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#include<stdio.h>
using namespace std;


/* ��ӡ���� */
void PrintRhombus();
/*����ʱ�����ͷ����������ʱ��ͷ���֮��Ķ���
	24Сʱ��ʱ��ʽ
*/
void CalculateAngle();
/* ������ʵ�ּ������������OO˼��*/
namespace Clock {
	class clock {
	public:
		clock();
		~clock();
		clock& seth(int);
		clock& setm(int);
		int geth();
		int getm();
		void cal();  //����Ƕ�
		void show();
		void run();
	private:
		int m_h;
		int m_m;
		double diff;

	};
}


/*�Զ���������ռ�*/
/* ***** ���� *********/
/*SpreadSheetCell��Ԫ����*/
namespace My_Code {
	/* һ����Ԫ����� */
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
	/* ���ӱ���� */
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
		int size () const{ return strlen(m_str); }   //const��Ա����������ı����
		char* c_str() const { return m_str; }
	private:
		char* m_str;
		int m_len;
	};
}
/* �Զ���IO�� */
namespace IO {
	class MyStrIobase {
	public:
		virtual ~MyStrIobase() {}
		virtual void send(const char* ptr, int n) {}
	};
	void sendstr(MyStrIobase& strio, const char* ptr, int n);

	/*���������̨ ��stdout�Ǳ�׼C�Ŀ���̨��std::cout��C++������Ҳ��ָ�����̨��*/
	class OStream :public MyStrIobase{
	public:
		void send(const char* ptr, int n)
		{
			for (int i = 0; i < n; ++i)
				putc(*ptr++, stdout);
			putc('\n', stdout);
		}
	};
	/* ��׼iostreamҲ�������*/
	void sendstr(ostream& os, const char* ptr, int n);
	/*�Զ���������������ļ�*/
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

	/*��ӡ�Զ�������  MInt*/
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
	
	/* �ñ�׼��fstream�����ļ����ж�д*/
	void writetofile1();
	void writetofile2();
	void writefromfile1();

	//template<class T> T& operator<<(T& io, const My_String& str)
	//{
	//	sendstr(io, str.c_str(), str.size());
	//	return io;
	//}

	
}

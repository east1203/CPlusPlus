
#include "./cases.h"
#include<stdio.h>
#include<iomanip>
#include<sstream>
#include<math.h>
void PrintRhombus()
{
	printf("Print Rhombus : \n");
	for (int i = 0; i <= 3; ++i)
	{
		for (int m = 0; m <= 2-i; ++m)
			printf(" ");
		for (int n = 0; n <= 2 * i; ++n)
			printf("*");
		printf("\n");
	}
	for (int i = 0; i <= 2; ++i)
	{
		for (int m = 0; m <= i; ++m)
			printf(" ");
		for (int n = 0; n <= 2 * (2 - i); ++n)
			printf("*");
		printf("\n");
	}
}

void CalculateAngle()
{
	int h , m;
	double hAngle, mAngle;
	double diff = 0;
	cout << "calculate the angle between hour hand and mimute hand " << endl;
	char flag;
	while (1)
	{
		cout << "enter the hour  number" << endl;
		cin >> h;
		cout << "enter the minute number " << endl;
		cin >> m;
		if (h <= 12)
			hAngle = h / 12.0 * 360+m/60.0*360/12;
		else
			hAngle = (h - 12) / 12.0 * 360+m/60.0*360/12;
		mAngle = m / 60.0 * 360;
		diff = abs(hAngle - mAngle);
		cout << "the angle is " << diff <<'\n'<< endl;
		cout << "if you want to quit ,enter 'q' or 'Q' ,otherwise enter 'c' to continue !" << endl;
		cin >> flag;
		//flag = getchar();
		if (flag == 'q' || flag == 'Q')
			break;
		flag = ' ';
	}
}
namespace Clock {
	clock::clock()
	{
	}
	clock::~clock()
	{
	}
	clock& clock::setm(int m)
	{
		m_m = m;
		return *this;
	}
	clock& clock::seth(int h)
	{
		m_h = h;
		return *this;
	}
	int clock::geth()
	{
		return m_h;
	}
	int clock::getm()
	{
		return m_m;
	}
	void clock::cal()
	{
		diff = abs(m_h % 12 / 12.0 * 360 + m_m / 60.0 * 360 / 12 - m_m % 60 / 60.0 * 360);
	}
	void clock::show()
	{
		cout.fill('0');
		cout << setw(2) << m_h << ":";
		cout << setw(2) << m_m << "=" << diff << endl;
	}
	void clock::run()
	{
		int m, h;
		cout << "enter hour and minute" << endl;
		cin >> h >> m;
		this->seth(h);
		this->setm(m);
		this->cal();
		this->show();
	}
}
namespace My_Code {



	double SpreadSheetCell::stringtodouble(const string str)
	{
		istringstream istr(str);     // 构造函数赋值
		double tmp;          // streamstring能将任意类型转换成string，也能将string转换成任意类型
		istr >> tmp;       
		if (istr.fail() || !istr.eof())   //
			return 0;
		return tmp;
	}
	string SpreadSheetCell::doubletostring(double value)
	{
		ostringstream ostr;
		ostr << value;
		return(ostr.str());
	}
	SpreadSheetCell::SpreadSheetCell() :m_value(0), m_Str("")
	{
	}
	SpreadSheetCell::SpreadSheetCell(string str) :m_value(stringtodouble(str)), m_Str(str)
	{
	}
	SpreadSheetCell::SpreadSheetCell(double value) : m_value(value), m_Str(doubletostring(value))
	{
	}
	SpreadSheetCell::SpreadSheetCell(const SpreadSheetCell& cell) : m_value(cell.m_value), m_Str(cell.m_Str)
	{
	}
	SpreadSheetCell::~SpreadSheetCell()
	{
	}
	SpreadSheetCell& SpreadSheetCell::operator=(const SpreadSheetCell& cell)
	{
		m_value = cell.m_value;
		m_Str = cell.m_Str;
		return *this;
	}
	SpreadSheetCell& SpreadSheetCell::operator+(const SpreadSheetCell& cell)
	{
		m_value = m_value + cell.m_value;
		m_Str = m_Str + cell.m_Str;
		return *this;
	}
	void SpreadSheetCell::SetDoubleValue(const double doublevalue)
	{
		m_value = doublevalue;
		m_Str = doubletostring(doublevalue);
	}
	void SpreadSheetCell::SetStringValue(const string stringvlaue)
	{
		m_value = stringtodouble(stringvlaue);
		m_Str = stringvlaue;
	}
	double SpreadSheetCell::GetDoubleValue()
	{
		return m_value;
	}
	string& SpreadSheetCell::GetStringValue()
	{
		return m_Str;
	}

	SpreadSheetData::SpreadSheetData(int width ,int height):
		m_width(width>defaultwidth?defaultwidth:width),m_high(height>defaulthigh?defaulthigh:height)
	{
		m_Cell = new SpreadSheetCell*[m_width];
		for (int i = 0; i < m_width; ++i)
			m_Cell[i] = new SpreadSheetCell[m_high];
	}
	SpreadSheetData::SpreadSheetData(SpreadSheetData &Data)
	{
		this->CopyFrom(Data);
	/*	m_width = Data.m_width;
		m_high = Data.m_high;
		m_Cell = new SpreadSheetCell*[m_width];
		for(int i=0;i<m_width;++i)
			m_Cell[i] = new SpreadSheetCell[m_high];
		for (int i = 0; i < m_width; ++i)
			for (int j = 0; j < m_high; ++j)
				m_Cell[i][j] = Data.m_Cell[i][j];*/
	}
	SpreadSheetData::~SpreadSheetData()
	{
		for (int i = 0; i<m_width; i++)
			delete[] m_Cell[i];
		delete[] m_Cell;
	}
	SpreadSheetData& SpreadSheetData::operator=(const SpreadSheetData & Data)
	{
		if (this == &Data)
			return *this;
		
		for (int i = 0; i < m_width; ++i)
			delete[] m_Cell[i];
		delete[] m_Cell;
		/*
		m_width = Data.m_width;
		m_high = Data.m_high;
		m_Cell = new SpreadSheetCell*[m_width];
		for ( int i = 0; i<m_width; ++i)
			m_Cell[i] = new SpreadSheetCell[m_high];
		for (int i = 0; i < m_width; ++i)
			for (int j = 0; j < m_high; ++j)
				m_Cell[i][j] = Data.m_Cell[i][j];
				*/
		this->CopyFrom(Data);
		return *this;
	}
	void SpreadSheetData::SetCellAt(int x, int y, const SpreadSheetCell& Cell)
	{
		if (!inRang(x, defaultwidth) || !inRang(y, defaulthigh))
		{
			cout << "参数有误" << endl;
			return;
		}
		m_Cell[x][y] = Cell;
	}
	SpreadSheetCell SpreadSheetData::GetCell(int x, int y)
	{
		SpreadSheetCell Cell;
		if (!inRang(x, m_width) || !inRang(y, m_high))
		{
			cout << "参数有误" << endl;
			return Cell;
		}
		
		return m_Cell[x][y];
	}
	bool SpreadSheetData::inRang(int val, int upper)
	{
		if (val<0 || val > upper)
			return false;
		return true;
	}
	void SpreadSheetData::CopyFrom(const SpreadSheetData & Data)
	{
		m_width = Data.m_width;
		m_high = Data.m_high;
		m_Cell = new SpreadSheetCell*[m_width];
		for (int i = 0; i<m_width; ++i)
			m_Cell[i] = new SpreadSheetCell[m_high];
		for (int i = 0; i < m_width; ++i)
			for (int j = 0; j < m_high; ++j)
				m_Cell[i][j] = Data.m_Cell[i][j];
	}
	void SpreadSheetData::test()
	{
		SpreadSheetCell Cell;
		Cell.SetDoubleValue(10);
		this->SetCellAt(3, 3, Cell);
		SpreadSheetCell Cell2;
		Cell2 = this->GetCell(3,3);
		cout << "Cell is :" << Cell.GetDoubleValue() << "***" << Cell.GetStringValue() << endl;
		cout << "Cell is :" << Cell2.GetDoubleValue() << "***" << Cell2.GetStringValue() << endl;
	}

	SpreadSheet::SpreadSheet(int width, int high)
	{
		m_Data = new SpreadSheetData(width, high);
	}
	SpreadSheet::SpreadSheet(const SpreadSheet& Data)
	{
		m_Data = new SpreadSheetData(*(Data.m_Data));
	}
	SpreadSheet::~SpreadSheet()
	{
		m_Data->~SpreadSheetData();
	}
	SpreadSheet& SpreadSheet::operator=(const SpreadSheet & Data)
	{
		*m_Data = *(Data.m_Data);
		return *this;
	}
	void SpreadSheet::SetCellAt(int x, int y, const SpreadSheetCell & cell)
	{
		m_Data->SetCellAt(x, y, cell);
	}
	SpreadSheetCell SpreadSheet::GetCelld(int x, int y)   //这里原来是返回SpreadSheetCell& 引用类型
	{																					//但是会出错，说返回局部对象或临时对象的地址
		
		return  m_Data->GetCell(x, y);
	}
	void SpreadSheet::test()
	{
		SpreadSheetCell Cell;
		Cell.SetDoubleValue(10);
		cout << "Cell " << Cell.GetDoubleValue() << endl;
		this->SetCellAt(2, 2, Cell);
		SpreadSheetCell Cell2(11);
		Cell2= GetCelld(2, 2);
		cout << "Cell is :" << Cell.GetDoubleValue() << "***" << Cell.GetStringValue() << endl;
		cout << "Cell2 is :" << Cell2.GetDoubleValue() << "***" << Cell2.GetStringValue() << endl;

	}

	My_String::My_String()
	{
		m_len = 4;
		m_str = new char[1];
		m_str[0] = '\0';
	}
	My_String::My_String(const char* str)
	{
		m_len = std::strlen(str);
		m_str = new char[m_len + 1];
		strcpy_s(m_str, m_len + 1, str);
	}
	My_String::My_String(const My_String& str)
	{
		m_len = str.m_len;
		m_str = new char[m_len + 1];
		strcpy_s(m_str, m_len + 1, str.m_str);
	}
	My_String::~My_String()
	{
		delete[] m_str;
	}
	My_String& My_String::operator=(const My_String & str)
	{
		if (this == &str)
			return *this;
		delete[] m_str;
		m_len = str.m_len;
		m_str = new char[m_len + 1];
		strcpy_s(m_str, m_len + 1, str.m_str);
		return *this;
	}
	My_String& My_String::operator=(const char *s)
	{
		delete[] m_str;
		m_len = std::strlen(s);
		m_str = new char[m_len + 1];
		strcpy_s(m_str, m_len + 1, s);
		return *this;
	}
	char& My_String::operator[](int i)
	{
		return m_str[i];
	}
	const char& My_String::operator[](int i) const
	{
		return m_str[i];
	}
	bool operator<(const My_String &str1, const My_String &str2)
	{
		return (std::strcmp(str1.m_str, str2.m_str)<0);
	}
	bool operator>(const My_String &str1, const My_String &str2)
	{
		return str2<str1;//调用上面的operator<
	}
	bool operator==(const My_String &str1, const My_String &str2)
	{
		return (std::strcmp(str1.m_str, str2.m_str) == 0);
	}
	ostream& operator<<(ostream &os, const My_String &str)
	{
		os << str.m_str;
		return os;
	}
	//istream& operator >> (istream &is, My_String &str)
	//{
	//	char temp[80];
	//	is.get(temp, 80);
	//	if (is)
	//		str = temp;//调用operator=
	//	while (is && is.get() != '\n')         //这一段不知道什么意思，但是注释掉也可以用
	//		continue;
	//	return is;
	//}
	istream& operator >> (istream &is, My_String &str)
	{
		char tmp[80];
		is.get(tmp, 80);
		if (is)
			str = tmp;
		return is;
	}




/* My_Code 命名空间结束*/
}
namespace IO {
	void sendstr(MyStrIobase& strio, const char* ptr, int n)
	{
		strio.send(ptr, n);
	}
	void sendstr(ostream& os, const char* ptr, int n)
	{
		os.write(ptr, n);
	}

	ostream& operator<<(ostream& os, const MInt& other) {
		os << other.mVal;
		return os;
	}
	istream& operator >> (istream& is, MInt& out) {
		is >> out.mVal;
		return is;
	}
	/* 用标准库fstream来对文件进行读写*/
	void writetofile1()
	{
		ofstream outFile("2.txt", std::ios::out);
		outFile << "this is test writetofile1 pro!" << endl;
		outFile.close();
	}
	void writetofile2()
	{
		ofstream outFile;
		outFile.open("3.txt", std::ios::out);
		outFile << "this is test writetofile2 pro!" << endl;
		outFile.close();
	}
	void writefromfile1()
	{
		ofstream outFile;
		outFile.open("4.txt", std::ios::out);
		outFile << "this is test writefromfile1 pro!" << endl;
		outFile.close();
		ifstream inFile("4.txt", std::ios::in);
		/*也可以用open函数打开*/
		string str;
		std::getline(inFile, str);
		cout << str << endl;
		inFile.close();
	}
}
//int main(void)
//{
//	SpreadSheetCell cell1(10.0);
//	SpreadSheetCell cell2("day");
//	SpreadSheetCell cell3=cell1+cell2;
//	cout << cell3.GetDoubleValue() << endl;
//	cout << cell3.GetStringValue() << endl;
//	system("pause");
//	return 0;
//}



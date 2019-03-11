#include "My_String.h"
#include <cstring>
using std::cin;
using std::cout;
namespace My_Code {

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
		if(is)
			str = tmp;
		return is;
	}
}


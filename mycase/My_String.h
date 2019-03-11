#pragma once
/* ÊµÏÖ×Ö·û´®Àà */

#include <iostream>
using std::ostream;
using std::istream;
namespace My_Code {
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
	private:
		char* m_str;
		int m_len;
	};
}


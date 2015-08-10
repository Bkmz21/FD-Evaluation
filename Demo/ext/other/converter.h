#pragma once

#include <windows.h>
#include <string>
#include <tchar.h>

using namespace std;


//================================================================================================================================================


namespace Other
{

class Converter
{
private: 
	static TCHAR tchar[255];

public:
	static string IntToStr(int i);
	static string FloatToStr(float f);
	static string DoubleToStr(double f);
	static string WCharToStr(WCHAR *wstr);
	static string CharToStr(CHAR *cstr);
	static TCHAR* StrToTChar(string str);
};

}
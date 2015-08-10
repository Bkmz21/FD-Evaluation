#include "converter.h"


//================================================================================================================================================


namespace Other
{

string Converter::IntToStr(int i)
{
	char sc[33];
	string str = "";

	_itoa(i, sc, 10);
	str.append(sc);

	return str;
}
string Converter::FloatToStr(float f)
{
	char sc[30];
	string str = "";

	sprintf(sc, "%f", f);
	str.append(sc);

	if (str.find(",") != -1)
	{
		str.replace(str.find(","), 1, ".");
	}

	return str;
}
string Converter::DoubleToStr(double f)
{
	char sc[50];
	string str = "";

	sprintf(sc, "%-20.15f", f);
	str.append(sc);

	return str;
}
string Converter::WCharToStr(WCHAR *wstr)
{
	char *cstr = new char[260];
	char DefChar = ' ';
	string str = "";
	
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, cstr, 260, &DefChar, NULL);
	str = cstr;
	
	delete[] cstr;
	return str;
}
string Converter::CharToStr(CHAR *cstr)
{
	string str = "";
	str.append(cstr);
	return str;
}
TCHAR Converter::tchar[255];
TCHAR* Converter::StrToTChar(string str)
{
	swprintf(tchar, 255, _T("%hs"), str.c_str());
	return tchar;
}

}
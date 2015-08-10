#pragma once

#include "work_dir.h"


//========================================================================================================


namespace Other
{

string WorkDir::GetCurrentDir()
{
	TCHAR lp[1000];
	GetModuleFileName(GetModuleHandle(NULL), lp, 1000);
	std::basic_string< TCHAR > stPath(lp);
	wchar_t* wstr = (wchar_t*)stPath.c_str();
	long sizew = wcstombs( NULL, wstr, 0) + 255;
	char *szName = new char[sizew + 1];
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, szName, sizew+1023, NULL, NULL);
	std::string path(szName ? szName : "");
	for (int i = path.length() - 1; i > 0; i--)
	{
		if (int(path[i]) == 92)
		{
			path = path.substr(0, i+1);
			break;
		}
	}
	delete[] szName;
	return WorkDir::ReplaceSlash(path);
}
bool WorkDir::FileExists(string path)
{
	FILE* testfile = fopen(path.c_str(), "r");
	if (testfile == NULL)
		return false;
	else
		fclose(testfile);
	return true;
}
string WorkDir::FileExistsAndRename(string path)
{
	if (FileExists(path))
	{
		string str = path;
		int i = 1;
		char sc[10];
		while (WorkDir::FileExists(str))
		{
			unsigned found = path.find_last_of(".");
			str = path.substr(0, found);
			str += "_";
			_itoa(i, sc, 10);
			str.append(sc);
			str += ".txt";
			i++;
		}
		path = str;
	}
	return path;
}
int WorkDir::FileCount(string strPath, vector<string> mask)
{
	int file_count = 0;
	WIN32_FIND_DATA fd; 
	HANDLE handle;

	for (int k = 0; k < mask.size(); ++k)
	{
		string strSpec = strPath + mask[k];
		TCHAR L_strSpec[255];
		swprintf (L_strSpec, 255, _T("%hs"), strSpec.c_str());
		handle = FindFirstFile(L_strSpec, &fd);
		//if(handle == INVALID_HANDLE_VALUE) return;
		int t = 0;
		while (FindNextFile(handle, &fd))
			t++;
		if (t == 0) continue;

		handle = FindFirstFile(L_strSpec, &fd);
		do 
		{
			file_count++;
		} 
		while (FindNextFile(handle, &fd));
	}	

	FindClose(handle);
	return file_count;
}
bool WorkDir::RemoveDir(IN LPCTSTR szDir)
{
	BOOL fRet = FALSE;
	if( !szDir) return fRet;

	size_t tReplaceLen = 1;
	WIN32_FIND_DATA fd = {};

	std::basic_string< TCHAR > stPath( szDir);
	stPath += _T( "\\*");

	HANDLE hFind = FindFirstFile( stPath.c_str(), &fd);
	if( hFind != INVALID_HANDLE_VALUE)
	{
		fRet = TRUE;
		do 
		{
			if( !(_tcscmp( fd.cFileName, _T( ".")) && _tcscmp( fd.cFileName, _T( ".."))) )
				continue;

			stPath.replace( stPath.end() - tReplaceLen, stPath.end(), fd.cFileName);
			tReplaceLen = _tcslen( fd.cFileName);

			if( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				fRet = RemoveDir( stPath.c_str());
			else
			{
				if( fd.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
					SetFileAttributes( stPath.c_str(), FILE_ATTRIBUTE_NORMAL);
				fRet = DeleteFile( stPath.c_str());
			}

		}
		while( fRet && FindNextFile( hFind, &fd));
		FindClose( hFind);

		if( fRet) fRet = RemoveDirectory( szDir);
	}
	return fRet;
}
string WorkDir::ReplaceSlash(string str)
{
	string str_rs = str;
	for (int i = 0; i < str_rs.length(); ++i)
	{
		if (str_rs[i] == char(92))
			str_rs[i] = char(47);
	}
	return str_rs;
}
string WorkDir::RecorPath(string str)
{
	if (str.length() < 3) return str;

	string currDir = WorkDir::GetCurrentDir();
	string str_rs = WorkDir::ReplaceSlash(str);
	if ((str_rs[0] == '.') && (str_rs[1] == '.')) 
	{
		str_rs.replace(0, 3, currDir.c_str());
	}
	//else
	//	if (str_rs[1] != ':')
	//		str_rs = currDir.append(str_rs);
	
	return str_rs;
}
void WorkDir::CreateFolder(string str)
{
	CreateDirectoryA(str.c_str(), NULL);
}

}
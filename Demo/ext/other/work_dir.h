#pragma once

#include <windows.h>
#include <iostream> 
#include <fstream>
#include <string>
#include <tchar.h>
#include <vector>

using namespace std;


//========================================================================================================


namespace Other
{

class WorkDir
{
public:
	static string GetCurrentDir();
	static bool FileExists(string path);
	static string FileExistsAndRename(string path);
	static int FileCount(string strPath, vector<string> mask);
	static bool RemoveDir(IN LPCTSTR szDir);
	static string ReplaceSlash(string str);
	static string RecorPath(string str);
	static void CreateFolder(string str);
};

}
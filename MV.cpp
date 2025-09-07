#include <windows.h>
#include <shellapi.h>
#include <iostream>
int main() {
	std::wstring pszSource;
    std::getline(std::wcin, pszSource); 
	// 输入一行路径
	pszSource += L'\0\0';
	// 确保以双null结尾.
    SHFILEOPSTRUCTW c = {0};
    c.wFunc = FO_DELETE;
    c.pFrom = pszSource.c_str();
    c.fFlags = FOF_ALLOWUNDO | FOF_SILENT |FOF_NOCONFIRMATION |FOF_NOERRORUI |FOF_NOCONFIRMMKDIR;
	// 文件操作是删除到回收站,并且无提示.
    SHFileOperationW(&c);
	// 宽字符
	return 0;
}
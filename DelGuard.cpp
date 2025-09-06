// 列举回收站中的文件和目录,由范文庆 周彬彬 安靖编著的ISBN 978-7-115-19095-6图书
// 被陈思汗修改于2025/9/6
#include <Windows.h>
#include <shlobj.h>
#include <stdio.h>
//SHGetFolderPathA(NULL,CSIDL_PERSONAL,(HANDLE)NULL,(DWORD)NULL,szMyDocument);
//上面是SHGetSpecialFolderPath(NULL,szMyDocument,CSIDL_PERSONAL,FALSE);的其他版本
int main()
{
    CHAR pszPath[MAX_PATH];        
    IShellFolder *pisf = NULL;
    IShellFolder *pisfRecBin = NULL;
    SHGetDesktopFolder(&pisfRecBin);  
    IEnumIDList *peidl = NULL;    
    LPITEMIDLIST pidlBin = NULL;
    LPITEMIDLIST idlCurrent = NULL;
    LPMALLOC pMalloc = NULL;
    SHGetMalloc(&pMalloc);
    SHGetFolderLocation(NULL, CSIDL_BITBUCKET, NULL, 0, &pidlBin);
	// 包含用户回收站的对象的虚拟文件夹
    pisfRecBin->BindToObject(pidlBin,NULL,IID_IShellFolder,(void **) &pisf);
	// IID_ISHELLFolder 全域唯一识别码是{000214E6-0000-0000-C000-000000000046}
	// IID 接口标识
    pisf->EnumObjects(NULL,
        SHCONTF_FOLDERS | SHCONTF_NONFOLDERS | SHCONTF_INCLUDEHIDDEN,
        &peidl);
	// 枚举文件夹内容,包括是或不是文件夹的项,隐藏的项
    STRRET strret;
    ULONG uFetched;
    // Next是接口IEnumIDList的方法,并非命名空间std的next.
	// celt=1时,&uFetched为NULL.
    while(1)
    {
        if(peidl->Next(1,&idlCurrent,&uFetched) == S_FALSE)
			//没有条目就停止检索	
            break;
        pisf->GetDisplayNameOf(idlCurrent,SHGDN_NORMAL,&strret);
		// 文件夹选项
		wprintf(L"%s\n", strret.pOleStr);
		// pOleStr是一个指针
    }
    pMalloc->Free(pidlBin);
    pMalloc->Free(strret.pOleStr);
	// 释放内存
    pMalloc->Release();
    peidl->Release();
    pisf->Release();
	// Release是LUnKnown成员函数,也即基础接口的成员函数,递减COM对象上接口的引用计数.
    return 0;    
}
// 2025-9-26.exe 视窗操作系统版本可以是
// 5.1.2600
// 6.1.7601
// 6.2.9200
// 10.0.26100.4946
// 10.0.19045.6216
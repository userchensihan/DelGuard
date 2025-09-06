#include <windows.h>
#include <shellapi.h>
int main() {
    SHEmptyRecycleBinW(NULL,NULL,SHERB_NOCONFIRMATION);
	return 0;
}
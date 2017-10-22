#include <windows.h>
#include <wchar.h>

int main(void) {

    unsigned __int64 freeCall,
                     total,
                     free;

    int r = GetDiskFreeSpaceExW(L"C:\\", (PULARGE_INTEGER) &freeCall,
        (PULARGE_INTEGER) &total, (PULARGE_INTEGER) &free);

    if (r == 0) {

        wprintf(L"Failed to get free disk space %ld", GetLastError());
        return 1;
    }	

    wprintf(L"Available space to caller: %I64u MB\n", freeCall / (1024*1024));
    wprintf(L"Total space: %I64u MB\n", total / (1024*1024));
    wprintf(L"Free space on drive: %I64u MB\n", free / (1024*1024));
    
    return 0;
}
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define CREATE_DIRECTORY 0

int _tmain(int argc, TCHAR *argv[]) {
  TCHAR dirRelativePath[] = _T("GoodDirectoryOne");
  TCHAR dirFullPath[] = _T("C:\\GoodDirectoryOne");

#if CREATE_DIRECTORY
  CreateDirectory(dirRelativePath, NULL);
  CreateDirectory(dirFullPath, NULL);
#else
  RemoveDirectory(dirRelativePath);
  RemoveDirectory(dirFullPath);
#endif

  return 0;
}
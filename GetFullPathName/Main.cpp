#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define STRING_LEN 128

int _tmain(int argc, TCHAR *argv[]) {
  if (argc != 2) return 1;
  LPCTSTR fileName = argv[1];
  TCHAR fileFullPath[STRING_LEN];
  LPTSTR filePtr;

  GetFullPathName(fileName, STRING_LEN, fileFullPath, &filePtr);
  _tprintf(_T("%s \n"), fileFullPath);
  _tprintf(_T("%s \n"), filePtr);
  return 0;
}
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR *argv[]) {
  TCHAR fileName[MAX_PATH];
  TCHAR bufFilePath[MAX_PATH];
  TCHAR currentDir[MAX_PATH];
  LPTSTR lpFilePart;
  DWORD result;

  GetCurrentDirectory(MAX_PATH, currentDir);
  _tprintf(_T("[CURRENT DIR]: %s \n"), currentDir);

  while (1) {
    _fputts(_T("Insert name of the file to find: "), stdout);
    _tscanf(_T("%s"), fileName);

    result = SearchPath(NULL, fileName, NULL, MAX_PATH, bufFilePath, &lpFilePart);
    if (result == 0) {
      _fputts(_T("File not found! \n"), stderr);
      _gettchar();
      return 1;
    } else {
      _tprintf(_T("File path: %s \n"), bufFilePath);
      _tprintf(_T("File name: %s \n"), lpFilePart);
    }
  }
  return 0;
}
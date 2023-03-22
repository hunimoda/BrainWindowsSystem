#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int ReadStringAndWrite();

int _tmain(int argc, TCHAR *argv[]) {
  int state = 0;
  while (1) {
    state = ReadStringAndWrite();
    if (state == -1) {
      _fputts(_T("Some problem occurred! \n"), stderr);
      break;
    }
    if (state == 0) {
      _fputts(_T("Graceful exit! \n"), stdout);
      break;
    }
  }
  return 0;
}

int ReadStringAndWrite() {
  FILE *file = NULL;
  TCHAR *strBufPtr = NULL;

  __try {
    file = _tfopen(_T("string.dat"), _T("a+t"));
    if (!file) return 1;

    DWORD strLen = 0;
    _fputts(_T("Input string length(0 to exit): "), stdout);
    _tscanf(_T("%d"), &strLen);
    if (!strLen) return 0;

    strBufPtr = (TCHAR *)malloc(sizeof(TCHAR) * (strLen + 1));
    if (!strBufPtr) return 2;

    _fputts(_T("Input string: "), stdout);
    _tscanf(_T("%s"), strBufPtr);
    _ftprintf(file, _T("%s \n"), strBufPtr);
  } __finally {
    if (file) fclose(file);
    if (strBufPtr) free(strBufPtr);
    _fputts(_T("__finally \n"), stdout);
  }
  return 0;
}
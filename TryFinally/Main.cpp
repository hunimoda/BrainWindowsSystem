#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR *argv[]) {
  int a = 0;
  int b = 0;

  __try {
    _fputts(_T("input divide string [a/b]: "), stdout);
    _tscanf(_T("%d/%d"), &a, &b);
    if (b == 0) return 1;
  } __finally {
    _fputts(_T("__finally block \n"), stdout);
  }
  _tprintf(_T("result: %d \n"), a / b);
  return 0;
}
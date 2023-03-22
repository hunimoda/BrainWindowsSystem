#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR *argv[]) {
  while (1) {
    _fputts(_T("1 for memory access exception \n"), stdout);
    _fputts(_T("2 for divide by 0 exception \n"), stdout);
    _fputts(_T("Select exception type(3 for exit): "), stdout);

    int sel = 0;
    _tscanf(_T("%d"), &sel);
    if (sel == 3) break;

    __try {
      if (sel == 1) {
        int *p = NULL;
        *p = 100;  // 예외 발생 지점
      } else if (sel == 2) {
        int n = 0;
        n = 7 / n;  // 예외 발생 지점
      }
    } __except (EXCEPTION_EXECUTE_HANDLER) {
      switch (GetExceptionCode()) {
        case EXCEPTION_ACCESS_VIOLATION:
          _fputts(_T("Access violation \n\n"), stderr);
          break;

        case EXCEPTION_INT_DIVIDE_BY_ZERO:
          _fputts(_T("Divide by zero \n\n"), stderr);
          break;
      }
    }
  }
  return 0;
}
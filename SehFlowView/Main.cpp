#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR *argv[]) {
  _fputts(_T("Start point! \n"), stdout);

  int *p = NULL;
  __try {
    *p = 100;
    _tprintf(_T("value: %d \n"), *p);
  } __except (EXCEPTION_EXECUTE_HANDLER) {
    _fputts(_T("Exception occurred! \n"), stderr);
  }
  _fputts(_T("End point! \n"), stdout);
  return 0;
}
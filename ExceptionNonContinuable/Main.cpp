#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define EXCEPTION_HUNIMODA ((DWORD)0xE000008L)

void SoftwareException();

int _tmain(int argc, TCHAR *argv[]) {
  __try {
    SoftwareException();
  } __except (EXCEPTION_CONTINUE_EXECUTION) {
    if (GetExceptionCode() == EXCEPTION_HUNIMODA) {
      _fputts(_T("EXCEPTION_HUNIMODA occurred! \n"), stderr);
    }
  }
  _fputts(_T("End of main \n"), stdout);
  return 0;
}

void SoftwareException() {
  RaiseException(EXCEPTION_HUNIMODA, EXCEPTION_NONCONTINUABLE, NULL, NULL);
  _fputts(_T("It's working! \n"), stdout);
}
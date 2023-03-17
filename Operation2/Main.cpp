#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[]) {
  SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);

  while (1) {
    for (DWORD i = 0; i < 10'000; i++) {
      for (DWORD j = 0; j < 10'000; j++) {
        for (DWORD k = 0; k < 10'000; k++) {
          for (DWORD l = 0; l < 10'000; l++);
        }
      }
    }
    // _fputts(_T("Operation2.exe \n"), stdout);
  }
  return 0;
}
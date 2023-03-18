#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR *argv[]) {
  SetProcessAffinityMask(GetCurrentProcess(), 1);
  SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);

  while (1) {
    // for (int i = 0; i < 10'000; i++) {
    //   for (int j = 0; j < 10'000; j++) {}
    // }
    Sleep(10);
    _fputts(_T("NORMAL_PRIORITY_CLASS Process \n"), stdout);
  }
  return 0;
}
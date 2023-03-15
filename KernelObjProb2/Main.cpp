#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[]) {
  DWORD n = 0;
  while (n < 100) {
    for (DWORD i = 0; i < 10'000; i++) {
      for (DWORD j = 0; j < 10'000; j++) {}
    }
    _fputts(_T("KernelObjProb2.exe \n"), stdout);
    n++;
  }
  return 0;
}
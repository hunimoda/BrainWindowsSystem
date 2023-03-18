#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR *argv[]) {
  SetProcessAffinityMask(GetCurrentProcess(), 1);

  STARTUPINFO siNormal = { 0, };
  PROCESS_INFORMATION piNormal;
  TCHAR commandOne[] = _T("NormalPriorityClass.exe");

  STARTUPINFO siBelow = { 0, };
  PROCESS_INFORMATION piBelow;
  TCHAR commandTwo[] = _T("BelowNormalPriorityClass.exe");

  siNormal.cb = sizeof(siNormal);
  siBelow.cb = sizeof(siBelow);

  SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);

  CreateProcess(
      NULL, commandOne, NULL, NULL, TRUE, 0, NULL, NULL, &siNormal, &piNormal);
  CreateProcess(
      NULL, commandTwo, NULL, NULL, TRUE, 0, NULL, NULL, &siBelow, &piBelow);

  while (1) {
    // for (int i = 0; i < 10'000; i++) {
    //   for (int j = 0; j < 10'000; j++) {}
    // }
    Sleep(10);
    _fputts(_T("ABOVE_NORMAL_PRIORITY_CLASS Process \n"), stdout);
  }
  return 0;
}
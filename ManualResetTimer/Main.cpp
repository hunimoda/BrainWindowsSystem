#define _WIN32_WINNT 0x0400

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR *argv[]) {
  HANDLE hTimer = NULL;
  LARGE_INTEGER liDueTime;

  liDueTime.QuadPart = -100'000'000;

  hTimer = CreateWaitableTimer(NULL, FALSE, _T("WaitableTimer"));
  if (!hTimer) {
    _tprintf(_T("CreateWaitableTimer error: %d \n"), GetLastError());
    return 1;
  }
  _fputts(_T("Waiting for 10 seconds... \n"), stdout);

  SetWaitableTimer(hTimer, &liDueTime, 0, NULL, NULL, FALSE);

  WaitForSingleObject(hTimer, INFINITE);
  _fputts(_T("Timer was signaled \n"), stdout);
  MessageBeep(MB_ICONEXCLAMATION);

  return 0;
}
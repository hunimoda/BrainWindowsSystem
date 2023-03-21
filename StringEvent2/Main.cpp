#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);
unsigned int WINAPI CountThreadFunction(LPVOID lpParam);

TCHAR string[128];
HANDLE hEvent;

int _tmain(int argc, TCHAR *argv[]) {
  HANDLE hThreads[2];
  DWORD dwThreadIds[2];

  hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
  if (!hEvent) {
    _fputts(_T("CreateEvent error \n"), stderr);
    return 1;
  }

  hThreads[0] = (HANDLE)_beginthreadex(
      NULL, 0, OutputThreadFunction, NULL, 0, (unsigned int *)&dwThreadIds[0]);
  hThreads[1] = (HANDLE)_beginthreadex(
      NULL, 0, CountThreadFunction, NULL, 0, (unsigned int *)&dwThreadIds[1]);
  if (!hThreads[0] || !hThreads[1]) {
    _fputts(_T("_beginthreadex error \n"), stderr);
    return 2;
  }

  _fputts(_T("Insert string: "), stdout);
  _fgetts(string, sizeof(string) / sizeof(TCHAR), stdin);

  SetEvent(hEvent);
  WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);

  CloseHandle(hEvent);
  CloseHandle(hThreads[0]);
  CloseHandle(hThreads[1]);

  return 0;
}

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam) {
  WaitForSingleObject(hEvent, INFINITE);
  _tprintf(_T("output string: %s"), string);
  return 0;
}

unsigned int WINAPI CountThreadFunction(LPVOID lpParam) {
  WaitForSingleObject(hEvent, INFINITE);
  _tprintf(_T("output string length: %d \n"), _tcslen(string));
  return 0;
}

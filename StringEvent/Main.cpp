#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

unsigned int WINAPI ThreadOutput(LPVOID lpParam);

TCHAR string[128];
HANDLE hEvent;

int _tmain(int argc, TCHAR *argv[]) {
  HANDLE hThread;
  DWORD dwThreadId;

  hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
  if (!hEvent) {
    _fputts(_T("Event object creation error \n"), stderr);
    return 1;
  }

  hThread = (HANDLE)_beginthreadex(
      NULL, 0, ThreadOutput, NULL, 0, (unsigned int *)&dwThreadId);
  if (!hThread) {
    _fputts(_T("Thread creation error \n"), stderr);
    return 2;
  }

  _fputts(_T("Insert string: "), stdout);
  _fgetts(string, sizeof(string) / sizeof(TCHAR), stdin);

  SetEvent(hEvent);
  WaitForSingleObject(hThread, INFINITE);
  CloseHandle(hEvent);
  CloseHandle(hThread);

  return 0;
}

unsigned int WINAPI ThreadOutput(LPVOID lpParam) {
  WaitForSingleObject(hEvent, INFINITE);
  _tprintf(_T("Output string: %s \n"), string);
  return 0;
}
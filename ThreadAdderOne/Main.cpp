#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

DWORD WINAPI ThreadProc(LPVOID lpParam) {
  DWORD start = ((DWORD *)lpParam)[0];
  DWORD end   = ((DWORD *)lpParam)[1];
  DWORD sum   = 0;

  for (DWORD i = start; i < end; i++) {
    sum += i;
  }
  return sum;
}

int _tmain(int argc, TCHAR *argv[]) {
  DWORD dwThreadID[3];
  HANDLE hThread[3];

  DWORD threadParam[] = { 1, 4, 7, 11 };
  DWORD sum = 0;
  for (int i = 0; i < 3; i++) {
    hThread[i] = CreateThread(
        NULL, 0, ThreadProc, threadParam + i, 0, &dwThreadID[i]);
    if (!hThread[i]) {
      _fputts(_T("Thread creation fault! \n"), stderr);
      return 1;
    }
  }

  WaitForMultipleObjects(3, hThread, TRUE, INFINITE);

  DWORD result = 0;
  for (int i = 0; i < 3; i++) {
    GetExitCodeThread(hThread[i], &result);
    sum += result;
  }

  _tprintf(_T("total sum(1 ~ 10): %d \n"), sum);

  for (int i = 0; i < 3; i++) {
    CloseHandle(hThread[i]);
  }
  return 0;
}
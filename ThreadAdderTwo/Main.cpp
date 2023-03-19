#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

static int total = 0;

DWORD WINAPI ThreadMain(LPVOID lpParam) {
  DWORD start = ((DWORD *)lpParam)[0];
  DWORD end   = ((DWORD *)lpParam)[1];

  for (DWORD num = start; num < end; num++) {
    total += num;
  }
  return 0;
}

int _tmain(int argc, TCHAR *argv[]) {
  DWORD dwThreadIDs[3];
  HANDLE hThreads[3];

  DWORD threadParams[] = { 1, 4, 7, 11 };

  for (int i = 0; i < 3; i++) {
    hThreads[i] = CreateThread(
        NULL, 0, ThreadMain, (LPVOID)&threadParams[i], 0, &dwThreadIDs[i]);
    if (hThreads[i] == NULL) {
      _fputts(_T("Thread creation failed! \n"), stderr);
      return 1;
    }
  }

  WaitForMultipleObjects(3, hThreads, TRUE, INFINITE);
  _tprintf(_T("total (1 ~ 10): %d \n"), total);

  for (int i = 0; i < 3; i++) {
    CloseHandle(hThreads[i]);
  }
  return 0;
}
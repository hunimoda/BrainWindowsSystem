#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#define MAX_THREADS (10 * 1'024)

unsigned int WINAPI ThreadMain(LPVOID lpParam) {
  DWORD threadNum = *(DWORD *)lpParam;
  while (1) {
    _tprintf(_T("thread num: %d \n"), threadNum);
    Sleep(1'000);
  }
  return 0;
}

DWORD threadCount = 0;

int _tmain(int argc, TCHAR *argv[]) {
  SetProcessAffinityMask(GetCurrentProcess(), 1);

  DWORD dwThreadIDs[MAX_THREADS];
  HANDLE hThreads[MAX_THREADS];

  while (1) {
    hThreads[threadCount] = (HANDLE)_beginthreadex(
        NULL, 0, ThreadMain, (LPVOID)&threadCount, 0,
        (unsigned int *)&dwThreadIDs[threadCount]);
    if (hThreads[threadCount] == NULL) {
      _tprintf(_T("MAXIMUM THREAD SIZE: %d \n"), threadCount);
      break;
    }
    threadCount++;
  }

  for (DWORD i = 0; i < threadCount; i++) {
    CloseHandle(hThreads[i]);
  }
  return 0;
}
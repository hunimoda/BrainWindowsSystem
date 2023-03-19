#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#define NUM_OF_GATE 10
#define NUM_OF_PEOPLE 10'000

LONG gTotalCount = 0;

void IncreaseCount() { gTotalCount++; }

unsigned int WINAPI ThreadMain(LPVOID lpParam) {
  for (int i = 0; i < NUM_OF_PEOPLE; i++) {
    IncreaseCount();
  }
  return 0;
}

int _tmain(int argc, TCHAR *argv[]) {
  DWORD dwThreadIDs[NUM_OF_GATE];
  HANDLE hThreads[NUM_OF_GATE];

  for (int i = 0; i < NUM_OF_GATE; i++) {
    hThreads[i] = (HANDLE)_beginthreadex(
        NULL, 0, ThreadMain, NULL, CREATE_SUSPENDED,
        (unsigned int *)&dwThreadIDs[i]);
    if (hThreads[i] == NULL) {
      _fputts(_T("Thread creation failed! \n"), stderr);
      return 1;
    }
  }

  for (int i = 0; i < NUM_OF_GATE; i++) {
    ResumeThread(hThreads[i]);
  }

  WaitForMultipleObjects(NUM_OF_GATE, hThreads, true, INFINITE);
  _tprintf(_T("total count: %d \n"), gTotalCount);
  for (int i = 0; i < NUM_OF_GATE; i++) {
    CloseHandle(hThreads[i]);
  }
  return 0;
}
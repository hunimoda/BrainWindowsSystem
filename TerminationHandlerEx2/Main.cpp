#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#define NUM_OF_GATE 7
int gTotalCount = 0;
HANDLE hMutex;

void IncreaseCount() {
  __try {
    WaitForSingleObject(hMutex, INFINITE);
    gTotalCount++;
  } __finally {
    ReleaseMutex(hMutex);
  }
}

unsigned int WINAPI ThreadProc(LPVOID lpParam) {
  for (int i = 0; i < 1'000; i++) {
    IncreaseCount();
  }
  return 0;
}

int _tmain(int argc, TCHAR *argv[]) {
  DWORD dwThreadIds[NUM_OF_GATE];
  HANDLE hThreads[NUM_OF_GATE];

  hMutex = CreateMutex(NULL, FALSE, NULL);
  if (!hMutex) {
    _tprintf(_T("CreateMutex fault: %d \n"), GetLastError());
    return 1;
  }

  for (int i = 0; i < NUM_OF_GATE; i++) {
    hThreads[i] = (HANDLE)_beginthreadex(
        NULL, 0, ThreadProc, NULL, CREATE_SUSPENDED,
        (unsigned int *)&dwThreadIds[i]);
    if (!hThreads[i]) {
      _fputts(_T("_beginthreadex fault! \n"), stderr);
      return 2;
    }
  }

  for (int i = 0; i < NUM_OF_GATE; i++) {
    ResumeThread(hThreads[i]);
  }

  WaitForMultipleObjects(NUM_OF_GATE, hThreads, TRUE, INFINITE);

  _tprintf(_T("total count: %d \n"), gTotalCount);
  for (int i = 0; i < NUM_OF_GATE; i++) {
    CloseHandle(hThreads[i]);
  }
  CloseHandle(hMutex);
  return 0;
}

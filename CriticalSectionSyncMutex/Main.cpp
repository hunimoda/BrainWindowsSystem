#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#define NUM_OF_GATE 64
#define NUM_OF_CROWD 10'000

int gTotalCount = 0;

HANDLE hMutex;

void AcquireMutex(HANDLE hMutex) { WaitForSingleObject(hMutex, INFINITE); }

void IncreaseCount() {
  AcquireMutex(hMutex);
  gTotalCount++;
  ReleaseMutex(hMutex);
}

unsigned int WINAPI ThreadMain(LPVOID lpParam) {
  for (int i = 0; i < NUM_OF_CROWD; i++) {
    IncreaseCount();
  }
  return 0;
}

int _tmain(int argc, TCHAR *argv[]) {
  DWORD dwThreadIDs[NUM_OF_GATE];
  HANDLE hThreads[NUM_OF_GATE];

  hMutex = CreateMutex(NULL, FALSE, NULL);
  if (hMutex == NULL) {
    _ftprintf(stderr, _T("Create mutex error: %d \n"), GetLastError());
    return 1;
  }

  for (int i = 0; i < NUM_OF_GATE; i++) {
    hThreads[i] = (HANDLE)_beginthreadex(
        NULL, 0, ThreadMain, NULL, CREATE_SUSPENDED,
        (unsigned int *)&dwThreadIDs[i]);
    if (hThreads[i] == NULL) {
      _fputts(_T("Thread creation fault! \n"), stderr);
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

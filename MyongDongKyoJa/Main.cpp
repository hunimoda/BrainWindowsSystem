#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <Windows.h>
#include <process.h>

#define NUMBER_OF_CUSTOMERS 50
#define RANGE_MIN 10
#define RANGE_MAX 20
#define TABLE_COUNT 10

HANDLE hSemaphore;
DWORD randomTimes[NUMBER_OF_CUSTOMERS];

void TakeMeal(DWORD time) {
  DWORD threadId = GetCurrentThreadId();

  WaitForSingleObject(hSemaphore, INFINITE);
  _tprintf(_T("Customer %d entered! \n"), threadId);
  _tprintf(_T("Customer %d having lunch... \n"), threadId);
  Sleep(time * 1'000);
  ReleaseSemaphore(hSemaphore, 1, NULL);

  _tprintf(_T("Customer %d leaving~ \n"), threadId);
}

unsigned int WINAPI ThreadMain(LPVOID lpParam) {
  TakeMeal(*(DWORD *)lpParam);
  return 0;
}

int _tmain(int argc, TCHAR *argv[]) {
  DWORD dwThreadIds[NUMBER_OF_CUSTOMERS];
  HANDLE hThreads[NUMBER_OF_CUSTOMERS];

  srand((unsigned int)time(NULL));

  for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
    randomTimes[i] =
        (RANGE_MAX - RANGE_MIN) * ((double)rand() / RAND_MAX) + RANGE_MIN;
  }

  hSemaphore = CreateSemaphore(NULL, TABLE_COUNT, TABLE_COUNT, NULL);
  if (hSemaphore == NULL) {
    _ftprintf(stderr, _T("CreateSemaphore error: %d \n"), GetLastError());
    return 1;
  }

  for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
    hThreads[i] = (HANDLE)_beginthreadex(
        NULL, 0, ThreadMain, &randomTimes[i], CREATE_SUSPENDED,
        (unsigned int *)&dwThreadIds[i]);
    if (hThreads[i] == NULL) {
      _fputts(_T("Thread creation fault! \n"), stderr);
      return 2;
    }
  }

  for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
    ResumeThread(hThreads[i]);
  }

  WaitForMultipleObjects(NUMBER_OF_CUSTOMERS, hThreads, TRUE, INFINITE);
  _fputts(_T("--- END --------------------------- \n"), stdout);

  for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
    CloseHandle(hThreads[i]);
  }
  CloseHandle(hSemaphore);

  return 0;
}
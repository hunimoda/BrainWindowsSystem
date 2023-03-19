#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

int gTotalCount = 0;
HANDLE hMutex;

unsigned int WINAPI IncrementCountOne(LPVOID lpParam) {
  WaitForSingleObject(hMutex, INFINITE);
  gTotalCount++;
  return 0;
}

unsigned int WINAPI IncrementCountTwo(LPVOID lpParam) {
  DWORD dwWaitResult = WaitForSingleObject(hMutex, INFINITE);
  if (dwWaitResult == WAIT_ABANDONED) {
    _fputts(_T("WAIT_ABANDONED \n"), stdout);
  }
  gTotalCount++;
  ReleaseMutex(hMutex);
  return 0;
}

int _tmain(int argc, TCHAR *argv[]) {
  DWORD dwThreadIdOne, dwThreadIdTwo;
  HANDLE hThreadOne, hThreadTwo;

  hMutex = CreateMutex(NULL, FALSE, NULL);
  if (hMutex == NULL) {
    _ftprintf(stderr, _T("CreateMutex error: %d \n"), GetLastError());
    return 1;
  }

  hThreadOne = (HANDLE)_beginthreadex(
      NULL, 0, IncrementCountOne, NULL, 0, (unsigned int *)&dwThreadIdOne);
  hThreadTwo = (HANDLE)_beginthreadex(
      NULL, 0, IncrementCountTwo, NULL, CREATE_SUSPENDED,
      (unsigned int *)&dwThreadIdTwo);

  Sleep(1'000);
  ResumeThread(hThreadTwo);
  Sleep(1'000);

  WaitForSingleObject(hMutex, INFINITE);
  _tprintf(_T("total count: %d \n"), gTotalCount);
  CloseHandle(hThreadOne);
  CloseHandle(hThreadTwo);
  CloseHandle(hMutex);
  return 0;
}
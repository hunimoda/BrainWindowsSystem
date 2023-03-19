#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#define CREATE_MUTEX 1
#define MUTEX_NAME _T("NamedMutex")

HANDLE hMutex;
DWORD dwWaitResult;

void ProcessBaseCriticalSection() {
  dwWaitResult = WaitForSingleObject(hMutex, INFINITE);
  switch (dwWaitResult) {
    case WAIT_OBJECT_0:
      _fputts(_T("Thread got mutex! \n"), stdout);
      break;

    case WAIT_TIMEOUT:
      _fputts(_T("Timer expiration! \n"), stdout);
      return;

    case WAIT_ABANDONED:
      return;
  }
  for (int i = 0; i < 5; i++) {
    _fputts(_T("Thread running... \n"), stdout);
    Sleep(3'000);
  }
  ReleaseMutex(hMutex);
}

int _tmain(int argc, TCHAR *argv[]) {
#if CREATE_MUTEX
  hMutex = CreateMutex(NULL, FALSE, MUTEX_NAME);
#else
  hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, MUTEX_NAME);
#endif

  if (hMutex == NULL) {
    _ftprintf(stderr, _T("CreateMutex error: %d \n"), GetLastError());
    return 1;
  }

  ProcessBaseCriticalSection();

  CloseHandle(hMutex);
  return 0;
}
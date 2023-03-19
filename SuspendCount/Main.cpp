#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

unsigned int WINAPI ThreadMain(LPVOID lpParam) {
  while (1) {
    _fputts(_T("Running state! \n"), stdout);
    Sleep(1'000);
  }
  return 0;
}

int _tmain(int argc, TCHAR *argv[]) {
  DWORD dwThreadID;
  HANDLE hThread;
  DWORD suspendCount;

  hThread = (HANDLE)_beginthreadex(
      NULL, 0, ThreadMain, NULL, CREATE_SUSPENDED, (unsigned int *)&dwThreadID);
  if (hThread == NULL) {
    _fputts(_T("Thread creation fault! \n"), stderr);
  }

  suspendCount = ResumeThread(hThread);
  _tprintf(_T("suspend count: %d \n"), suspendCount);
  Sleep(10'000);

  suspendCount = SuspendThread(hThread);
  _tprintf(_T("suspend count: %d \n"), suspendCount);
  Sleep(10'000);

  suspendCount = SuspendThread(hThread);
  _tprintf(_T("suspend count: %d \n"), suspendCount);
  Sleep(10'000);

  suspendCount = ResumeThread(hThread);
  _tprintf(_T("suspend count: %d \n"), suspendCount);
  Sleep(10'000);

  suspendCount = ResumeThread(hThread);
  _tprintf(_T("suspend count: %d \n"), suspendCount);

  WaitForSingleObject(hThread, INFINITE);
  return 0;
}
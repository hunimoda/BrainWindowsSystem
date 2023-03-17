#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR *argv[]) {
  HANDLE hParent;
  _stscanf(argv[1], _T("%p"), &hParent);
  DWORD isSuccess = WaitForSingleObject(hParent, INFINITE);

  _fputts(_T("[Child Process] \n"), stdout);

  if (isSuccess == WAIT_FAILED) {
    _fputts(_T("WAIT_FAILED returned!"), stderr);
    Sleep(10'000);
    return -1;
  } else {
    _fputts(_T("Some random string \n"), stdout);
    DWORD exitCode;
    GetExitCodeProcess(hParent, &exitCode);
    _tprintf(_T("Parent said: %d \n"), exitCode);
    Sleep(10'000);
    return 0;
  }
}
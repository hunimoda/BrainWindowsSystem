#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR *argv[]) {
  HANDLE hProcess;
  TCHAR cmdString[1024];

  DuplicateHandle(GetCurrentProcess(), GetCurrentProcess(), GetCurrentProcess(),
                  &hProcess, 0, TRUE, DUPLICATE_SAME_ACCESS);
  
  _stprintf(cmdString, _T("%s %p"), _T("DuplicateHandleChildProcess.exe"),
            hProcess);

  STARTUPINFO si = { 0, };
  PROCESS_INFORMATION pi;
  si.cb = sizeof(si);

  BOOL isSuccess =
      CreateProcess(NULL, cmdString, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL,
                    NULL, &si, &pi);
  if (!isSuccess) {
    _fputts(_T("CreateProcess failed! \n"), stderr);
    return 1;
  }
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);

  _fputts(_T("[Parent Process] \n"), stdout);
  _fputts(_T("Oooooooooooooooooooooooooooooops! \n"), stdout);
  return 12345;
}
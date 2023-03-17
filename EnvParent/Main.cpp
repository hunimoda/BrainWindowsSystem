#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR *argv[]) {
  SetEnvironmentVariable(_T("good"), _T("morning"));
  SetEnvironmentVariable(_T("hey"), _T("ho"));
  SetEnvironmentVariable(_T("big"), _T("boy"));

  STARTUPINFO si = { 0, };
  PROCESS_INFORMATION pi;
  si.cb = sizeof(si);

  TCHAR command[] = _T("EnvChild");
  CreateProcess(NULL, command, NULL, NULL, FALSE,
                CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT,
                NULL, NULL, &si, &pi);
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
  return 0;
}
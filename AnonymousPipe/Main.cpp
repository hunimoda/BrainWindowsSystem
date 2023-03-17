#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR *argv[]) {
  HANDLE hReadPipe, hWritePipe;

  TCHAR sendString[] = _T("anonymous pipe");
  TCHAR recvString[128];

  DWORD bytesWritten;
  DWORD bytesRead;

  CreatePipe(&hReadPipe, &hWritePipe, NULL, 0);

  WriteFile(hWritePipe, sendString, sizeof(TCHAR) * _tcslen(sendString),
            &bytesWritten, NULL);
  ReadFile(hReadPipe, recvString, sizeof(recvString), &bytesRead, NULL);
  recvString[bytesRead / sizeof(TCHAR)] = NULL;
  _tprintf(_T("string received: %s \n"), recvString);

  CloseHandle(hReadPipe);
  CloseHandle(hWritePipe);

  return 0;
}
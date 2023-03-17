#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define BUF_SIZE 1024

int _tmain(int argc, TCHAR *argv[]) {
  HANDLE hPipe;
  TCHAR readDataBuf[BUF_SIZE + 1];
  LPCTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe");

  while (1) {
    hPipe = CreateFile(pipeName, GENERIC_READ | GENERIC_WRITE,
                       0, NULL, OPEN_EXISTING, 0, NULL);
    if (hPipe != INVALID_HANDLE_VALUE) break;
    if (GetLastError() != ERROR_PIPE_BUSY) {
      _fputts(_T("Could not open pipe \n"), stderr);
      return 1;
    }
    if (!WaitNamedPipe(pipeName, 20'000)) {
      _fputts(_T("Could not open pipe \n"), stderr);
      return 2;
    }
  }

  DWORD pipeMode = PIPE_READMODE_MESSAGE | PIPE_WAIT;
  BOOL isSuccess = SetNamedPipeHandleState(hPipe, &pipeMode, NULL, NULL);
  if (!isSuccess) {
    _fputts(_T("SetNamedPipeHandleState failed \n"), stderr);
    return 3;
  }

  LPCTSTR fileName = _T("news.txt");
  DWORD bytesWritten = 0;
  isSuccess = WriteFile(
      hPipe, fileName, sizeof(TCHAR) * (_tcslen(fileName) + 1),
      &bytesWritten, NULL);
  if (!isSuccess) {
    _fputts(_T("WriteFile failed \n"), stderr);
    return 4;
  }

  DWORD bytesRead = 0;
  while (1) {
    isSuccess = ReadFile(
        hPipe, readDataBuf, sizeof(TCHAR) * BUF_SIZE, &bytesRead, NULL);
    if (!isSuccess && GetLastError() != ERROR_MORE_DATA) {
      break;
    }

    readDataBuf[bytesRead / sizeof(TCHAR)] = 0;
    _tprintf(_T("%s \n"), readDataBuf);
    _gettchar();
  }

  CloseHandle(hPipe);
  return 0;
}
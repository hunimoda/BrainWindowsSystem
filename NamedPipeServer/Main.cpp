#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define BUFFER_SIZE 1024

int CommToClient(HANDLE);

int _tmain(int argc, TCHAR *argv[]) {
  LPCTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe");
  HANDLE hPipe;

  while (1) {
    // 네임드 파이프 생성
    hPipe = CreateNamedPipe(
        pipeName, PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES, BUFFER_SIZE, BUFFER_SIZE, 20'000, NULL);
    if (hPipe == INVALID_HANDLE_VALUE) {
      _fputts(_T("CreatePipe failed! \n"), stderr);
      return 1;
    }

    _fputts(_T("before connect \n"), stdout);
    bool isSuccess = ConnectNamedPipe(hPipe, NULL) ?
        TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);
    _fputts(_T("after connect \n"), stdout);
    if (isSuccess) {
      CommToClient(hPipe);
    } else {
      CloseHandle(hPipe);
    }
  }
  return 0;
}

int CommToClient(HANDLE hPipe) {
  TCHAR fileName[MAX_PATH];
  TCHAR dataBuf[BUFFER_SIZE];

  DWORD fileNameSize;
  BOOL isSuccess = ReadFile(
      hPipe, fileName, sizeof(fileName) - sizeof(TCHAR), &fileNameSize, NULL);
  fileName[fileNameSize / sizeof(TCHAR)] = NULL;

  if (!isSuccess || fileNameSize == 0) {
    _fputts(_T("Pipe read message error! \n"), stderr);
    return 1;
  }

  FILE *filePtr = _tfopen(fileName, _T("rt"));
  if (!filePtr) {
    _tprintf(_T("File open fault: '%s' - error_code: %d \n"), fileName,
             GetLastError());
    return 2;
  }

  DWORD bytesWritten = 0;
  DWORD bytesRead = 0;

  while (!feof(filePtr)) {
    bytesRead = (DWORD)fread(dataBuf, sizeof(TCHAR), BUFFER_SIZE, filePtr);
    WriteFile(hPipe, dataBuf, bytesRead, &bytesWritten, NULL);

    if (bytesRead != bytesWritten) {
      _fputts(_T("Pipe write message error! \n"), stderr);
      break;
    }
  }

  FlushFileBuffers(hPipe);
  DisconnectNamedPipe(hPipe);
  CloseHandle(hPipe);

  return 0;
}
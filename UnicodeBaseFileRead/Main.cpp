#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define BUFFER_SIZE 4

int _tmain(int argc, TCHAR *argv[]) {
  TCHAR fileName[] = _T("data.txt");
  TCHAR buffer[BUFFER_SIZE + 1];

  HANDLE hFile = CreateFile(
      fileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING,
      FILE_ATTRIBUTE_NORMAL, 0);
  if (hFile == INVALID_HANDLE_VALUE) {
    _fputts(_T("CreateFile fault! \n"), stderr);
    return 1;
  }

  DWORD totalByteRead = 0;
  DWORD numOfByteRead = 0;
  while (ReadFile(hFile, buffer, sizeof(TCHAR) * BUFFER_SIZE,
                  &numOfByteRead, NULL) &&
         numOfByteRead > 0) {
    buffer[numOfByteRead / sizeof(TCHAR)] = NULL;
    _fputts(buffer, stdout);
    totalByteRead += numOfByteRead;
  }
  _fputts(_T("\n"), stdout);
  _tprintf(_T("Total bytes read: %dB \n"), totalByteRead);

  CloseHandle(hFile);
  return 0;
}
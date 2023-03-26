#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define STRING_LEN 128

TCHAR fileData[] = _T("abcdefghijklmnopqrstuvwxyz");

int _tmain(int argc, TCHAR *argv[]) {
  TCHAR fileName[] = _T("abcd.dat");
  TCHAR readBuf[STRING_LEN + 1];

  HANDLE hFileWrite, hFileRead;
  DWORD numOfByteWritten;

  hFileWrite = CreateFile(
      fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
  WriteFile(hFileWrite, fileData, sizeof(TCHAR) * _tcslen(fileData),
            &numOfByteWritten, NULL);
  CloseHandle(hFileWrite);

  SetCurrentDirectory(_T("C:\\"));
  hFileRead = CreateFile(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
  if (hFileRead == INVALID_HANDLE_VALUE) {
    _fputts(_T("CreateFile fault! \n"), stderr);
    return 1;
  }
  ReadFile(hFileRead, readBuf, sizeof(TCHAR) * STRING_LEN, &numOfByteWritten,
           NULL);
  readBuf[numOfByteWritten / sizeof(TCHAR)] = NULL;
  _tprintf(_T("read string: %s \n"), readBuf);
  CloseHandle(hFileRead);

  return 0;
}

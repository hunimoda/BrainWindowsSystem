#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define STRING_LEN 128

TCHAR fileData[] = _T("abcdefghijklmnopqrstuvwxyz");

int _tmain(int argc, TCHAR *argv[]) {
  TCHAR fileName[] = _T("abcd.dat");
  TCHAR readBuf[STRING_LEN];

  HANDLE hFile;
  DWORD numOfByteWritten = 0;
  DWORD dwPtrLow = 0;

  LONG lDistanceLow = sizeof(TCHAR) * 4;
  LONG lDistanceHigh = 0;

  hFile = CreateFile(
      fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
  WriteFile(hFile, fileData, sizeof(fileData), &numOfByteWritten, NULL);
  _tprintf(_T("Bytes written: %d B \n"), numOfByteWritten);
  CloseHandle(hFile);

  hFile = CreateFile(
      fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
  ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
  _tprintf(_T("%s \n"), readBuf);

  dwPtrLow = SetFilePointer(hFile, lDistanceLow, &lDistanceHigh, FILE_BEGIN);
  if (dwPtrLow == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR) {
    _fputts(_T("SetFilePointer error \n"), stderr);
    return 1;
  }

  ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
  _tprintf(_T("%s \n"), readBuf);

  CloseHandle(hFile);
  return 0;
}
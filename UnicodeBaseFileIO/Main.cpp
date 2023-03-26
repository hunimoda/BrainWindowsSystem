#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR *argv[]) {
  TCHAR fileName[] = _T("data.txt");
  TCHAR fileData[] = _T("Simple string");

  HANDLE hFile = CreateFile(
      fileName, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS,
      FILE_ATTRIBUTE_NORMAL, 0);
  if (hFile == INVALID_HANDLE_VALUE) {
    _fputts(_T("CreateFile fault! \n"), stderr);
    return 1;
  }

  DWORD numOfByteWritten = 0;
  WriteFile(hFile, fileData, sizeof(TCHAR) * _tcslen(fileData),
            &numOfByteWritten, NULL);
  _tprintf(_T("Written data size: %uB \n"), numOfByteWritten);

  CloseHandle(hFile);
  return 0;
}
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR *argv[]) {
  HANDLE hMailSlot;
  TCHAR message[50];
  DWORD bytesWritten;

  // 핸들을 얻는 코드
  FILE *file = _tfopen(_T("InheritableHandle.txt"), _T("rt"));
  _ftscanf(file, _T("%p"), &hMailSlot);
  fclose(file);
  _tprintf(_T("Inheritable handle: %p \n"), hMailSlot);

  while (1) {
    _fputts(_T("MY CMD>"), stdout);
    _fgetts(message, sizeof(message) / sizeof(TCHAR), stdin);

    if (!WriteFile(hMailSlot, message, _tcslen(message) * sizeof(TCHAR),
                   &bytesWritten, NULL)) {
      _ftprintf(stderr, _T("Error code: %d \n"), GetLastError());
      _fputts(_T("Unable to write!"), stderr);
      _gettchar();
      CloseHandle(hMailSlot);
      return 1;
    }
    if (!_tcscmp(message, _T("exit"))) {
      _fputts(_T("Good bye! \n"), stdout);
      break;
    }
  }
  CloseHandle(hMailSlot);
  return 0;
}

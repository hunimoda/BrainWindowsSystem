#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define STRING_LEN 128

TCHAR fileData[] = _T("abcdefghijklmnopqrstuvwxyz");

int _tmain(int argc, TCHAR *argv[]) {
  // 파일 개방 후 알파벳 출력
  LPCTSTR fileName = _T("sample.txt");
  HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
  DWORD numberOfBytesWritten = 0;
  WriteFile(hFile, fileData, sizeof(TCHAR) * _tcslen(fileData),
            &numberOfBytesWritten, NULL);
  CloseHandle(hFile);

  // 파일 개방 후 내용을 읽어들임
  TCHAR buffer[STRING_LEN + 1];
  hFile = CreateFile(
      fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
  DWORD numberOfBytesRead = 0;
  ReadFile(hFile, buffer, sizeof(TCHAR) * STRING_LEN, &numberOfBytesRead, NULL);
  buffer[numberOfBytesRead / sizeof(TCHAR)] = NULL;
  _tprintf(_T("1) content: %s \n"), buffer);

  // 파일 포인터를 앞에서 4번째로 이동
  DWORD dwFilePtr = SetFilePointer(hFile, sizeof(TCHAR) * 4, NULL, FILE_BEGIN);
  if (dwFilePtr == INVALID_SET_FILE_POINTER) {
    _fputts(_T("SetFilePointer fault! \n"), stderr);
    return 2;
  }
  ReadFile(hFile, buffer, sizeof(TCHAR) * STRING_LEN, &numberOfBytesRead, NULL);
  buffer[numberOfBytesRead / sizeof(TCHAR)] = NULL;
  _tprintf(_T("2) content: %s \n"), buffer);

  // 파일 포인터를 끝에서 3번째 칸으로 이동
  dwFilePtr = SetFilePointer(hFile, sizeof(TCHAR) * (-3), NULL, FILE_END);
  if (dwFilePtr == INVALID_SET_FILE_POINTER) {
    _fputts(_T("SetFilePointer fault! \n"), stderr);
    return 2;
  }
  ReadFile(hFile, buffer, sizeof(TCHAR) * STRING_LEN, &numberOfBytesRead, NULL);
  buffer[numberOfBytesRead / sizeof(TCHAR)] = NULL;
  _tprintf(_T("3) content: %s \n"), buffer);

  CloseHandle(hFile);
  return 0;
}
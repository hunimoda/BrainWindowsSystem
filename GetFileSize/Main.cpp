#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR *argv[]) {
  // 전달인자의 수 확인
  if (argc != 2) {
    _fputts(_T("Usage: %s [FILE_NAME] \n"), stderr);
    return 1;
  }

  // 파일 개방
  TCHAR *fileName = argv[1];
  HANDLE hFile = CreateFile(
      fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
  if (hFile == INVALID_HANDLE_VALUE) {
    _fputts(_T("CreateFile fault! \n"), stderr);
    return 2;
  }

  // 파일 사이즈 계산
  DWORD fileSizeHigh = 0;
  DWORD fileSizeLow = GetFileSize(hFile, &fileSizeHigh);

  _tprintf(_T("High 4 byte file size: %u byte \n"), fileSizeHigh);
  _tprintf(_T("Low 4 byte file size:  %u byte \n"), fileSizeLow);

  // 전체 파일 사이즈 계산 후 출력
  LARGE_INTEGER fileSize;
  fileSize.HighPart = fileSizeHigh;
  fileSize.LowPart = fileSizeLow;
  _tprintf(_T("Total file size: %llu byte \n"), fileSize.QuadPart);

  CloseHandle(hFile);
  return 0;
}
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define TIME_STRING_LEN 128

void ShowAttributes(DWORD);
LPCTSTR FormatFileTime(FILETIME);

int _tmain(int argc, TCHAR *argv[]) {
  // 전달인자의 수 확인
  if (argc != 2) {
    _ftprintf(stderr, _T("Usage: %s [FILE NAME] \n"), argv[0]);
    return 1;
  }

  // 인자로 전달받은 파일을 읽기 모드로 개방
  const TCHAR *fileName = argv[1];
  HANDLE hFile = CreateFile(
      fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
  if (hFile == INVALID_HANDLE_VALUE) {
    _fputts(_T("CreateFile fault! \n"), stderr);
    return 2;
  }

  // 파일 정보 추출
  BY_HANDLE_FILE_INFORMATION fileInformation;
  GetFileInformationByHandle(hFile, &fileInformation);

  // 파일 정보 중 특성 정보 출력
  ShowAttributes(fileInformation.dwFileAttributes);

  // 추가 정보 출력
  _tprintf(_T("File size: %u B \n"), fileInformation.nFileSizeLow);
  _tprintf(_T("Created at: %s \n"),
           FormatFileTime(fileInformation.ftCreationTime));
  _tprintf(_T("Accessed at: %s \n"),
           FormatFileTime(fileInformation.ftLastAccessTime));
  _tprintf(_T("Written at: %s \n"),
           FormatFileTime(fileInformation.ftLastWriteTime));

  CloseHandle(hFile);
  return 0;
}

void ShowAttributes(DWORD dwFileAttributes) {
  if (dwFileAttributes & FILE_ATTRIBUTE_NORMAL) {
    _fputts(_T("Normal \n"), stdout);
    return;
  }
  if (dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) {
    _fputts(_T("Archive \n"), stdout);
  }
  if (dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
    _fputts(_T("Read-only \n"), stdout);
  }
  if (dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) {
    _fputts(_T("Hidden \n"), stdout);
  }
  _fputts(_T("\n"), stdout);
}

LPCTSTR FormatFileTime(FILETIME fileTime) {
  static TCHAR fileTimeStr[TIME_STRING_LEN];
  SYSTEMTIME systemTime, localTime;
  FileTimeToSystemTime(&fileTime, &systemTime);
  SystemTimeToTzSpecificLocalTime(NULL, &systemTime, &localTime);
  _stprintf_s(fileTimeStr, TIME_STRING_LEN, _T("%d-%02d-%02d %02d:%02d:%02d"),
              localTime.wYear, localTime.wMonth, localTime.wDay,
              localTime.wHour, localTime.wMinute, localTime.wSecond);
  return fileTimeStr;
}
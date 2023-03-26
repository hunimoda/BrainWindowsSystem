#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

LPCTSTR GetTimeString(const FILETIME &);

int _tmain(int argc, TCHAR *argv[]) {
  // 탐색 대상 디렉터리 지정
  TCHAR findDirectory[MAX_PATH] = { NULL, };
  if (argc == 1) {
    GetCurrentDirectory(MAX_PATH, findDirectory);
  } else {
    _tcscpy(findDirectory, argv[1]);
  }
  _tcscat(findDirectory, _T("\\*"));

  // 검색 핸들 획득
  WIN32_FIND_DATA win32FindData;
  HANDLE hFind = FindFirstFile(findDirectory, &win32FindData);
  if (hFind == INVALID_HANDLE_VALUE) {
    if (GetLastError() == ERROR_FILE_NOT_FOUND) {
      _fputts(_T("No file was found! \n"), stderr);
      return 1;
    } else {
      _fputts(_T("FindFirstFile fault! \n"), stderr);
      return 2;
    }
  }

  do {
    if (!_tcscmp(win32FindData.cFileName, _T(".")) ||
        !_tcscmp(win32FindData.cFileName, _T(".."))) {
      continue;
    }
    _tprintf(_T("[%s] \n"), win32FindData.cFileName);
    if (_tcslen(win32FindData.cAlternateFileName) > 0) {
      _tprintf(_T("alias:       %s \n"), win32FindData.cAlternateFileName);
    }
    _tprintf(_T("attributes:  0x%08X \n"), win32FindData.dwFileAttributes);
    _tprintf(_T("created at:  %s \n"),
             GetTimeString(win32FindData.ftCreationTime));
    _tprintf(_T("last access: %s \n"),
             GetTimeString(win32FindData.ftLastAccessTime));
    _tprintf(_T("last write:  %s \n"),
             GetTimeString(win32FindData.ftLastWriteTime));
    DWORD64 fileSize = win32FindData.nFileSizeLow;
    fileSize += win32FindData.nFileSizeHigh * ((DWORD64)MAXDWORD + 1);
    _tprintf(_T("file size:   %lld B \n\n"), fileSize);
  } while (FindNextFile(hFind, &win32FindData));

  FindClose(hFind);
  return 0;
}

LPCTSTR GetTimeString(const FILETIME &fileTime) {
  static TCHAR timeString[] = _T("0000-00-00 00:00:00");
  SYSTEMTIME systemTime, localTime;
  FileTimeToSystemTime(&fileTime, &systemTime);
  SystemTimeToTzSpecificLocalTime(NULL, &systemTime, &localTime);
  _stprintf(timeString, _T("%04d-%02d-%02d %02d:%02d:%02d"),
            localTime.wYear, localTime.wMonth, localTime.wDay,
            localTime.wHour, localTime.wMinute, localTime.wSecond);
  return timeString;
}
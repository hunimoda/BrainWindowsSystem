#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define TIME_STRING_LEN 128

int _tmain(int argc, TCHAR *argv[]) {
  TCHAR fileName[] = _T("Main.cpp");
  HANDLE hFile = CreateFile(
      fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
  if (hFile == INVALID_HANDLE_VALUE) {
    _fputts(_T("CreateFile fault! \n"), stderr);
    return 1;
  }

  // 파일 시간 정보 추출
  FILETIME creationTime, lastAccessTime, lastWriteTime;
  if (!GetFileTime(hFile, &creationTime, &lastAccessTime, &lastWriteTime)) {
    _fputts(_T("GetFileTime fault! \n"), stderr);
    return 2;
  }

  // 시간 정보 변환
  SYSTEMTIME stCreate, stCreateLocal;
  FileTimeToSystemTime(&creationTime, &stCreate);
  SystemTimeToTzSpecificLocalTime(NULL, &stCreate, &stCreateLocal);
  SYSTEMTIME stAccess, stAccessLocal;
  FileTimeToSystemTime(&lastAccessTime, &stAccess);
  SystemTimeToTzSpecificLocalTime(NULL, &stAccess, &stAccessLocal);
  SYSTEMTIME stWrite, stWriteLocal;
  FileTimeToSystemTime(&lastWriteTime, &stWrite);
  SystemTimeToTzSpecificLocalTime(NULL, &stWrite, &stWriteLocal);

  // 시간 정보 문자열 형태로 구성
  TCHAR fileCreateTime[TIME_STRING_LEN];
  _stprintf(fileCreateTime, _T("%02d/%02d/%d  %02d:%02d:%02d"),
            stCreateLocal.wMonth, stCreateLocal.wDay, stCreateLocal.wYear,
            stCreateLocal.wHour, stCreateLocal.wMinute, stCreateLocal.wSecond);
  TCHAR fileAccessTime[TIME_STRING_LEN];
  _stprintf(fileAccessTime, _T("%02d/%02d/%d  %02d:%02d:%02d"),
            stAccessLocal.wMonth, stAccessLocal.wDay, stAccessLocal.wYear,
            stAccessLocal.wHour, stAccessLocal.wMinute, stAccessLocal.wSecond);
  TCHAR fileWriteTime[TIME_STRING_LEN];
  _stprintf(fileWriteTime, _T("%02d/%02d/%d  %02d:%02d:%02d"),
            stWriteLocal.wMonth, stWriteLocal.wDay, stWriteLocal.wYear,
            stWriteLocal.wHour, stWriteLocal.wMinute, stWriteLocal.wSecond);
  
  // 시간 문자열 출력
  _tprintf(_T("Create time: %s \n"), fileCreateTime);
  _tprintf(_T("Access time: %s \n"), fileAccessTime);
  _tprintf(_T("Write time: %s \n"), fileWriteTime);

  CloseHandle(hFile);
  return 0;
}
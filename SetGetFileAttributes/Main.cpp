#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

void ShowAttributes(const DWORD);

int _tmain(int argc, TCHAR *argv[]) {
  // 전달인자의 수 확인
  if (argc != 2) {
    _fputts(_T("Usage: %s [FILE NAME] \n"), stderr);
    return 1;
  }

  const TCHAR *fileName = argv[1];

  // 원본 파일 정보 출력
  _fputts(_T("*** Original file attributes *** \n"), stdout);
  DWORD fileAttributes = GetFileAttributes(fileName);
  ShowAttributes(fileAttributes);
  _fputts(_T("\n"), stdout);

  //// 파일 정보 변경 (읽기 전용 + 숨김)
  //fileAttributes |= FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN;
  //SetFileAttributes(fileName, fileAttributes);

  //// 변경된 파일 정보 출력
  //_fputts(_T("*** Changed file attributes *** \n"), stdout);
  //fileAttributes = GetFileAttributes(fileName);
  //ShowAttributes(fileAttributes);
  //_fputts(_T("\n"), stdout);
  
  return 0;
}

void ShowAttributes(const DWORD fileAttributes) {
  if (fileAttributes & FILE_ATTRIBUTE_NORMAL) {
    _fputts(_T("normal \n"), stdout);
    return;
  }
  if (fileAttributes & FILE_ATTRIBUTE_READONLY) {
    _fputts(_T("read-only \n"), stdout);
  }
  if (fileAttributes & FILE_ATTRIBUTE_HIDDEN) {
    _fputts(_T("hidden \n"), stdout);
  }
  if (fileAttributes & FILE_ATTRIBUTE_SYSTEM) {
    _fputts(_T("system \n"), stdout);
  }
  if (fileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
    _fputts(_T("directory \n"), stdout);
  }
  if (fileAttributes & FILE_ATTRIBUTE_ARCHIVE) {
    _fputts(_T("archive \n"), stdout);
  }
  if (fileAttributes & FILE_ATTRIBUTE_DEVICE) {
    _fputts(_T("device \n"), stdout);
  }
  if (fileAttributes & FILE_ATTRIBUTE_TEMPORARY) {
    _fputts(_T("temporary \n"), stdout);
  }
  if (fileAttributes & FILE_ATTRIBUTE_SPARSE_FILE) {
    _fputts(_T("sparse file \n"), stdout);
  }
  if (fileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) {
    _fputts(_T("reparse point \n"), stdout);
  }
  if (fileAttributes & FILE_ATTRIBUTE_COMPRESSED) {
    _fputts(_T("compressed \n"), stdout);
  }
  if (fileAttributes & FILE_ATTRIBUTE_OFFLINE) {
    _fputts(_T("offline \n"), stdout);
  }
  if (fileAttributes & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED) {
    _fputts(_T("not content indexed \n"), stdout);
  }
  if (fileAttributes & FILE_ATTRIBUTE_ENCRYPTED) {
    _fputts(_T("encrypted \n"), stdout);
  }
  if (fileAttributes & FILE_ATTRIBUTE_INTEGRITY_STREAM) {
    _fputts(_T("integrity stream \n"), stdout);
  }
  if (fileAttributes & FILE_ATTRIBUTE_VIRTUAL) {
    _fputts(_T("virtual \n"), stdout);
  }
  if (fileAttributes & FILE_ATTRIBUTE_NO_SCRUB_DATA) {
    _fputts(_T("no scrub data \n"), stdout);
  }
  if (fileAttributes & FILE_ATTRIBUTE_EA) {
    _fputts(_T("ea \n"), stdout);
  }
  if (fileAttributes & FILE_ATTRIBUTE_PINNED) {
    _fputts(_T("pinned \n"), stdout);
  }
  if (fileAttributes & FILE_ATTRIBUTE_UNPINNED) {
    _fputts(_T("unpinned \n"), stdout);
  }
  if (fileAttributes & FILE_ATTRIBUTE_RECALL_ON_OPEN) {
    _fputts(_T("recall on open \n"), stdout);
  }
  if (fileAttributes & FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS) {
    _fputts(_T("recall on data access \n"), stdout);
  }
}
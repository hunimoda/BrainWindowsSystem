#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define BUFFER_SIZE 1024

int _tmain(int argc, TCHAR *argv[]) {
  TCHAR value[BUFFER_SIZE];
  if (GetEnvironmentVariable(_T("good"), value, sizeof(value)) > 0) {
    _tprintf(_T("%s \n"), value);
  }
  if (GetEnvironmentVariable(_T("hey"), value, sizeof(value)) > 0) {
    _tprintf(_T("%s \n"), value);
  }
  if (GetEnvironmentVariable(_T("big"), value, sizeof(value)) > 0) {
    _tprintf(_T("%s \n"), value);
  }
  Sleep(10'000);
  return 0;
}